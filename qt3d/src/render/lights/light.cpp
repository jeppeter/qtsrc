/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
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

#include "light_p.h"
#include "qlight.h"
#include <Qt3DCore/qscenepropertychange.h>
#include <private/abstractrenderer_p.h>
#include <private/nodemanagers_p.h>
#include <private/qbackendnode_p.h>
#include <private/managers_p.h>

QT_BEGIN_NAMESPACE

using namespace Qt3DCore;

namespace Qt3DRender {
namespace Render {

RenderLightFunctor::RenderLightFunctor(NodeManagers *managers)
    : m_managers(managers)
{
}

Qt3DCore::QBackendNode *RenderLightFunctor::create(Qt3DCore::QNode *frontend, const Qt3DCore::QBackendNodeFactory *factory) const
{
    Light *backend = m_managers->lightManager()->getOrCreateResource(frontend->id());
    backend->setFactory(factory);
    backend->setManagers(m_managers);
    backend->setPeer(frontend);
    return backend;
}

Qt3DCore::QBackendNode *RenderLightFunctor::get(const Qt3DCore::QNodeId &id) const
{
    return m_managers->lightManager()->lookupResource(id);
}

void RenderLightFunctor::destroy(const Qt3DCore::QNodeId &id) const
{
    m_managers->lightManager()->releaseResource(id);
}

} // namespace Render
} // namespace Qt3DRender

QT_END_NAMESPACE
