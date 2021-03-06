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

#ifndef QDECLARATIVEROUTEMAPITEM_H_
#define QDECLARATIVEROUTEMAPITEM_H_

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

#include "qdeclarativegeomapitembase_p.h"
#include "qdeclarativegeomap_p.h"
#include "qdeclarativepolylinemapitem_p.h"
#include <QPen>
#include <QBrush>

QT_BEGIN_NAMESPACE

class QDeclarativeGeoRoute;

class QDeclarativeRouteMapItem : public QDeclarativePolylineMapItem
{
    Q_OBJECT

    Q_PROPERTY(QDeclarativeGeoRoute *route READ route WRITE setRoute NOTIFY routeChanged)

public:
    explicit QDeclarativeRouteMapItem(QQuickItem *parent = 0);
    ~QDeclarativeRouteMapItem();

    QDeclarativeGeoRoute *route() const;
    void setRoute(QDeclarativeGeoRoute *route);

Q_SIGNALS:
    void routeChanged(const QDeclarativeGeoRoute *route);

private slots:
    void updateRoutePath();

protected:
    void setPath(const QJSValue &value) Q_DECL_OVERRIDE;

private:
    QDeclarativeGeoRoute *route_;
};

QT_END_NAMESPACE

QML_DECLARE_TYPE(QDeclarativeRouteMapItem)

#endif /* QDECLARATIVEROUTEMAPITEM_H_ */
