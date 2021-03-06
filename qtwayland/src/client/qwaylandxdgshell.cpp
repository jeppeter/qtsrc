/****************************************************************************
**
** Copyright (C) 2014 Eurogiciel, author: <philippe.coval@eurogiciel.fr>
** Contact: http://www.qt.io/licensing/
**
** This file is part of the config.tests of the Qt Toolkit.
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

#include "qwaylandxdgshell_p.h"

#include "qwaylanddisplay_p.h"
#include "qwaylandwindow_p.h"
#include "qwaylandinputdevice_p.h"
#include "qwaylandscreen_p.h"
#include "qwaylandxdgpopup_p.h"
#include "qwaylandxdgsurface_p.h"

#include <QtCore/QDebug>

QT_BEGIN_NAMESPACE

namespace QtWaylandClient {

QWaylandXdgShell::QWaylandXdgShell(struct ::xdg_shell *shell)
    : QtWayland::xdg_shell(shell)
{
}

QWaylandXdgShell::QWaylandXdgShell(struct ::wl_registry *registry, uint32_t id)
    : QtWayland::xdg_shell(registry, id, 1)
{
    use_unstable_version(QtWayland::xdg_shell::version_current);
}

QWaylandXdgShell::~QWaylandXdgShell()
{
    xdg_shell_destroy(object());
}

QWaylandXdgSurface *QWaylandXdgShell::createXdgSurface(QWaylandWindow *window)
{
    return new QWaylandXdgSurface(this, window);
}

QWaylandXdgPopup *QWaylandXdgShell::createXdgPopup(QWaylandWindow *window)
{
    QWaylandWindow *parentWindow = window->transientParent();
    ::wl_surface *parentSurface = parentWindow->object();
    QWaylandInputDevice *inputDevice = window->display()->lastInputDevice();
    ::wl_seat *seat = inputDevice->wl_seat();
    uint serial = inputDevice->serial();
    QPoint position = window->geometry().topLeft();
    int x = position.x() + parentWindow->frameMargins().left();
    int y = position.y() + parentWindow->frameMargins().top();
    return new QWaylandXdgPopup(get_xdg_popup(window->object(), parentSurface, seat, serial, x, y), window);
}

void QWaylandXdgShell::xdg_shell_ping(uint32_t serial)
{
    pong(serial);
}

}

QT_END_NAMESPACE
