/****************************************************************************
**
** Copyright (C) 2013 BogDan Vatra <bogdan@kde.org>
** Contact: http://www.qt.io/licensing/
**
** This file is part of the QtSensors module of the Qt Toolkit.
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

#include "androidmagnetometer.h"

enum AndroidSensorStatus
{
    SENSOR_STATUS_UNRELIABLE = 0,
    SENSOR_STATUS_ACCURACY_LOW = 1,
    SENSOR_STATUS_ACCURACY_MEDIUM = 2,
    SENSOR_STATUS_ACCURACY_HIGH = 3,
};

AndroidMagnetometer::AndroidMagnetometer(AndroidSensors::AndroidSensorType type, QSensor *sensor)
    :AndroidCommonSensor<QMagnetometerReading>(type, sensor)
{}

void AndroidMagnetometer::onAccuracyChanged(jint accuracy)
{
    // Expected range is [0, 3]
    if (accuracy < SENSOR_STATUS_UNRELIABLE || accuracy > SENSOR_STATUS_ACCURACY_HIGH) {
        qWarning("Unable to get sensor accuracy. Unexpected value: %d", accuracy);
        return;
    }

    m_reader.setCalibrationLevel(accuracy / qreal(3.0));
}

void AndroidMagnetometer::onSensorChanged(jlong timestamp, const jfloat *values, uint size)
{
    if (size<3)
        return;
    m_reader.setTimestamp(timestamp/1000);
    // check https://developer.android.com/reference/android/hardware/SensorEvent.html#values
    m_reader.setX(values[0]/1e6);
    m_reader.setY(values[1]/1e6);
    m_reader.setZ(values[2]/1e6);
    newReadingAvailable();
}
