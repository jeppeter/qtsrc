/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the QtLocation module of the Qt Toolkit.
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

#ifndef QDECLARATIVECONTACTDETAIL_P_H
#define QDECLARATIVECONTACTDETAIL_P_H

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

#include <QtCore/QObject>
#include <QtLocation/QPlaceContactDetail>
#include <QtQml/QQmlPropertyMap>
#include <QtQml/qqml.h>

QT_BEGIN_NAMESPACE

class QDeclarativeContactDetails : public QQmlPropertyMap
{
    Q_OBJECT

public:
    explicit QDeclarativeContactDetails(QObject *parent = 0);
    virtual QVariant updateValue(const QString &key, const QVariant &input);
};

class QDeclarativeContactDetail : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QPlaceContactDetail contactDetail READ contactDetail WRITE setContactDetail)
    Q_PROPERTY(QString label READ label WRITE setLabel NOTIFY labelChanged)
    Q_PROPERTY(QString value READ value WRITE setValue NOTIFY valueChanged)

public:
    explicit QDeclarativeContactDetail(QObject *parent = 0);
    explicit QDeclarativeContactDetail(const QPlaceContactDetail &src, QObject *parent = 0);
    ~QDeclarativeContactDetail();

    QPlaceContactDetail contactDetail() const;
    void setContactDetail(const QPlaceContactDetail &contactDetail);

    QString label() const;
    void setLabel(const QString &label);

    QString value() const;
    void setValue(const QString &value);

Q_SIGNALS:
    void labelChanged();
    void valueChanged();

private:
    QPlaceContactDetail m_contactDetail;

};

QT_END_NAMESPACE

QML_DECLARE_TYPE(QDeclarativeContactDetail)

#endif
