/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the QtQuick module of the Qt Toolkit.
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

import QtQuick 2.5
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.3

ApplicationWindow {
    id: window

    width: 520
    height: 340
    visible: true
    title: "Shortcuts - main"

    menuBar: MenuBar {
        Menu {
            title: "File"
            MenuItem {
                text: "New..."
                shortcut: StandardKey.New
                onTriggered: shortcutWindow.createObject(window)
            }
            MenuItem {
                text: "Quit"
                shortcut: StandardKey.Quit
                onTriggered: Qt.quit()
            }
        }
    }

    Loader {
        anchors.margins: 20
        anchors.fill: parent
        sourceComponent: shortcutColumn
    }

    Component {
        id: shortcutWindow

        ApplicationWindow {
            width: 520
            height: 300
            visible: true
            title: "Shortcuts - child"

            Loader {
                anchors.margins: 20
                anchors.fill: parent
                sourceComponent: shortcutColumn
            }

            onClosing: destroy(1)
        }
    }

    Component {
        id: shortcutColumn

        Column {
            spacing: 20

            Repeater {
                model: ["Esc", "Ctrl+C", "Alt+6", "Shift+F12", "Ctrl+X,Ctrl+C"]

                RowLayout {
                    spacing: 20
                    width: parent.width

                    CheckBox {
                        id: checkbox
                        text: modelData
                        checked: index % 2 == 0
                        Layout.fillWidth: true
                    }

                    ComboBox {
                        id: combobox
                        enabled: checkbox.checked
                        model: ["WindowShortcut", "ApplicationShortcut"]
                    }

                    Shortcut {
                        id: shortcut

                        property int activationCount: 0
                        property int ambiguousActivationCount: 0

                        sequence: modelData
                        enabled: checkbox.checked
                        context: combobox.currentText

                        onActivated: { activationCount++; activationTimer.restart() }
                        onActivatedAmbiguously: { ambiguousActivationCount++; ambiguousActivationTimer.restart() }
                    }

                    Timer { id: activationTimer; interval: 500 }
                    Timer { id: ambiguousActivationTimer; interval: 500 }

                    Column {
                        Text {
                            font.pixelSize: 10
                            text: qsTr("Activated: %1").arg(shortcut.activationCount)
                            color: activationTimer.running ? "red" : checkbox.checked ? "black" : "gray"
                        }
                        Text {
                            font.pixelSize: 10
                            text: qsTr("Ambiguously: %1").arg(shortcut.ambiguousActivationCount)
                            color: ambiguousActivationTimer.running ? "red" : checkbox.checked ? "black" : "gray"
                        }
                    }
                }
            }
        }
    }
}

