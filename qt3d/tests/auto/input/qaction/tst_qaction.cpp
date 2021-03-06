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

#include <QtTest/QTest>
#include <Qt3DCore/private/qnode_p.h>
#include <Qt3DCore/private/qscene_p.h>

#include <Qt3DInput/QAction>
#include <Qt3DInput/QActionInput>

#include "testpostmanarbiter.h"

// We need to call QNode::clone which is protected
// So we sublcass QNode instead of QObject
class tst_QAction: public Qt3DCore::QNode
{
    Q_OBJECT
public:
    tst_QAction()
    {
    }

    ~tst_QAction()
    {
        QNode::cleanup();
    }

private Q_SLOTS:

    void checkCloning_data()
    {
        QTest::addColumn<Qt3DInput::QAction *>("action");

        Qt3DInput::QAction *defaultConstructed = new Qt3DInput::QAction();
        QTest::newRow("defaultConstructed") << defaultConstructed;

        Qt3DInput::QAction *namedaction = new Qt3DInput::QAction();
        namedaction->setName(QStringLiteral("fire"));
        QTest::newRow("namedAction") << namedaction;

        Qt3DInput::QAction *namedactionWithInputs = new Qt3DInput::QAction();
        Qt3DInput::QActionInput *actionInput1 = new Qt3DInput::QActionInput();
        Qt3DInput::QActionInput *actionInput2 = new Qt3DInput::QActionInput();
        Qt3DInput::QActionInput *actionInput3 = new Qt3DInput::QActionInput();
        namedactionWithInputs->setName("accelerate");
        namedactionWithInputs->addInput(actionInput1);
        namedactionWithInputs->addInput(actionInput2);
        namedactionWithInputs->addInput(actionInput3);
        QTest::newRow("namedActionWithInputs") << namedactionWithInputs;
    }

    void checkCloning()
    {
        // GIVEN
        QFETCH(Qt3DInput::QAction *, action);

        // WHEN
        Qt3DInput::QAction *clone = static_cast<Qt3DInput::QAction *>(QNode::clone(action));
        QCoreApplication::processEvents();

        // THEN
        QVERIFY(clone != Q_NULLPTR);
        QCOMPARE(action->id(), clone->id());
        QCOMPARE(action->name(), clone->name());
        QCOMPARE(action->inputs().count(), clone->inputs().count());

        for (int i = 0, m = action->inputs().count(); i < m; ++i) {
            QCOMPARE(action->inputs().at(i)->id(), clone->inputs().at(i)->id());
        }

    }

    void checkPropertyUpdates()
    {
        // GIVEN
        QScopedPointer<Qt3DInput::QAction> action(new Qt3DInput::QAction());
        TestArbiter arbiter(action.data());

        // WHEN
        action->setName(QStringLiteral("454"));
        QCoreApplication::processEvents();

        // THEN
        QCOMPARE(arbiter.events.size(), 1);
        Qt3DCore::QScenePropertyChangePtr change = arbiter.events.first().staticCast<Qt3DCore::QScenePropertyChange>();
        QCOMPARE(change->propertyName(), "name");
        QCOMPARE(change->value().toString(), QStringLiteral("454"));
        QCOMPARE(change->type(), Qt3DCore::NodeUpdated);

        arbiter.events.clear();

        // WHEN
        Qt3DInput::QActionInput *input = new Qt3DInput::QActionInput();
        action->addInput(input);
        QCoreApplication::processEvents();

        // THEN
        QCOMPARE(arbiter.events.size(), 1);
        change = arbiter.events.first().staticCast<Qt3DCore::QScenePropertyChange>();
        QCOMPARE(change->propertyName(), "input");
        QCOMPARE(change->value().value<Qt3DCore::QNodeId>(), input->id());
        QCOMPARE(change->type(), Qt3DCore::NodeAdded);

        arbiter.events.clear();

        // WHEN
        action->removeInput(input);
        QCoreApplication::processEvents();

        // THEN
        QCOMPARE(arbiter.events.size(), 1);
        change = arbiter.events.first().staticCast<Qt3DCore::QScenePropertyChange>();
        QCOMPARE(change->propertyName(), "input");
        QCOMPARE(change->value().value<Qt3DCore::QNodeId>(), input->id());
        QCOMPARE(change->type(), Qt3DCore::NodeRemoved);

        arbiter.events.clear();
    }

protected:
    Qt3DCore::QNode *doClone() const Q_DECL_OVERRIDE
    {
        return Q_NULLPTR;
    }

};

QTEST_MAIN(tst_QAction)

#include "tst_qaction.moc"
