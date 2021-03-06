/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the tools applications of the Qt Toolkit.
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

/*
  qmlcodeparser.h
*/

#ifndef QMLCODEPARSER_H
#define QMLCODEPARSER_H

#include "codeparser.h"

#include <qset.h>
#ifndef QT_NO_DECLARATIVE
#include <private/qqmljsengine_p.h>
#include <private/qqmljslexer_p.h>
#include <private/qqmljsparser_p.h>
#endif

QT_BEGIN_NAMESPACE

class Config;
class Node;
class QString;

class QmlCodeParser : public CodeParser
{
    Q_DECLARE_TR_FUNCTIONS(QDoc::QmlCodeParser)

public:
    QmlCodeParser();
    virtual ~QmlCodeParser();

    virtual void initializeParser(const Config& config) Q_DECL_OVERRIDE;
    virtual void terminateParser() Q_DECL_OVERRIDE;
    virtual QString language() Q_DECL_OVERRIDE;
    virtual QStringList sourceFileNameFilter() Q_DECL_OVERRIDE;
    virtual void parseSourceFile(const Location& location, const QString& filePath) Q_DECL_OVERRIDE;
    virtual void doneParsingSourceFiles() Q_DECL_OVERRIDE;

#ifndef QT_NO_DECLARATIVE
    /* Copied from src/declarative/qml/qdeclarativescriptparser.cpp */
    void extractPragmas(QString &script);
#endif

protected:
    const QSet<QString>& topicCommands();
    const QSet<QString>& otherMetaCommands();

private:
#ifndef QT_NO_DECLARATIVE
    QQmlJS::Engine engine;
    QQmlJS::Lexer *lexer;
    QQmlJS::Parser *parser;
#endif
};

QT_END_NAMESPACE

#endif
