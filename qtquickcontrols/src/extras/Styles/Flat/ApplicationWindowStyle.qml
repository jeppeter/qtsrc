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
import QtQuick.Controls.Styles 1.4 as Base
import QtQuick.Controls.Styles.Flat 1.0

Base.ApplicationWindowStyle {
    panel: Item {
        readonly property alias contentArea: contentArea
        readonly property alias menuBarArea: menuBarArea
        readonly property alias toolBarArea: toolBarArea
        readonly property alias statusBarArea: statusBarArea
        readonly property bool hasToolBar: !!control.toolBar && control.toolBar.Accessible.role === Accessible.ToolBar

        Rectangle {
            id: background
            visible: !styleData.hasColor
            color: FlatStyle.backgroundColor
        }

        Item {
            id: contentArea
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: statusBarArea.top
            anchors.topMargin: toolBarArea.implicitHeight
        }

        Item {
            id: toolBarArea
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            implicitHeight: childrenRect.height
            height: visibleChildren.length > 0 ? implicitHeight : 0

            Loader {
                visible: active
                active: !hasToolBar && !!control.menuBar
                anchors.left: parent.left
                anchors.right: parent.right
                sourceComponent: ToolBar {
                    __menu: proxyMenu.items.length > 1 ? proxyMenu :
                            proxyMenu.items.length === 1 ? proxyMenu.items[0] : null
                }
            }
        }

        Item {
            id: statusBarArea
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            implicitHeight: childrenRect.height
            height: visibleChildren.length > 0 ? implicitHeight : 0
        }

        Item {
            id: menuBarArea
            visible: false

            Menu {
                id: proxyMenu
                __isProxy: true
                items: control.menuBar ? control.menuBar.menus : []
            }

            Binding {
                target: control.toolBar
                property: "__menu"
                value: proxyMenu.items.length > 1 ? proxyMenu :
                       proxyMenu.items.length === 1 ? proxyMenu.items[0] : null
                when: hasToolBar
            }
        }
    }
}
