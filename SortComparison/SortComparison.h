#pragma once
#pragma execution_character_set("utf-8")
#include <QtWidgets/QMainWindow>
#include "ui_SortComparison.h"
#include "Widget.h"

class SortComparison : public QMainWindow
{
    Q_OBJECT

public:
    SortComparison(QWidget *parent = Q_NULLPTR);
    QLabel* state_label;
private slots:
    void btn_sort_click();
    void btn_rand_click();
    void btn_com_click();
    void btn_export_click();
    void btn_clean_click();
    void infoRecv(QString);


private:
    Ui::SortComparisonClass ui;
    
};
