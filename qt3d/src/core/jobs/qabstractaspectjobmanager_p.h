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

#ifndef QABSTRACTASPECTJOBMANAGER_P_H
#define QABSTRACTASPECTJOBMANAGER_P_H

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

#include <QObject>

#include <Qt3DCore/qaspectjob.h>

QT_BEGIN_NAMESPACE

namespace Qt3DCore {

class QT3DCORESHARED_EXPORT QAbstractAspectJobManager : public QObject
{
    Q_OBJECT
public:
    explicit QAbstractAspectJobManager(QObject *p = Q_NULLPTR);

    virtual void initialize() {}
    virtual void enqueueJobs(const QVector<QAspectJobPtr> &jobQueue) = 0;
    virtual void waitForAllJobs() = 0;

    // Callback signature for running SynchronizedJobs
    typedef void (*JobFunction)(void *);
    virtual void waitForPerThreadFunction(JobFunction func, void *arg) = 0;
};

} // namespace Qt3DCore

QT_END_NAMESPACE

#endif // QABSTRACTASPECTJOBMANAGER_P_H
