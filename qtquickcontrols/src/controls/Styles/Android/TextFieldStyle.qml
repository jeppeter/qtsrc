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

import QtQuick 2.4
import QtQuick.Window 2.2
import QtQuick.Controls 1.2
import QtQuick.Controls.Private 1.0
import QtQuick.Controls.Styles.Android 1.0
import "drawables"

Style {
    readonly property TextField control: __control

    property int renderType: Text.QtRendering

    property Component panel: Item {
        id: panel

        readonly property var styleDef: AndroidStyle.styleDef.editTextStyle

        readonly property real minWidth: styleDef.View_minWidth || 0
        readonly property real minHeight: styleDef.View_minHeight || 0
        readonly property real labelWidth: Math.max(label.implicitWidth, metrics.width) + bg.padding.left + bg.padding.right
        readonly property real labelHeight: label.implicitHeight + bg.padding.top + bg.padding.bottom

        implicitWidth: Math.max(minWidth, Math.max(bg.implicitWidth, labelWidth))
        implicitHeight: Math.max(minHeight, Math.max(bg.implicitHeight, labelHeight))

        DrawableLoader {
            id: bg
            anchors.fill: parent
            focused: control.activeFocus
            window_focused: focused && control.Window.active
            styleDef: panel.styleDef.View_background
        }

        readonly property real topMargin: bg.padding.top
        readonly property real leftMargin: bg.padding.left
        readonly property real rightMargin: bg.padding.right
        readonly property real bottomMargin: bg.padding.bottom

        readonly property alias font: label.font
        readonly property alias textColor: label.color
        readonly property alias placeholderTextColor: label.hintColor
        readonly property alias selectionColor: label.selectionColor
        readonly property color selectedTextColor: label.selectedTextColor

        TextMetrics {
            id: metrics
            text: "12345678901234567890"
        }

        LabelStyle {
            id: label
            visible: false
            text: control.text || control.placeholderText
            focused: control.activeFocus
            window_focused: focused && control.Window.active
            styleDef: panel.styleDef
        }
    }

    property Component __selectionHandle: DrawableLoader {
        styleDef: AndroidStyle.styleDef.textViewStyle.TextView_textSelectHandleLeft
        x: -width / 4 * 3
        y: styleData.lineHeight
    }

    property Component __cursorHandle: CursorHandleStyle { }
}
