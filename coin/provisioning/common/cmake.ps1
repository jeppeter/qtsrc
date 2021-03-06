#############################################################################
##
## Copyright (C) 2017 The Qt Company Ltd.
## Contact: http://www.qt.io/licensing/
##
## This file is part of the provisioning scripts of the Qt Toolkit.
##
## $QT_BEGIN_LICENSE:LGPL21$
## Commercial License Usage
## Licensees holding valid commercial Qt licenses may use this file in
## accordance with the commercial license agreement provided with the
## Software or, alternatively, in accordance with the terms contained in
## a written agreement between you and The Qt Company. For licensing terms
## and conditions see http://www.qt.io/terms-conditions. For further
## information use the contact form at http://www.qt.io/contact-us.
##
## GNU Lesser General Public License Usage
## Alternatively, this file may be used under the terms of the GNU Lesser
## General Public License version 2.1 or version 3 as published by the Free
## Software Foundation and appearing in the file LICENSE.LGPLv21 and
## LICENSE.LGPLv3 included in the packaging of this file. Please review the
## following information to ensure the GNU Lesser General Public License
## requirements will be met: https://www.gnu.org/licenses/lgpl.html and
## http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
##
## As a special exception, The Qt Company gives you certain additional
## rights. These rights are described in The Qt Company LGPL Exception
## version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
##
## $QT_END_LICENSE$
##
#############################################################################

. "$PSScriptRoot\helpers.ps1"

$majorminorversion = "3.6"
$version = "3.6.2"

$zip = "c:\users\qt\downloads\cmake-" + $version + "-win32-x86.zip"
$officialurl = "https://cmake.org/files/v" + $majorminorversion + "/cmake-" + $version + "-win32-x86.zip"
$cachedurl = "\\ci-files01-hki.intra.qt.io\provisioning\cmake\cmake-" + $version + "-win32-x86.zip"

Download $officialurl $cachedurl $zip
Verify-Checksum $zip "541F6E7EFD228E46770B8631FFE57097576E4D4E"

Extract-Zip $zip C:
# TODO: Remove line below after all Windows TIER2 VMs are based on vanilla OS
if((Test-Path -Path "C:\CMake" )){
    try {
        Rename-Item -ErrorAction 'Stop' "C:\CMake" C:\CMake_old
    } catch {}
}
$defaultinstallfolder = "C:\cmake-" + $version + "-win32-x86"
Rename-Item $defaultinstallfolder C:\CMake

echo "CMake = $version" >> ~\versions.txt

