/****************************************************************************
**
** Copyright (C) 2014 Klaralvdalens Datakonsult AB (KDAB).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the Qt3D module of the Qt Toolkit.
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

#ifndef QT3DRENDER_RENDER_QUICK_QUICK3DRENDERPASSFILTER_P_H
#define QT3DRENDER_RENDER_QUICK_QUICK3DRENDERPASSFILTER_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists for the convenience
// of other Qt classes.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <Qt3DQuick/private/quick3dnode_p.h>
#include <Qt3DRender/qrenderpassfilter.h>
#include <Qt3DRender/qannotation.h>
#include <Qt3DQuickRender/private/qt3dquickrender_global_p.h>
#include <QQmlListProperty>

QT_BEGIN_NAMESPACE

namespace Qt3DRender {
namespace Render {
namespace Quick {

class QT3DQUICKRENDERSHARED_PRIVATE_EXPORT Quick3DRenderPassFilter : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<Qt3DRender::QAnnotation> includes READ includeList)
    Q_PROPERTY(QQmlListProperty<Qt3DRender::QParameter> parameters READ parameterList)

public:
    explicit Quick3DRenderPassFilter(QObject *parent = 0);

    QQmlListProperty<QAnnotation> includeList();
    QQmlListProperty<QParameter> parameterList();

    inline QRenderPassFilter *parentRenderPassFilter() const { return qobject_cast<Qt3DRender::QRenderPassFilter*>(parent()); }

private:
    static void appendInclude(QQmlListProperty<QAnnotation> *list, QAnnotation *criterion);
    static QAnnotation *includeAt(QQmlListProperty<QAnnotation> *list, int index);
    static int includesCount(QQmlListProperty<QAnnotation> *list);
    static void clearIncludes(QQmlListProperty<QAnnotation> *list);

    static void appendParameter(QQmlListProperty<QParameter> *list, QParameter *param);
    static QParameter *parameterAt(QQmlListProperty<QParameter> *list, int index);
    static int parametersCount(QQmlListProperty<QParameter> *list);
    static void clearParameterList(QQmlListProperty<QParameter> *list);
};

} // namespace Quick
} // namespace Render
} // namespace Qt3DRender

QT_END_NAMESPACE

#endif // QT3DRENDER_RENDER_QUICK_QUICK3DRENDERPASSFILTER_P_H
