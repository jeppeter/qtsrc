/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the QtCore module of the Qt Toolkit.
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

#ifndef QJSONPARSER_P_H
#define QJSONPARSER_P_H

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

#include <qjsondocument.h>
#include <qvarlengtharray.h>

QT_BEGIN_NAMESPACE

namespace QJsonPrivate {

class Parser
{
public:
    Parser(const char *json, int length);

    QJsonDocument parse(QJsonParseError *error);

    class ParsedObject
    {
    public:
        ParsedObject(Parser *p, int pos) : parser(p), objectPosition(pos) {
            offsets.reserve(64);
        }
        void insert(uint offset);

        Parser *parser;
        int objectPosition;
        QVector<uint> offsets;

        inline QJsonPrivate::Entry *entryAt(int i) const {
            return reinterpret_cast<QJsonPrivate::Entry *>(parser->data + objectPosition + offsets[i]);
        }
    };


private:
    inline void eatBOM();
    inline bool eatSpace();
    inline char nextToken();

    bool parseObject();
    bool parseArray();
    bool parseMember(int baseOffset);
    bool parseString(bool *latin1);
    bool parseValue(QJsonPrivate::Value *val, int baseOffset);
    bool parseNumber(QJsonPrivate::Value *val, int baseOffset);
    const char *head;
    const char *json;
    const char *end;

    char *data;
    int dataLength;
    int current;
    int nestingLevel;
    QJsonParseError::ParseError lastError;

    inline int reserveSpace(int space) {
        if (current + space >= dataLength) {
            dataLength = 2*dataLength + space;
            char *newData = (char *)realloc(data, dataLength);
            if (!newData) {
                lastError = QJsonParseError::DocumentTooLarge;
                return -1;
            }
            data = newData;
        }
        int pos = current;
        current += space;
        return pos;
    }
};

}

QT_END_NAMESPACE

#endif
