/****************************************************************************
 **
 ** Copyright (C) 2013 Ivan Vizir <define-true-false@yandex.com>
 ** Copyright (C) 2015 The Qt Company Ltd.
 ** Contact: http://www.qt.io/licensing/
 **
 ** This file is part of the QtWinExtras module of the Qt Toolkit.
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

#ifndef QQUICKTASKBARBUTTON_P_H
#define QQUICKTASKBARBUTTON_P_H

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

#include <QQuickItem>
#include <QWinTaskbarButton>
#include <QWinTaskbarProgress>

QT_BEGIN_NAMESPACE

class QVariant;
class QQuickTaskbarButtonPrivate;

class QQuickTaskbarOverlay : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QUrl iconSource READ iconSource WRITE setIconSource NOTIFY iconSourceChanged)
    Q_PROPERTY(QString accessibleDescription READ accessibleDescription WRITE setAccessibleDescription NOTIFY accessibleDescriptionChanged)

public:
    explicit QQuickTaskbarOverlay(QWinTaskbarButton *button, QObject *parent = 0);

    QUrl iconSource() const;
    void setIconSource(const QUrl &iconSource);

    QString accessibleDescription() const;
    void setAccessibleDescription(const QString &description);

Q_SIGNALS:
    void iconSourceChanged();
    void accessibleDescriptionChanged();

private Q_SLOTS:
    void iconLoaded(const QVariant &);

private:
    QUrl m_iconSource;
    QWinTaskbarButton *m_button;
};

class QQuickTaskbarButton : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QQuickTaskbarOverlay *overlay  READ overlay CONSTANT)
    Q_PROPERTY(QWinTaskbarProgress *progress READ progress CONSTANT)

public:
    explicit QQuickTaskbarButton(QQuickItem *parent = 0);
    ~QQuickTaskbarButton();

    QQuickTaskbarOverlay *overlay() const;
    QWinTaskbarProgress *progress() const;

protected:
    void itemChange(ItemChange, const ItemChangeData &) Q_DECL_OVERRIDE;

private:
    QWinTaskbarButton *m_button;
    QQuickTaskbarOverlay *m_overlay;
};

QT_END_NAMESPACE

#endif // QQUICKTASKBARBUTTON_P_H
