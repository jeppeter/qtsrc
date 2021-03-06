/****************************************************************************
**
** Copyright (C) 2015 Paul Lemire paul.lemire350@gmail.com
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

#include <QtTest/QTest>
#include <Qt3DRender/private/boundingvolumedebug_p.h>
#include <Qt3DRender/qboundingvolumedebug.h>
#include <Qt3DCore/private/qbackendnode_p.h>
#include <Qt3DCore/qscenepropertychange.h>
#include "testpostmanarbiter.h"

class tst_BoundingVolumeDebug : public QObject
{
    Q_OBJECT
private Q_SLOTS:

    void checkPeerPropertyMirroring()
    {
        // GIVEN
        Qt3DRender::Render::BoundingVolumeDebug boundingVolumeDebug;
        Qt3DRender::QBoundingVolumeDebug fbvH;
        fbvH.setRecursive(true);

        // WHEN
        boundingVolumeDebug.setPeer(&fbvH);

        // THEN
        QVERIFY(!boundingVolumeDebug.peerUuid().isNull());
        QCOMPARE(boundingVolumeDebug.isRecursive(), true);
    }

    void checkInitialAndCleanedUpState()
    {
        // GIVEN
        Qt3DRender::Render::BoundingVolumeDebug boundingVolumeDebug;

        // THEN
        QVERIFY(boundingVolumeDebug.peerUuid().isNull());
        QCOMPARE(boundingVolumeDebug.isRecursive(), false);
        QCOMPARE(boundingVolumeDebug.radius(), 0.0f);
        QCOMPARE(boundingVolumeDebug.center(), QVector3D());

        // GIVEN
        Qt3DRender::QBoundingVolumeDebug fbvH;
        fbvH.setEnabled(true);

        // WHEN
        boundingVolumeDebug.updateFromPeer(&fbvH);
        boundingVolumeDebug.setRadius(427.0f);
        boundingVolumeDebug.setCenter(QVector3D(454.0f, 383.0f, 355.0f));
        boundingVolumeDebug.cleanup();

        // THEN
        QVERIFY(boundingVolumeDebug.peerUuid().isNull());
        QCOMPARE(boundingVolumeDebug.isRecursive(), false);
        QCOMPARE(boundingVolumeDebug.radius(), 0.0f);
        QCOMPARE(boundingVolumeDebug.center(), QVector3D());
    }

    void checkPropertyChanges()
    {
        // GIVEN
        Qt3DRender::Render::BoundingVolumeDebug boundingVolumeDebug;
        QVERIFY(!boundingVolumeDebug.isRecursive());

        // WHEN
        Qt3DCore::QScenePropertyChangePtr updateChange(new Qt3DCore::QScenePropertyChange(Qt3DCore::NodeUpdated, Qt3DCore::QSceneChange::Node, Qt3DCore::QNodeId()));
        updateChange->setValue(true);
        updateChange->setPropertyName("recursive");
        boundingVolumeDebug.sceneChangeEvent(updateChange);

        // THEN
        QCOMPARE(boundingVolumeDebug.isRecursive(), true);
    }

    void checkBackendPropertyNotifications()
    {
        // GIVEN
        TestArbiter arbiter;
        Qt3DRender::Render::BoundingVolumeDebug boundingVolumeDebug;
        Qt3DCore::QBackendNodePrivate::get(&boundingVolumeDebug)->setArbiter(&arbiter);

        // WHEN
        boundingVolumeDebug.setRadius(1340.0f);

        // THEN
        QCOMPARE(arbiter.events.count(), 1);
        Qt3DCore::QScenePropertyChangePtr change = arbiter.events.first().staticCast<Qt3DCore::QScenePropertyChange>();
        QCOMPARE(change->propertyName(), "radius");
        QCOMPARE(change->value().toFloat(), 1340.0f);

        arbiter.events.clear();

        // WHEN
        boundingVolumeDebug.setRadius(1340.0f);

        // THEN
        QCOMPARE(arbiter.events.count(), 0);


        // WHEN
        boundingVolumeDebug.setCenter(QVector3D(1.0f, 2.0f, 3.0f));

        // THEN
        QCOMPARE(arbiter.events.count(), 1);
        change = arbiter.events.first().staticCast<Qt3DCore::QScenePropertyChange>();
        QCOMPARE(change->propertyName(), "center");
        QCOMPARE(change->value().value<QVector3D>(), QVector3D(1.0f, 2.0f, 3.0f));

        arbiter.events.clear();

        // WHEN
        boundingVolumeDebug.setCenter(QVector3D(1.0f, 2.0f, 3.0f));


        // THEN
        QCOMPARE(arbiter.events.count(), 0);
    }
};


QTEST_APPLESS_MAIN(tst_BoundingVolumeDebug)

#include "tst_boundingvolumedebug.moc"
