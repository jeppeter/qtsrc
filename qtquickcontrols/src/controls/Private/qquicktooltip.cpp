/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Quick Controls module of the Qt Toolkit.
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

#include "qquicktooltip_p.h"
#include <qquickwindow.h>
#include <qquickitem.h>
#include <private/qguiapplication_p.h>
#include <qpa/qplatformintegration.h>
#include <QtQuick/QQuickRenderControl>

#ifdef QT_WIDGETS_LIB
#include <qtooltip.h>
#endif

QT_BEGIN_NAMESPACE

QQuickTooltip::QQuickTooltip(QObject *parent)
    : QObject(parent)
{

}

void QQuickTooltip::showText(QQuickItem *item, const QPointF &pos, const QString &str)
{
    if (!item || !item->window())
        return;
#ifdef QT_WIDGETS_LIB
    if (QGuiApplicationPrivate::platformIntegration()->
            hasCapability(QPlatformIntegration::MultipleWindows) &&
        QCoreApplication::instance()->inherits("QApplication")) {
        QPoint quickWidgetOffsetInTlw;
        QWindow *renderWindow = QQuickRenderControl::renderWindowFor(item->window(), &quickWidgetOffsetInTlw);
        QWindow *window = renderWindow ? renderWindow : item->window();
        const QPoint offsetInQuickWidget = item->mapToScene(pos).toPoint();
        const QPoint mappedPos = window->mapToGlobal(offsetInQuickWidget + quickWidgetOffsetInTlw);
        QToolTip::showText(mappedPos, str);
    }
#else
    Q_UNUSED(item);
    Q_UNUSED(pos);
    Q_UNUSED(str);
#endif
}

void QQuickTooltip::hideText()
{
#ifdef QT_WIDGETS_LIB
    QToolTip::hideText();
#endif
}

QT_END_NAMESPACE
