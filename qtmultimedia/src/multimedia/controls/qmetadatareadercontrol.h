/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Toolkit.
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

#ifndef QMETADATAREADERCONTROL_H
#define QMETADATAREADERCONTROL_H

#include <QtMultimedia/qmediacontrol.h>
#include <QtMultimedia/qmediaobject.h>

#include <QtMultimedia/qmediaresource.h>

#include <QtMultimedia/qtmultimediadefs.h>
#include <QtMultimedia/qmultimedia.h>

QT_BEGIN_NAMESPACE

// Required for QDoc workaround
class QString;

class Q_MULTIMEDIA_EXPORT QMetaDataReaderControl : public QMediaControl
{
    Q_OBJECT
public:
    ~QMetaDataReaderControl();

    virtual bool isMetaDataAvailable() const = 0;

    virtual QVariant metaData(const QString &key) const = 0;
    virtual QStringList availableMetaData() const = 0;

Q_SIGNALS:
    void metaDataChanged();
    void metaDataChanged(const QString &key, const QVariant &value);

    void metaDataAvailableChanged(bool available);

protected:
    explicit QMetaDataReaderControl(QObject *parent = Q_NULLPTR);
};

#define QMetaDataReaderControl_iid "org.qt-project.qt.metadatareadercontrol/5.0"
Q_MEDIA_DECLARE_CONTROL(QMetaDataReaderControl, QMetaDataReaderControl_iid)

QT_END_NAMESPACE


#endif  // QMETADATAPROVIDER_H
