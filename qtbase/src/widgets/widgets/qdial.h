/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the QtWidgets module of the Qt Toolkit.
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


#ifndef QDIAL_H
#define QDIAL_H

#include <QtWidgets/qabstractslider.h>

QT_BEGIN_NAMESPACE


#ifndef QT_NO_DIAL

class QDialPrivate;
class QStyleOptionSlider;

class Q_WIDGETS_EXPORT QDial: public QAbstractSlider
{
    Q_OBJECT

    Q_PROPERTY(bool wrapping READ wrapping WRITE setWrapping)
    Q_PROPERTY(int notchSize READ notchSize)
    Q_PROPERTY(qreal notchTarget READ notchTarget WRITE setNotchTarget)
    Q_PROPERTY(bool notchesVisible READ notchesVisible WRITE setNotchesVisible)
public:
    explicit QDial(QWidget *parent = Q_NULLPTR);

    ~QDial();

    bool wrapping() const;

    int notchSize() const;

    void setNotchTarget(double target);
    qreal notchTarget() const;
    bool notchesVisible() const;

    QSize sizeHint() const Q_DECL_OVERRIDE;
    QSize minimumSizeHint() const Q_DECL_OVERRIDE;

public Q_SLOTS:
    void setNotchesVisible(bool visible);
    void setWrapping(bool on);

protected:
    bool event(QEvent *e) Q_DECL_OVERRIDE;
    void resizeEvent(QResizeEvent *re) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *pe) Q_DECL_OVERRIDE;

    void mousePressEvent(QMouseEvent *me) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *me) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *me) Q_DECL_OVERRIDE;

    void sliderChange(SliderChange change) Q_DECL_OVERRIDE;
    void initStyleOption(QStyleOptionSlider *option) const;


private:
    Q_DECLARE_PRIVATE(QDial)
    Q_DISABLE_COPY(QDial)
};

#endif  // QT_NO_DIAL

QT_END_NAMESPACE

#endif // QDIAL_H
