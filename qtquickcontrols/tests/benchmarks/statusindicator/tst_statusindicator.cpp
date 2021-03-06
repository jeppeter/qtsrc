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

#include <QtTest/QtTest>
#include <QtQml/QQmlComponent>
#include <QtQml/QQmlEngine>
#include <QtQuick/QQuickItem>
#include <QtQuick/QQuickWindow>

class tst_StatusIndicator: public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void benchmarkCreation_data();
    void benchmarkCreation();
};

void tst_StatusIndicator::benchmarkCreation_data()
{
    QTest::addColumn<bool>("active");

    QTest::newRow("active") << true;
    QTest::newRow("inactive") << false;
}

void tst_StatusIndicator::benchmarkCreation()
{
    QFETCH(bool, active);

    QQuickWindow window;
    window.resize(240, 240);
    window.create();

    QQmlEngine engine;
    // TODO: fix
    QString path = QString::fromLatin1(SRCDIR "/LotsOfIndicators%1.qml").arg(active ? "Active" : "Inactive");
    QQmlComponent component(&engine, QUrl::fromLocalFile(path));
    QVERIFY2(!component.isError(), qPrintable(component.errorString()));
    QVERIFY(component.isReady());
    QBENCHMARK {
        QQuickItem *root = qobject_cast<QQuickItem*>(component.create());
        root->setParentItem(window.contentItem());
        window.grabWindow();
    }
}

QTEST_MAIN(tst_StatusIndicator)

#include "tst_statusindicator.moc"
