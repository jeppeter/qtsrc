/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the QtCore module of the Qt Toolkit.
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

#ifndef QSTATE_P_H
#define QSTATE_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include "qstate.h"
#include "private/qabstractstate_p.h"

#include <QtCore/qlist.h>
#include <QtCore/qbytearray.h>
#include <QtCore/qpointer.h>
#include <QtCore/qvariant.h>

#ifndef QT_NO_STATEMACHINE

QT_BEGIN_NAMESPACE

#ifndef QT_NO_PROPERTIES

struct QPropertyAssignment
{
    QPropertyAssignment()
        : object(0), explicitlySet(true) {}
    QPropertyAssignment(QObject *o, const QByteArray &n,
                        const QVariant &v, bool es = true)
        : object(o), propertyName(n), value(v), explicitlySet(es)
        {}

    bool objectDeleted() const { return !object; }
    void write() const { Q_ASSERT(object != 0); object->setProperty(propertyName, value); }
    bool hasTarget(QObject *o, const QByteArray &pn) const
    { return object == o && propertyName == pn; }

    QPointer<QObject> object;
    QByteArray propertyName;
    QVariant value;
    bool explicitlySet; // false means the property is being restored to its old value
};
Q_DECLARE_TYPEINFO(QPropertyAssignment, Q_MOVABLE_TYPE);

#endif // QT_NO_PROPERTIES

class QAbstractTransition;
class QHistoryState;

class QState;
class Q_CORE_EXPORT QStatePrivate : public QAbstractStatePrivate
{
    Q_DECLARE_PUBLIC(QState)
public:
    QStatePrivate();
    ~QStatePrivate();

    static QStatePrivate *get(QState *q) { return q ? q->d_func() : 0; }
    static const QStatePrivate *get(const QState *q) { return q? q->d_func() : 0; }

    QList<QAbstractState*> childStates() const;
    QList<QHistoryState*> historyStates() const;
    QList<QAbstractTransition*> transitions() const;

    void emitFinished();
    void emitPropertiesAssigned();

    QAbstractState *errorState;
    QAbstractState *initialState;
    QState::ChildMode childMode;
    mutable bool childStatesListNeedsRefresh;
    mutable bool transitionsListNeedsRefresh;
    mutable QList<QAbstractState*> childStatesList;
    mutable QList<QAbstractTransition*> transitionsList;

#ifndef QT_NO_PROPERTIES
    QVector<QPropertyAssignment> propertyAssignments;
#endif
};

QT_END_NAMESPACE

#endif // QT_NO_STATEMACHINE

#endif
