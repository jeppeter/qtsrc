/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the QtBluetooth module of the Qt Toolkit.
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

#ifndef OSXBTDEVICEINQUIRY_P_H
#define OSXBTDEVICEINQUIRY_P_H

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

#include "osxbluetooth_p.h"

#include <QtCore/qglobal.h>

#include <Foundation/Foundation.h>
#include <IOKit/IOReturn.h>

@class QT_MANGLE_NAMESPACE(OSXBTDeviceInquiry);

QT_BEGIN_NAMESPACE

namespace OSXBluetooth {

class DeviceInquiryDelegate {
public:
    typedef QT_MANGLE_NAMESPACE(OSXBTDeviceInquiry) DeviceInquiryObjC;

    virtual ~DeviceInquiryDelegate();

    virtual void inquiryFinished(IOBluetoothDeviceInquiry *inq) = 0;
    virtual void error(IOBluetoothDeviceInquiry *inq, IOReturn error) = 0;
    virtual void deviceFound(IOBluetoothDeviceInquiry *inq, IOBluetoothDevice *device) = 0;
};

}

QT_END_NAMESPACE

@interface QT_MANGLE_NAMESPACE(OSXBTDeviceInquiry) : NSObject<IOBluetoothDeviceInquiryDelegate>
{
    IOBluetoothDeviceInquiry *m_inquiry;
    bool m_active;
    QT_PREPEND_NAMESPACE(OSXBluetooth::DeviceInquiryDelegate) *m_delegate;//C++ "delegate"
}

- (id)initWithDelegate:(QT_PREPEND_NAMESPACE(OSXBluetooth::DeviceInquiryDelegate) *)delegate;
- (void)dealloc;

- (bool)isActive;
- (IOReturn)start;
- (IOReturn)stop;

//Obj-C delegate:
- (void)deviceInquiryComplete:(IOBluetoothDeviceInquiry *)sender
        error:(IOReturn)error aborted:(BOOL)aborted;

- (void)deviceInquiryDeviceFound:(IOBluetoothDeviceInquiry *)sender
        device:(IOBluetoothDevice *)device;

- (void)deviceInquiryStarted:(IOBluetoothDeviceInquiry *)sender;

@end

#endif
