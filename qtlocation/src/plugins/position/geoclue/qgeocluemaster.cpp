/****************************************************************************
**
** Copyright (C) 2013 Jolla Ltd, author: Aaron McCarthy <aaron.mccarthy@jollamobile.com>
** Contact: http://www.qt.io/licensing/
**
** This file is part of the QtPositioning module of the Qt Toolkit.
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

#include "qgeocluemaster.h"

#include <master_interface.h>
#include <geoclue_interface.h>
#include <masterclient_interface.h>

#include <QtCore/QLoggingCategory>

Q_DECLARE_LOGGING_CATEGORY(lcPositioningGeoclue)

QT_BEGIN_NAMESPACE

QGeoclueMaster::QGeoclueMaster(QObject *parent)
:   QObject(parent), m_master(0), m_provider(0), m_client(0)
{
}

QGeoclueMaster::~QGeoclueMaster()
{
    releaseMasterClient();

    delete m_master;
}

bool QGeoclueMaster::hasMasterClient() const
{
    return m_client;
}

bool QGeoclueMaster::createMasterClient(Accuracy::Level accuracyLevel, ResourceFlags resourceFlags)
{
    Q_ASSERT(!m_provider || !m_client);

    if (!m_master) {
        qCDebug(lcPositioningGeoclue) << "creating master interface";
        m_master = new OrgFreedesktopGeoclueMasterInterface(QStringLiteral("org.freedesktop.Geoclue.Master"),
                                                            QStringLiteral("/org/freedesktop/Geoclue/Master"),
                                                            QDBusConnection::sessionBus());
    }

    qCDebug(lcPositioningGeoclue) << "creating client";
    QDBusPendingReply<QDBusObjectPath> client = m_master->Create();
    if (client.isError()) {
        QDBusError e = client.error();
        qCritical("Failed to create Geoclue client interface. Geoclue error: %s",
                  qPrintable(e.errorString(e.type())));
        return false;
    }

    qCDebug(lcPositioningGeoclue) << "Geoclue client path:" << client.value().path();

    m_provider = new OrgFreedesktopGeoclueInterface(QStringLiteral("org.freedesktop.Geoclue.Master"),
                                                    client.value().path(), QDBusConnection::sessionBus());
    m_provider->AddReference();

    m_client = new OrgFreedesktopGeoclueMasterClientInterface(QStringLiteral("org.freedesktop.Geoclue.Master"),
                                                              client.value().path(),
                                                              QDBusConnection::sessionBus());

    connect(m_client, SIGNAL(PositionProviderChanged(QString,QString,QString,QString)),
            this, SIGNAL(positionProviderChanged(QString,QString,QString,QString)));

    QDBusPendingReply<> reply = m_client->SetRequirements(accuracyLevel, 0, true, resourceFlags);
    if (reply.isError()) {
        QDBusError e = reply.error();
        qCritical("Failed to set Geoclue positioning requirements. Geoclue error: %s",
                  qPrintable(e.errorString(e.type())));

        releaseMasterClient();
        return false;
    }

    // Need to create the master position interface even though it will not be used, otherwise
    // GetPositionProvider always returns empty strings.
    reply = m_client->PositionStart();
    if (reply.isError()) {
        QDBusError e = reply.error();
        qCritical("Failed to start positioning. Geoclue error: %s",
                  qPrintable(e.errorString(e.type())));

        releaseMasterClient();
        return false;
    }

    return true;
}

void QGeoclueMaster::releaseMasterClient()
{
    if (m_provider)
        m_provider->RemoveReference();
    delete m_provider;
    m_provider = 0;
    delete m_client;
    m_client = 0;
}

QT_END_NAMESPACE
