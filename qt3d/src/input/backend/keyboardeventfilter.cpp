/****************************************************************************
**
** Copyright (C) 2014 Klaralvdalens Datakonsult AB (KDAB).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the Qt3D module of the Qt Toolkit.
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

#include "keyboardeventfilter_p.h"
#include "inputhandler_p.h"
#include <QEvent>
#include <QKeyEvent>

QT_BEGIN_NAMESPACE

namespace Qt3DInput {
namespace Input {

// The KeyboardEventFilter must be in the same thread as the view it will be monitoring

KeyboardEventFilter::KeyboardEventFilter(QObject *parent)
    : QObject(parent)
{
}

void KeyboardEventFilter::setInputHandler(InputHandler *handler)
{
    m_inputHandler = handler;
}

// Triggered in the view thread (usually the main thread)
bool KeyboardEventFilter::eventFilter(QObject *obj, QEvent *e)
{
    Q_UNUSED(obj);
    if (e->type() == QEvent::KeyPress || e->type() == QEvent::KeyRelease) {
        // Store event to be processed later on in an InputAspect job
        m_inputHandler->appendKeyEvent(QT_PREPEND_NAMESPACE(QKeyEvent)(*static_cast<QT_PREPEND_NAMESPACE(QKeyEvent) *>(e)));
    }
    return false;
}

} // namespace Input
} // namespace Qt3DInput

QT_END_NAMESPACE
