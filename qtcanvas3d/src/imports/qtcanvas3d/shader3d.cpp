/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the QtCanvas3D module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL3$
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
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPLv3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or later as published by the Free
** Software Foundation and appearing in the file LICENSE.GPL included in
** the packaging of this file. Please review the following information to
** ensure the GNU General Public License version 2.0 requirements will be
** met: http://www.gnu.org/licenses/gpl-2.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "shader3d_p.h"

QT_BEGIN_NAMESPACE
QT_CANVAS3D_BEGIN_NAMESPACE

/*!
 * \qmltype Canvas3DShader
 * \since QtCanvas3D 1.0
 * \inqmlmodule QtCanvas3D
 * \inherits Canvas3DAbstractObject
 * \brief Contains a shader.
 *
 * An uncreatable QML type that contains a shader. You can get it by calling
 * the \l{Context3D::createShader()}{Context3D.createShader()} method.
 */

CanvasShader::CanvasShader(GLenum type, CanvasGlCommandQueue *queue, QObject *parent) :
    CanvasAbstractObject(queue, parent),
    m_shaderId(queue->createResourceId()),
    m_sourceCode("")
{
    queueCommand(CanvasGlCommandQueue::glCreateShader, GLint(type), m_shaderId);
}

CanvasShader::~CanvasShader()
{
    del();
}

GLint CanvasShader::id()
{
    return m_shaderId;
}

bool CanvasShader::isAlive()
{
    return bool(m_shaderId);
}

void CanvasShader::del()
{
    if (m_shaderId) {
        queueCommand(CanvasGlCommandQueue::glDeleteShader, m_shaderId);
        m_shaderId = 0;
    }
}

QString CanvasShader::sourceCode()
{
    return m_sourceCode;
}

void CanvasShader::setSourceCode(const QString &source)
{
    m_sourceCode = source;
}

void CanvasShader::compileShader()
{
    if (m_shaderId) {
        queueCommand(CanvasGlCommandQueue::glCompileShader, new QByteArray(m_sourceCode.toLatin1()),
                     m_shaderId);
    }
}

QT_CANVAS3D_END_NAMESPACE
QT_END_NAMESPACE
