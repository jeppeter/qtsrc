/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the QtQuick module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL21$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file. Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** As a special exception, The Qt Company gives you certain additional
** rights. These rights are described in The Qt Company LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qquicktextnode_p.h"

#include "qquicktextnodeengine_p.h"

#include <private/qsgadaptationlayer_p.h>
#include <private/qsgdistancefieldglyphnode_p.h>
#include <private/qquickclipnode_p.h>
#include <private/qquickitem_p.h>
#include <QtQuick/private/qsgcontext_p.h>

#include <QtCore/qpoint.h>
#include <qtextdocument.h>
#include <qtextlayout.h>
#include <qabstracttextdocumentlayout.h>
#include <qxmlstream.h>
#include <private/qquickstyledtext_p.h>
#include <private/qfont_p.h>
#include <private/qfontengine_p.h>

#include <private/qtextdocumentlayout_p.h>
#include <qhash.h>

QT_BEGIN_NAMESPACE

namespace {

    class ProtectedLayoutAccessor: public QAbstractTextDocumentLayout
    {
    public:
        inline QTextCharFormat formatAccessor(int pos)
        {
            return format(pos);
        }
    };

}

/*!
  Creates an empty QQuickTextNode
*/
QQuickTextNode::QQuickTextNode(QQuickItem *ownerElement)
    : m_cursorNode(0), m_ownerElement(ownerElement), m_useNativeRenderer(false)
{
#ifdef QSG_RUNTIME_DESCRIPTION
    qsgnode_set_description(this, QLatin1String("text"));
#endif
}

QQuickTextNode::~QQuickTextNode()
{
    qDeleteAll(m_textures);
}

QSGGlyphNode *QQuickTextNode::addGlyphs(const QPointF &position, const QGlyphRun &glyphs, const QColor &color,
                                     QQuickText::TextStyle style, const QColor &styleColor,
                                     QSGNode *parentNode)
{
    QSGRenderContext *sg = QQuickItemPrivate::get(m_ownerElement)->sceneGraphRenderContext();
    QRawFont font = glyphs.rawFont();
    bool preferNativeGlyphNode = m_useNativeRenderer;
    if (!preferNativeGlyphNode) {
        QRawFontPrivate *fontPriv = QRawFontPrivate::get(font);
        if (fontPriv->fontEngine->hasUnreliableGlyphOutline()) {
            preferNativeGlyphNode = true;
        } else {
            QFontEngine *fe = QRawFontPrivate::get(font)->fontEngine;
            preferNativeGlyphNode = !fe->isSmoothlyScalable;
        }
    }

    QSGGlyphNode *node = sg->sceneGraphContext()->createGlyphNode(sg, preferNativeGlyphNode);

    node->setOwnerElement(m_ownerElement);
    node->setGlyphs(position + QPointF(0, glyphs.rawFont().ascent()), glyphs);
    node->setStyle(style);
    node->setStyleColor(styleColor);
    node->setColor(color);
    node->update();

    /* We flag the geometry as static, but we never call markVertexDataDirty
       or markIndexDataDirty on them. This is because all text nodes are
       discarded when a change occurs. If we start appending/removing from
       existing geometry, then we also need to start marking the geometry as
       dirty.
     */
    node->geometry()->setIndexDataPattern(QSGGeometry::StaticPattern);
    node->geometry()->setVertexDataPattern(QSGGeometry::StaticPattern);

    if (parentNode == 0)
        parentNode = this;
    parentNode->appendChildNode(node);

    return node;
}

void QQuickTextNode::setCursor(const QRectF &rect, const QColor &color)
{
    if (m_cursorNode != 0)
        delete m_cursorNode;

    QSGRenderContext *sg = QQuickItemPrivate::get(m_ownerElement)->sceneGraphRenderContext();
    m_cursorNode =  sg->sceneGraphContext()->createRectangleNode(rect, color);
    appendChildNode(m_cursorNode);
}

void QQuickTextNode::clearCursor()
{
    if (m_cursorNode)
        removeChildNode(m_cursorNode);
    delete m_cursorNode;
    m_cursorNode = 0;
}

void QQuickTextNode::addRectangleNode(const QRectF &rect, const QColor &color)
{
    QSGRenderContext *sg = QQuickItemPrivate::get(m_ownerElement)->sceneGraphRenderContext();
    appendChildNode(sg->sceneGraphContext()->createRectangleNode(rect, color));
}


void QQuickTextNode::addImage(const QRectF &rect, const QImage &image)
{
    QSGRenderContext *sg = QQuickItemPrivate::get(m_ownerElement)->sceneGraphRenderContext();
    QSGImageNode *node = sg->sceneGraphContext()->createImageNode();
    QSGTexture *texture = sg->createTexture(image);
    m_textures.append(texture);
    node->setTargetRect(rect);
    node->setInnerTargetRect(rect);
    node->setTexture(texture);
    appendChildNode(node);
    node->update();
}

void QQuickTextNode::addTextDocument(const QPointF &position, QTextDocument *textDocument,
                                  const QColor &textColor,
                                  QQuickText::TextStyle style, const QColor &styleColor,
                                  const QColor &anchorColor,
                                  const QColor &selectionColor, const QColor &selectedTextColor,
                                  int selectionStart, int selectionEnd)
{
    QQuickTextNodeEngine engine;
    engine.setTextColor(textColor);
    engine.setSelectedTextColor(selectedTextColor);
    engine.setSelectionColor(selectionColor);
    engine.setAnchorColor(anchorColor);
    engine.setPosition(position);

    QList<QTextFrame *> frames;
    frames.append(textDocument->rootFrame());
    while (!frames.isEmpty()) {
        QTextFrame *textFrame = frames.takeFirst();
        frames.append(textFrame->childFrames());

        engine.addFrameDecorations(textDocument, textFrame);

        if (textFrame->firstPosition() > textFrame->lastPosition()
         && textFrame->frameFormat().position() != QTextFrameFormat::InFlow) {
            const int pos = textFrame->firstPosition() - 1;
            ProtectedLayoutAccessor *a = static_cast<ProtectedLayoutAccessor *>(textDocument->documentLayout());
            QTextCharFormat format = a->formatAccessor(pos);
            QRectF rect = a->frameBoundingRect(textFrame);

            QTextBlock block = textFrame->firstCursorPosition().block();
            engine.setCurrentLine(block.layout()->lineForTextPosition(pos - block.position()));
            engine.addTextObject(rect.topLeft(), format, QQuickTextNodeEngine::Unselected, textDocument,
                                 pos, textFrame->frameFormat().position());
        } else {
            QTextFrame::iterator it = textFrame->begin();

            while (!it.atEnd()) {
                Q_ASSERT(!engine.currentLine().isValid());

                QTextBlock block = it.currentBlock();
                engine.addTextBlock(textDocument, block, position, textColor, anchorColor, selectionStart, selectionEnd);
                ++it;
            }
        }
    }

    engine.addToSceneGraph(this, style, styleColor);
}

void QQuickTextNode::addTextLayout(const QPointF &position, QTextLayout *textLayout, const QColor &color,
                                QQuickText::TextStyle style, const QColor &styleColor,
                                const QColor &anchorColor,
                                const QColor &selectionColor, const QColor &selectedTextColor,
                                int selectionStart, int selectionEnd,
                                int lineStart, int lineCount)
{
    QQuickTextNodeEngine engine;
    engine.setTextColor(color);
    engine.setSelectedTextColor(selectedTextColor);
    engine.setSelectionColor(selectionColor);
    engine.setAnchorColor(anchorColor);
    engine.setPosition(position);

#ifndef QT_NO_IM
    int preeditLength = textLayout->preeditAreaText().length();
    int preeditPosition = textLayout->preeditAreaPosition();
#endif

    QVarLengthArray<QTextLayout::FormatRange> colorChanges;
    engine.mergeFormats(textLayout, &colorChanges);

    lineCount = lineCount >= 0
            ? qMin(lineStart + lineCount, textLayout->lineCount())
            : textLayout->lineCount();

    for (int i=lineStart; i<lineCount; ++i) {
        QTextLine line = textLayout->lineAt(i);

        int start = line.textStart();
        int length = line.textLength();
        int end = start + length;

#ifndef QT_NO_IM
        if (preeditPosition >= 0
         && preeditPosition >= start
         && preeditPosition < end) {
            end += preeditLength;
        }
#endif

        engine.setCurrentLine(line);
        engine.addGlyphsForRanges(colorChanges, start, end, selectionStart, selectionEnd);
    }

    engine.addToSceneGraph(this, style, styleColor);
}

void QQuickTextNode::deleteContent()
{
    while (firstChild() != 0)
        delete firstChild();
    m_cursorNode = 0;
    qDeleteAll(m_textures);
    m_textures.clear();
}

QT_END_NAMESPACE
