/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Designer of the Qt Toolkit.
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

#ifndef WIDGETBOX_H
#define WIDGETBOX_H

#include "widgetbox_global.h"
#include <qdesigner_widgetbox_p.h>

QT_BEGIN_NAMESPACE

class QDesignerFormEditorInterface;
class QDesignerFormWindowInterface;

namespace qdesigner_internal {

class WidgetBoxTreeWidget;

class QT_WIDGETBOX_EXPORT WidgetBox : public QDesignerWidgetBox
{
    Q_OBJECT
public:
    explicit WidgetBox(QDesignerFormEditorInterface *core, QWidget *parent = 0, Qt::WindowFlags flags = 0);
    virtual ~WidgetBox();

    QDesignerFormEditorInterface *core() const;

    int categoryCount() const Q_DECL_OVERRIDE;
    Category category(int cat_idx) const Q_DECL_OVERRIDE;
    void addCategory(const Category &cat) Q_DECL_OVERRIDE;
    void removeCategory(int cat_idx) Q_DECL_OVERRIDE;

    int widgetCount(int cat_idx) const Q_DECL_OVERRIDE;
    Widget widget(int cat_idx, int wgt_idx) const Q_DECL_OVERRIDE;
    void addWidget(int cat_idx, const Widget &wgt) Q_DECL_OVERRIDE;
    void removeWidget(int cat_idx, int wgt_idx) Q_DECL_OVERRIDE;

    void dropWidgets(const QList<QDesignerDnDItemInterface*> &item_list, const QPoint &global_mouse_pos) Q_DECL_OVERRIDE;

    void setFileName(const QString &file_name) Q_DECL_OVERRIDE;
    QString fileName() const Q_DECL_OVERRIDE;
    bool load() Q_DECL_OVERRIDE;
    bool save() Q_DECL_OVERRIDE;

    bool loadContents(const QString &contents) Q_DECL_OVERRIDE;
    QIcon iconForWidget(const QString &className, const QString &category = QString()) const Q_DECL_OVERRIDE;

protected:
    void dragEnterEvent (QDragEnterEvent * event) Q_DECL_OVERRIDE;
    void dragMoveEvent(QDragMoveEvent * event) Q_DECL_OVERRIDE;
    void dropEvent (QDropEvent * event) Q_DECL_OVERRIDE;

private slots:
    void handleMousePress(const QString &name, const QString &xml, const QPoint &global_mouse_pos);

private:
    QDesignerFormEditorInterface *m_core;
    WidgetBoxTreeWidget *m_view;
};

}  // namespace qdesigner_internal

QT_END_NAMESPACE

#endif // WIDGETBOX_H
