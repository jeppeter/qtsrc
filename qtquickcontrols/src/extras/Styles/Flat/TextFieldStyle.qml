/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Quick Extras module of the Qt Toolkit.
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
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2 as Base
import QtQuick.Controls.Styles.Flat 1.0
import QtQuick.Controls.Private 1.0

Base.TextFieldStyle {
    font.family: FlatStyle.fontFamily

    textColor: !control.enabled ? FlatStyle.mediumFrameColor : FlatStyle.defaultTextColor
    placeholderTextColor: FlatStyle.mediumFrameColor
    selectionColor: FlatStyle.textSelectionColor
    selectedTextColor: FlatStyle.defaultTextColor
    renderType: FlatStyle.__renderType

    padding {
        top: 0
        left: Math.round(FlatStyle.scaleFactor * 10)
        right: Math.round(FlatStyle.scaleFactor * 10)
        bottom: 0
    }

    background: Rectangle {
        implicitWidth: Math.round(150 * FlatStyle.scaleFactor)
        implicitHeight: Math.max(Math.round(26 * FlatStyle.scaleFactor), Math.round(control.__contentHeight * 1.2))
        radius: FlatStyle.radius
        border.width: (control.activeFocus ? FlatStyle.twoPixels : enabled ? FlatStyle.onePixel : 0)
        border.color: control.activeFocus ? FlatStyle.highlightColor : FlatStyle.darkFrameColor
        color: enabled ? FlatStyle.backgroundColor : FlatStyle.disabledColor
        opacity: enabled ? 1.0 : 0.15
    }

    __selectionHandle: SelectionHandleStyle { }
    __cursorHandle: CursorHandleStyle { }
}
