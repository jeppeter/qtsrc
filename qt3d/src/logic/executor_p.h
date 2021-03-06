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

#ifndef QT3DLOGIC_LOGIC_EXECUTOR_P_H
#define QT3DLOGIC_LOGIC_EXECUTOR_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists for the convenience
// of other Qt classes.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QtCore/qobject.h>
#include <QtCore/qcoreevent.h>
#include <Qt3DCore/qnodeid.h>

QT_BEGIN_NAMESPACE

class QSemaphore;

namespace Qt3DCore {
class QScene;
}

namespace Qt3DLogic {
namespace Logic {

class FrameUpdateEvent : public QEvent
{
public:
    FrameUpdateEvent(float dt)
        : QEvent(QEvent::User)
        , m_dt(dt)
    {}

    float deltaTime() const { return m_dt; }

private:
    float m_dt;
};

class Executor : public QObject
{
    Q_OBJECT
public:
    explicit Executor(QObject *parent = 0);

    void setScene(Qt3DCore::QScene *scene) { m_scene = scene; }
    void setSemephore(QSemaphore *semaphore) { m_semaphore = semaphore; }
    void clearQueueAndProceed();

public Q_SLOTS:
    void enqueueLogicFrameUpdates(const QVector<Qt3DCore::QNodeId> &nodeIds);

protected:
    bool event(QEvent *e);
    void processLogicFrameUpdates(float dt);

private:
    QVector<Qt3DCore::QNodeId> m_nodeIds;
    Qt3DCore::QScene *m_scene;
    QSemaphore *m_semaphore;
};

} // namespace Logic
} // namespace Qt3DLogic

QT_END_NAMESPACE

#endif // QT3DLOGIC_LOGIC_EXECUTOR_P_H
