/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Quick Layouts module of the Qt Toolkit.
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

#include <QtGui/private/qfont_p.h>

#include "qquicklayoutstyleinfo_p.h"


QT_BEGIN_NAMESPACE

QQuickLayoutStyleInfo::QQuickLayoutStyleInfo()
{
}

qreal QQuickLayoutStyleInfo::spacing(Qt::Orientation /*orientation*/) const
{
#if defined(Q_OS_ANDROID) || defined(Q_OS_IOS) || defined(Q_OS_BLACKBERRY) || defined(Q_OS_QNX) || defined(Q_OS_WINRT)
    // On Android and iOS the default spacing between each UI element is 8dp
    qreal spacing = 8.0;
#else
    qreal spacing = 5.0;
#endif

#ifndef Q_OS_OSX
    // On OS X the DPI is always 72 so we should not scale it
    spacing = qRound(spacing * (qreal(qt_defaultDpiX()) / 96.0));
#endif

    return spacing;
}

qreal QQuickLayoutStyleInfo::windowMargin(Qt::Orientation /*orientation*/) const
{
    return 0;
}

bool QQuickLayoutStyleInfo::hasChangedCore() const
{
    // never changes
    return false;
}

QT_END_NAMESPACE

