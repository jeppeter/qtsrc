/****************************************************************************
**
** Copyright (C) 2013 Centria research and development
** Contact: http://www.qt.io/licensing/
**
** This file is part of the QtNfc module of the Qt Toolkit.
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

#ifndef QNEARFIELDTARGET_ANDROID_P_H
#define QNEARFIELDTARGET_ANDROID_P_H

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

#include "android/androidjninfc_p.h"
#include "qnearfieldtarget.h"
#include "qnearfieldtarget_p.h"
#include "qndefmessage.h"
#include "qlist.h"
#include "qstringlist.h"
#include <QTimer>

#include <QtAndroidExtras/QAndroidJniObject>
#include <QtAndroidExtras/QAndroidJniEnvironment>

QT_BEGIN_NAMESPACE

class NearFieldTarget : public QNearFieldTarget
{
    Q_OBJECT
public:
    NearFieldTarget(QAndroidJniObject intent,
                    const QByteArray uid,
                    QObject *parent = 0);
    virtual ~NearFieldTarget();
    virtual QByteArray uid() const;
    virtual Type type() const;
    virtual AccessMethods accessMethods() const;
    virtual bool hasNdefMessage();
    virtual RequestId readNdefMessages();
    virtual RequestId sendCommand(const QByteArray &command);
    virtual RequestId sendCommands(const QList<QByteArray> &commands);
    virtual RequestId writeNdefMessages(const QList<QNdefMessage> &messages);
    void setIntent(QAndroidJniObject intent);

signals:
    void targetDestroyed(const QByteArray &tagId);
    void targetLost(QNearFieldTarget *target);
    void ndefMessageRead(const QNdefMessage &message, const QNearFieldTarget::RequestId &id);

protected slots:
    void checkIsTargetLost();

protected:
    void releaseIntent();
    void updateTechList();
    void updateType();
    Type getTagType() const;
    void setupTargetCheckTimer();
    void handleTargetLost();
    QAndroidJniObject getTagTechnology(const QString &tech) const;
    QByteArray jbyteArrayToQByteArray(const jbyteArray &byteArray) const;
    bool catchJavaExceptions(bool verbose = true) const;

protected:
    QAndroidJniObject m_intent;
    QByteArray m_uid;
    QStringList m_techList;
    Type m_type;
    QTimer *m_targetCheckTimer;
};

QT_END_NAMESPACE

#endif // QNEARFIELDTARGET_ANDROID_P_H
