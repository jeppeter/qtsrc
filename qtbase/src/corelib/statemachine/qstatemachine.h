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

#ifndef QSTATEMACHINE_H
#define QSTATEMACHINE_H

#include <QtCore/qstate.h>

#include <QtCore/qcoreevent.h>
#include <QtCore/qlist.h>
#include <QtCore/qobject.h>
#include <QtCore/qset.h>
#include <QtCore/qvariant.h>

QT_BEGIN_NAMESPACE


#ifndef QT_NO_STATEMACHINE

class QStateMachinePrivate;
class QAbstractAnimation;
class Q_CORE_EXPORT QStateMachine : public QState
{
    Q_OBJECT
    Q_PROPERTY(QString errorString READ errorString)
    Q_PROPERTY(QState::RestorePolicy globalRestorePolicy READ globalRestorePolicy WRITE setGlobalRestorePolicy)
    Q_PROPERTY(bool running READ isRunning WRITE setRunning NOTIFY runningChanged)
#ifndef QT_NO_ANIMATION
    Q_PROPERTY(bool animated READ isAnimated WRITE setAnimated)
#endif
public:
    class Q_CORE_EXPORT SignalEvent : public QEvent
    {
    public:
        SignalEvent(QObject *sender, int signalIndex,
                     const QList<QVariant> &arguments);
        ~SignalEvent();

        inline QObject *sender() const { return m_sender; }
        inline int signalIndex() const { return m_signalIndex; }
        inline QList<QVariant> arguments() const { return m_arguments; }

    private:
        QObject *m_sender;
        int m_signalIndex;
        QList<QVariant> m_arguments;

        friend class QSignalTransitionPrivate;
    };

    class Q_CORE_EXPORT WrappedEvent : public QEvent
    {
    public:
        WrappedEvent(QObject *object, QEvent *event);
        ~WrappedEvent();

        inline QObject *object() const { return m_object; }
        inline QEvent *event() const { return m_event; }

    private:
        QObject *m_object;
        QEvent *m_event;
    };

    enum EventPriority {
        NormalPriority,
        HighPriority
    };

    enum Error {
        NoError,
        NoInitialStateError,
        NoDefaultStateInHistoryStateError,
        NoCommonAncestorForTransitionError
    };

    explicit QStateMachine(QObject *parent = Q_NULLPTR);
    explicit QStateMachine(QState::ChildMode childMode, QObject *parent = Q_NULLPTR);
    ~QStateMachine();

    void addState(QAbstractState *state);
    void removeState(QAbstractState *state);

    Error error() const;
    QString errorString() const;
    void clearError();

    bool isRunning() const;

#ifndef QT_NO_ANIMATION
    bool isAnimated() const;
    void setAnimated(bool enabled);

    void addDefaultAnimation(QAbstractAnimation *animation);
    QList<QAbstractAnimation *> defaultAnimations() const;
    void removeDefaultAnimation(QAbstractAnimation *animation);
#endif // QT_NO_ANIMATION

    QState::RestorePolicy globalRestorePolicy() const;
    void setGlobalRestorePolicy(QState::RestorePolicy restorePolicy);

    void postEvent(QEvent *event, EventPriority priority = NormalPriority);
    int postDelayedEvent(QEvent *event, int delay);
    bool cancelDelayedEvent(int id);

    QSet<QAbstractState*> configuration() const;

#ifndef QT_NO_STATEMACHINE_EVENTFILTER
    bool eventFilter(QObject *watched, QEvent *event) Q_DECL_OVERRIDE;
#endif

public Q_SLOTS:
    void start();
    void stop();
    void setRunning(bool running);

Q_SIGNALS:
    void started(QPrivateSignal);
    void stopped(QPrivateSignal);
    void runningChanged(bool running);


protected:
    void onEntry(QEvent *event) Q_DECL_OVERRIDE;
    void onExit(QEvent *event) Q_DECL_OVERRIDE;

    virtual void beginSelectTransitions(QEvent *event);
    virtual void endSelectTransitions(QEvent *event);

    virtual void beginMicrostep(QEvent *event);
    virtual void endMicrostep(QEvent *event);

    bool event(QEvent *e) Q_DECL_OVERRIDE;

protected:
    QStateMachine(QStateMachinePrivate &dd, QObject *parent);

private:
    Q_DISABLE_COPY(QStateMachine)
    Q_DECLARE_PRIVATE(QStateMachine)
    Q_PRIVATE_SLOT(d_func(), void _q_start())
    Q_PRIVATE_SLOT(d_func(), void _q_process())
#ifndef QT_NO_ANIMATION
    Q_PRIVATE_SLOT(d_func(), void _q_animationFinished())
#endif
    Q_PRIVATE_SLOT(d_func(), void _q_startDelayedEventTimer(int, int))
    Q_PRIVATE_SLOT(d_func(), void _q_killDelayedEventTimer(int, int))
};

#endif //QT_NO_STATEMACHINE

QT_END_NAMESPACE

#endif
