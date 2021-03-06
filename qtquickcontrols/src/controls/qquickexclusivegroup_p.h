/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Quick Controls module of the Qt Toolkit.
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

#ifndef QQUICKEXCLUSIVEGROUP1_H
#define QQUICKEXCLUSIVEGROUP1_H

#include <QtCore/qobject.h>
#include <QtCore/qmetaobject.h>
#include <QtQml/qqmllist.h>

QT_BEGIN_NAMESPACE

class QQuickAction;

class QQuickExclusiveGroup1 : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QObject *current READ current WRITE setCurrent NOTIFY currentChanged)
    Q_PROPERTY(QQmlListProperty<QQuickAction> __actions READ actions)
    Q_CLASSINFO("DefaultProperty", "__actions")

public:
    explicit QQuickExclusiveGroup1(QObject *parent = 0);

    QObject *current() const { return m_current; }
    void setCurrent(QObject * o);

    QQmlListProperty<QQuickAction> actions();

public Q_SLOTS:
    void bindCheckable(QObject *o);
    void unbindCheckable(QObject *o);

Q_SIGNALS:
    void currentChanged();

private Q_SLOTS:
    void updateCurrent();

private:
    static void append_actions(QQmlListProperty<QQuickAction> *list, QQuickAction *action);

    QObject * m_current;
    QMetaMethod m_updateCurrentMethod;
};

QT_END_NAMESPACE

#endif // QQUICKEXCLUSIVEGROUP1_H
