/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the plugins of the Qt Toolkit.
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

#include "qnswindowdelegate.h"

#include <QDebug>
#include <qpa/qwindowsysteminterface.h>

@implementation QNSWindowDelegate

- (id) initWithQCocoaWindow: (QCocoaWindow *) cocoaWindow
{
    self = [super init];

    if (self) {
        m_cocoaWindow = cocoaWindow;
    }
    return self;
}

- (void)windowDidBecomeKey:(NSNotification *)notification
{
    Q_UNUSED(notification);
    if (m_cocoaWindow->m_windowUnderMouse) {
        QPointF windowPoint;
        QPointF screenPoint;
        [m_cocoaWindow->m_qtView convertFromScreen:[NSEvent mouseLocation] toWindowPoint:&windowPoint andScreenPoint:&screenPoint];
        QWindowSystemInterface::handleEnterEvent(m_cocoaWindow->m_enterLeaveTargetWindow, windowPoint, screenPoint);
    }
}

- (void)windowDidResize:(NSNotification *)notification
{
    Q_UNUSED(notification);
    if (m_cocoaWindow) {
        m_cocoaWindow->windowDidResize();
    }
}

- (void)windowDidEndLiveResize:(NSNotification *)notification
{
    Q_UNUSED(notification);
    if (m_cocoaWindow) {
        m_cocoaWindow->windowDidEndLiveResize();
    }
}

- (void)windowWillMove:(NSNotification *)notification
{
    Q_UNUSED(notification);
    if (m_cocoaWindow) {
        m_cocoaWindow->windowWillMove();
    }
}

- (void)windowDidMove:(NSNotification *)notification
{
    Q_UNUSED(notification);
    if (m_cocoaWindow) {
        m_cocoaWindow->windowDidMove();
    }
}

- (BOOL)windowShouldClose:(NSNotification *)notification
{
    Q_UNUSED(notification);
    if (m_cocoaWindow) {
        return m_cocoaWindow->windowShouldClose();
    }

    return YES;
}

- (BOOL)windowShouldZoom:(NSWindow *)window toFrame:(NSRect)newFrame
{
    Q_UNUSED(newFrame);
    if (m_cocoaWindow && m_cocoaWindow->m_qtView)
        [m_cocoaWindow->m_qtView notifyWindowWillZoom:![window isZoomed]];
    return YES;
}

- (BOOL)window:(NSWindow *)window shouldPopUpDocumentPathMenu:(NSMenu *)menu
{
    Q_UNUSED(window);
    Q_UNUSED(menu);
    return m_cocoaWindow && m_cocoaWindow->m_hasWindowFilePath;
}

- (BOOL)window:(NSWindow *)window shouldDragDocumentWithEvent:(NSEvent *)event from:(NSPoint)dragImageLocation withPasteboard:(NSPasteboard *)pasteboard
{
    Q_UNUSED(window);
    Q_UNUSED(event);
    Q_UNUSED(dragImageLocation);
    Q_UNUSED(pasteboard);
    return m_cocoaWindow && m_cocoaWindow->m_hasWindowFilePath;
}
@end
