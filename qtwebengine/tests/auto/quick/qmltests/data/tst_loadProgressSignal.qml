/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtWebEngine module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL-EXCEPT$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick 2.0
import QtTest 1.0
import QtWebEngine 1.2

TestWebEngineView {
    id: webEngineView
    width: 400
    height: 300

    SignalSpy {
        id: spyProgress
        target: webEngineView
        signalName: "loadProgressChanged"
    }

    TestCase {
        name: "WebEngineViewLoadProgressSignal"

        function test_loadProgressSignal() {
            compare(spyProgress.count, 0)
            compare(webEngineView.loadProgress, 0)
            webEngineView.url = Qt.resolvedUrl("test1.html")
            spyProgress.wait()
            verify(webEngineView.loadProgress > -1 && webEngineView.loadProgress < 101)
            if (webEngineView.loadProgress > 0 && webEngineView.loadProgress < 100) {
                verify(webEngineView.waitForLoadSucceeded())
                spyProgress.wait()
                compare(webEngineView.loadProgress, 100)
            }
        }
    }
}
