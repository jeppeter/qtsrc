/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the QtGui module of the Qt Toolkit.
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


#include "cache_p.h"
#include "bridge_p.h"

#ifndef QT_NO_ACCESSIBILITY
#include "cache_adaptor.h"

#define QSPI_OBJECT_PATH_CACHE "/org/a11y/atspi/cache"

QT_BEGIN_NAMESPACE

/*!
    \class QSpiDBusCache
    \internal
    \brief This class is responsible for the AT-SPI cache interface.

    The idea behind the cache is that starting an application would
    result in many dbus calls. The way GTK/Gail/ATK work is that
    they create accessibles for all objects on startup.
    In order to avoid querying all the objects individually via DBus
    they get sent by using the GetItems call of the cache.

    Additionally the AddAccessible and RemoveAccessible signals
    are responsible for adding/removing objects from the cache.

    Currently the Qt bridge chooses to ignore these.
*/

QSpiDBusCache::QSpiDBusCache(QDBusConnection c, QObject* parent)
    : QObject(parent)
{
    new CacheAdaptor(this);
    c.registerObject(QLatin1String(QSPI_OBJECT_PATH_CACHE), this, QDBusConnection::ExportAdaptors);
}

void QSpiDBusCache::emitAddAccessible(const QSpiAccessibleCacheItem& item)
{
    emit AddAccessible(item);
}

void QSpiDBusCache::emitRemoveAccessible(const QSpiObjectReference& item)
{
    emit RemoveAccessible(item);
}

QSpiAccessibleCacheArray QSpiDBusCache::GetItems()
{
    return QSpiAccessibleCacheArray();
}

QT_END_NAMESPACE
#endif //QT_NO_ACCESSIBILITY
