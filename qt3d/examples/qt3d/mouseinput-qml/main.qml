/****************************************************************************
**
** Copyright (C) 2015 Klaralvdalens Datakonsult AB (KDAB).
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

import Qt3D.Core 2.0
import Qt3D.Render 2.0
import Qt3D.Input 2.0

Entity {
    id: sceneRoot

    Camera {
        id: camera
        projectionType: CameraLens.PerspectiveProjection
        fieldOfView: 45
        aspectRatio: 16/9
        nearPlane : 0.1
        farPlane : 1000.0
        position: Qt.vector3d( 0.0, 0.0, -40.0 )
        upVector: Qt.vector3d( 0.0, 1.0, 0.0 )
        viewCenter: Qt.vector3d( 0.0, 0.0, 0.0 )
    }

    Configuration {
        controlledCamera: camera
    }

    components: FrameGraph {
        ForwardRenderer {
            camera: camera
            clearColor: "black"
        }
    }

    SphereMesh {
        id: sphereMesh
        radius: 3
    }

    Material {
        id: material
        effect : Effect {
        }
    }

    MouseController {
        id: mouseController
    }

    Entity {
        id: sphere1

        property real scaleFactor: 1.0

        property Transform transform: Transform {
            scale: sphere1.scaleFactor
        }

        property MouseInput mouseInput : MouseInput {
            controller: mouseController

            onClicked: {
                //Signal not implemented yet
            }

            onReleased: {
                switch (mouse.button) {
                case Qt.LeftButton:
                    sphere1.scaleFactor += 0.5;
                    break;

                case Qt.RightButton:
                    sphere1.scaleFactor -= 0.5;
                    break;
                }
            }
        }

        components: [sphereMesh, material, transform, mouseInput]
    }
}
