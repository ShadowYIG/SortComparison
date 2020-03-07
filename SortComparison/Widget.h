#pragma once
#include <QtWidgets>
#include "ui_Widget.h"
#include "SortComparison.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget* parent = Q_NULLPTR);
    ~Widget();
private slots:
    void btn_sure_click();
signals:
    void infoSend(QString);

private:
    Ui::Form from;
};
