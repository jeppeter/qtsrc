/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick 2.2
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.2
import io.qt.example 1.0

SettingsForm {
    id: form
    anchors.fill: parent

    function readData() {
        CustomerModel.selection.forEach(function (rowIndex) {
            form.firstName.text = CustomerModel.get(rowIndex).firstName
            form.lastName.text = CustomerModel.get(rowIndex).lastName
            form.customerId.text = CustomerModel.get(rowIndex).customerId
            form.email.text = CustomerModel.get(rowIndex).email
            form.address.text = CustomerModel.get(rowIndex).address
            form.phoneNumber.text = CustomerModel.get(rowIndex).phoneNumber
            form.zipCode.text = CustomerModel.get(rowIndex).zipCode
            form.city.text = CustomerModel.get(rowIndex).city
            form.title.currentIndex = form.title.find(CustomerModel.get(rowIndex).title)
        })

        save.enabled = true
        cancel.enabled = true
        gridLayout.enabled = true
    }

    function writeData() {
        CustomerModel.selection.forEach(function (rowIndex) {
            var notes = CustomerModel.get(rowIndex).notes
            CustomerModel.set(rowIndex, {
                                            firstName: form.firstName.text,
                                            lastName: form.lastName.text,
                                            customerId: form.customerId.text,
                                            email: form.firstName.email,
                                            address: form.lastName.address,
                                            phoneNumber: form.customerId.phoneNumber,
                                            zipCode: form.customerId.zipCode,
                                            city: form.customerId.city,
                                            title: form.title.currentText,
                                            notes: notes
                                        })
        })
    }

    cancel.onClicked: readData()
    save.onClicked: writeData()

    Connections {
        target: CustomerModel.selection
        onSelectionChanged: form.readData()
    }

    Component.onCompleted: readData()
}
