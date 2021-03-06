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

import QtQuick 2.3
import QtQuick.Controls 1.4
import QtQuick.Controls.Private 1.0
import QtQuick.Controls.Styles 1.4 as Base
import QtQuick.Controls.Styles.Flat 1.0
import QtQuick.Extras.Private 1.0
import QtQuick.Extras.Private.CppUtils 1.0

Base.StatusIndicatorStyle {
    color: FlatStyle.focusedTextColor

    indicator: Item {
        implicitWidth: Math.max(12, MathUtils.roundEven(12 * FlatStyle.scaleFactor))
        implicitHeight: MathUtils.roundEven(implicitWidth / 2)

        Rectangle {
            // Math.max because the control could be manually resized to be too small.
            width: Math.max(12, MathUtils.roundEven(parent.width))
            height: MathUtils.roundEven(width / 2)
            radius: Math.max(2, height * 0.2)
            anchors.centerIn: parent
            color: !control.enabled || !control.active ? FlatStyle.disabledColor : control.color
            opacity: control.enabled ? (control.active ? 1 : 0.3) : (control.active ? FlatStyle.disabledOpacity : 0.15)
        }
    }
}
