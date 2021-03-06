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

import QtQuick 2.2
import QtQuick.Window 2.2
import QtQuick.Controls 1.2
import QtQuick.Controls.Private 1.0
import QtQuick.Controls.Styles.Android 1.0
import "drawables"

Style {
    readonly property ToolBar control: __control

    padding {
        left: 0
        right: 0
        top: AndroidStyle.styleDef.actionBarStyle.View_paddingTop
        bottom: AndroidStyle.styleDef.actionBarStyle.View_paddingBottom
    }

    property Component menuButton: Item {
        readonly property var styleDef: AndroidStyle.styleDef.actionButtonStyle

        readonly property real minWidth: styleDef.View_minWidth || 0
        readonly property real minHeight: styleDef.View_minHeight || 0
        readonly property real paddingStart: styleDef.View_paddingStart || 0
        readonly property real paddingEnd: styleDef.View_paddingEnd || 0

        implicitWidth: Math.max(minWidth, button.implicitWidth)
        implicitHeight: Math.max(minHeight, button.implicitHeight)

        DrawableLoader {
            id: button
            anchors.fill: parent
            pressed: styleData.pressed
            focused: styleData.activeFocus
            window_focused: control.Window.active
            styleDef: parent.styleDef.View_background
        }

        DrawableLoader {
            id: icon
            anchors.centerIn: parent
            pressed: styleData.pressed
            focused: styleData.activeFocus
            window_focused: control.Window.active
            styleDef: AndroidStyle.styleDef.actionOverflowButtonStyle.ImageView_src
        }
    }

    property Component panel: Item {
        id: panel

        readonly property var styleDef: AndroidStyle.styleDef.actionBarStyle

        readonly property real minWidth: styleDef.View_minWidth || 0
        readonly property real minHeight: styleDef.View_minHeight || 0
        readonly property real buttonHeight: AndroidStyle.styleDef.actionButtonStyle.View_minHeight || 0

        implicitWidth: Math.max(minWidth, bg.implicitWidth)
        implicitHeight: Math.max(minHeight, Math.max(buttonHeight, bg.implicitHeight))

        DrawableLoader {
            id: bg
            anchors.fill: parent
            focused: control.activeFocus
            window_focused: focused && control.Window.active
            styleDef: panel.styleDef.ActionBar_backgroundStacked
        }
    }
}
