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
#include <Qt3DCore/qentity.h>

#include <Qt3DRender/qtechniquefilter.h>
#include <Qt3DRender/qparameter.h>
#include <Qt3DRender/qannotation.h>

#include "testpostmanarbiter.h"

// We need to call QNode::clone which is protected
// So we sublcass QNode instead of QObject
class tst_QTechniqueFilter: public Qt3DCore::QNode
{
    Q_OBJECT
public:
    ~tst_QTechniqueFilter()
    {
        QNode::cleanup();
    }

private Q_SLOTS:

    void checkSaneDefaults()
    {
        QScopedPointer<Qt3DRender::QTechniqueFilter> defaulttechniqueFilter(new Qt3DRender::QTechniqueFilter);

        QCOMPARE(defaulttechniqueFilter->criteria().count(), 0);
        QCOMPARE(defaulttechniqueFilter->parameters().count(), 0);
    }

    void checkCloning_data()
    {
        QTest::addColumn<Qt3DRender::QTechniqueFilter *>("techniqueFilter");
        QTest::addColumn<QList<Qt3DRender::QParameter *> >("parameters");
        QTest::addColumn<QList<Qt3DRender::QAnnotation *> >("annotations");

        Qt3DRender::QTechniqueFilter *defaultConstructed = new Qt3DRender::QTechniqueFilter();
        QTest::newRow("defaultConstructed") << defaultConstructed << QList<Qt3DRender::QParameter *>() << QList<Qt3DRender::QAnnotation *>();

        Qt3DRender::QTechniqueFilter *techniqueFilterWithParams = new Qt3DRender::QTechniqueFilter();
        Qt3DRender::QParameter *parameter1 = new Qt3DRender::QParameter(QStringLiteral("displacement"), 454.0f);
        Qt3DRender::QParameter *parameter2 = new Qt3DRender::QParameter(QStringLiteral("torque"), 650);
        QList<Qt3DRender::QParameter *> params1 = QList<Qt3DRender::QParameter *>() << parameter1 << parameter2;
        techniqueFilterWithParams->addParameter(parameter1);
        techniqueFilterWithParams->addParameter(parameter2);
        QTest::newRow("techniqueFilterWithParams") << techniqueFilterWithParams << params1 << QList<Qt3DRender::QAnnotation *>();

        Qt3DRender::QTechniqueFilter *techniqueFilterWithAnnotations = new Qt3DRender::QTechniqueFilter();
        Qt3DRender::QAnnotation *annotation1 = new Qt3DRender::QAnnotation();
        Qt3DRender::QAnnotation *annotation2 = new Qt3DRender::QAnnotation();
        annotation1->setName(QStringLiteral("hasSuperCharger"));
        annotation1->setValue(true);
        annotation1->setName(QStringLiteral("hasNitroKit"));
        annotation1->setValue(false);
        QList<Qt3DRender::QAnnotation *> annotations1 = QList<Qt3DRender::QAnnotation *>() << annotation1 << annotation2;
        techniqueFilterWithAnnotations->addRequirement(annotation1);
        techniqueFilterWithAnnotations->addRequirement(annotation2);
        QTest::newRow("techniqueFilterWithAnnotations") << techniqueFilterWithAnnotations << QList<Qt3DRender::QParameter *>() << annotations1;

        Qt3DRender::QTechniqueFilter *techniqueFilterWithParamsAndAnnotations = new Qt3DRender::QTechniqueFilter();
        Qt3DRender::QParameter *parameter3 = new Qt3DRender::QParameter(QStringLiteral("displacement"), 383.0f);
        Qt3DRender::QParameter *parameter4 = new Qt3DRender::QParameter(QStringLiteral("torque"), 555);
        Qt3DRender::QAnnotation *annotation3 = new Qt3DRender::QAnnotation();
        Qt3DRender::QAnnotation *annotation4 = new Qt3DRender::QAnnotation();
        annotation3->setName(QStringLiteral("hasSuperCharger"));
        annotation3->setValue(false);
        annotation4->setName(QStringLiteral("hasNitroKit"));
        annotation4->setValue(true);
        QList<Qt3DRender::QParameter *> params2 = QList<Qt3DRender::QParameter *>() << parameter3 << parameter4;
        QList<Qt3DRender::QAnnotation *> annotations2 = QList<Qt3DRender::QAnnotation *>() << annotation3 << annotation4;
        techniqueFilterWithParamsAndAnnotations->addParameter(parameter3);
        techniqueFilterWithParamsAndAnnotations->addParameter(parameter4);
        techniqueFilterWithParamsAndAnnotations->addRequirement(annotation3);
        techniqueFilterWithParamsAndAnnotations->addRequirement(annotation4);
        QTest::newRow("techniqueFilterWithParamsAndAnnotations") << techniqueFilterWithParamsAndAnnotations << params2 << annotations2;
    }

    void checkCloning()
    {
        // GIVEN
        QFETCH(Qt3DRender::QTechniqueFilter*, techniqueFilter);
        QFETCH(QList<Qt3DRender::QParameter *>, parameters);
        QFETCH(QList<Qt3DRender::QAnnotation *>, annotations);

        // THEN
        QCOMPARE(techniqueFilter->parameters(), parameters);
        QCOMPARE(techniqueFilter->criteria(), annotations);

        // WHEN
        Qt3DRender::QTechniqueFilter *clone = static_cast<Qt3DRender::QTechniqueFilter *>(QNode::clone(techniqueFilter));

        // THEN
        QVERIFY(clone != Q_NULLPTR);
        QCOMPARE(techniqueFilter->id(), clone->id());

        QCOMPARE(techniqueFilter->criteria().count(), clone->criteria().count());
        QCOMPARE(techniqueFilter->parameters().count(), clone->parameters().count());

        for (int i = 0, m = parameters.count(); i < m; ++i) {
            Qt3DRender::QParameter *pClone = clone->parameters().at(i);
            Qt3DRender::QParameter *pOrig = parameters.at(i);
            QCOMPARE(pOrig->id(),pClone->id());
            QCOMPARE(pOrig->name(), pClone->name());
            QCOMPARE(pOrig->value(), pClone->value());
            QVERIFY(pClone->parent() == clone);
            QVERIFY(pOrig->parent() == techniqueFilter);
        }

        for (int i = 0, m = annotations.count(); i < m; ++i) {
            Qt3DRender::QAnnotation *aClone = clone->criteria().at(i);
            Qt3DRender::QAnnotation *aOrig = annotations.at(i);
            QCOMPARE(aOrig->id(),aClone->id());
            QCOMPARE(aOrig->name(), aClone->name());
            QCOMPARE(aOrig->value(), aClone->value());
            QVERIFY(aClone->parent() == clone);
            QVERIFY(aOrig->parent() == techniqueFilter);
        }

        delete techniqueFilter;
        delete clone;
    }

    void checkPropertyUpdates()
    {
        // GIVEN
        QScopedPointer<Qt3DRender::QTechniqueFilter> techniqueFilter(new Qt3DRender::QTechniqueFilter());
        TestArbiter arbiter(techniqueFilter.data());

        // WHEN
        Qt3DRender::QParameter *param1 = new Qt3DRender::QParameter();
        techniqueFilter->addParameter(param1);
        QCoreApplication::processEvents();

        // THEN
        QCOMPARE(arbiter.events.size(), 1);
        Qt3DCore::QScenePropertyChangePtr change = arbiter.events.first().staticCast<Qt3DCore::QScenePropertyChange>();
        QCOMPARE(change->propertyName(), "parameter");
        QCOMPARE(change->subjectId(),techniqueFilter->id());
        QCOMPARE(change->value().value<Qt3DCore::QNodeId>(), param1->id());
        QCOMPARE(change->type(), Qt3DCore::NodeAdded);

        arbiter.events.clear();

        // WHEN
        techniqueFilter->addParameter(param1);
        QCoreApplication::processEvents();

        // THEN
        QCOMPARE(arbiter.events.size(), 0);

        // WHEN
        techniqueFilter->removeParameter(param1);
        QCoreApplication::processEvents();

        // THEN
        QCOMPARE(arbiter.events.size(), 1);
        change = arbiter.events.first().staticCast<Qt3DCore::QScenePropertyChange>();
        QCOMPARE(change->propertyName(), "parameter");
        QCOMPARE(change->subjectId(), techniqueFilter->id());
        QCOMPARE(change->value().value<Qt3DCore::QNodeId>(), param1->id());
        QCOMPARE(change->type(), Qt3DCore::NodeRemoved);

        arbiter.events.clear();

        // WHEN
        Qt3DRender::QAnnotation *annotation1 = new Qt3DRender::QAnnotation();
        techniqueFilter->addRequirement(annotation1);
        QCoreApplication::processEvents();

        // THEN
        QCOMPARE(arbiter.events.size(), 1);
        change = arbiter.events.first().staticCast<Qt3DCore::QScenePropertyChange>();
        QCOMPARE(change->propertyName(), "require");
        QCOMPARE(change->subjectId(),techniqueFilter->id());
        QCOMPARE(change->value().value<Qt3DCore::QNodeId>(), annotation1->id());
        QCOMPARE(change->type(), Qt3DCore::NodeAdded);

        arbiter.events.clear();

        // WHEN
        techniqueFilter->addRequirement(annotation1);
        QCoreApplication::processEvents();

        // THEN
        QCOMPARE(arbiter.events.size(), 0);

        // WHEN
        techniqueFilter->removeRequirement(annotation1);
        QCoreApplication::processEvents();

        // THEN
        QCOMPARE(arbiter.events.size(), 1);
        change = arbiter.events.first().staticCast<Qt3DCore::QScenePropertyChange>();
        QCOMPARE(change->propertyName(), "require");
        QCOMPARE(change->subjectId(), techniqueFilter->id());
        QCOMPARE(change->value().value<Qt3DCore::QNodeId>(), annotation1->id());
        QCOMPARE(change->type(), Qt3DCore::NodeRemoved);

        arbiter.events.clear();
    }

protected:
    Qt3DCore::QNode *doClone() const Q_DECL_OVERRIDE
    {
        return Q_NULLPTR;
    }

};

QTEST_MAIN(tst_QTechniqueFilter)

#include "tst_qtechniquefilter.moc"
