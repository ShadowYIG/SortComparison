#include "SortComparison.h"

#include "Widget.h"
#include <QtCharts/QtCharts>
#include "dataProcessing.h"
#include "SortComparison.h"
#include <vector>
#include <sstream>
#include <QDebug>
string qstr2str(const QString qstr);
QString str2qstr(const string str);
bool AllisNum(string str);
SortComparison::SortComparison(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    ui.tableWidget->setRowCount(1);
    ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui.tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    state_label = new QLabel(this);
    ui.statusBar->addWidget(state_label);
}

void SortComparison::infoRecv(QString sInfo)
{
    ui.text_num->setPlainText(sInfo);
}

void SortComparison::btn_sort_click()
{
    QString qstr = ui.text_num->toPlainText();
    string str = qstr2str(qstr);
    if (str == "") {
        QMessageBox::critical(this, "数据错误", "数据不能为空");
    }
    int code = 1;
    stringstream ss(str);
    vector<int> v_num;
    while (getline(ss, str, ','))
    {
        if (AllisNum(str)) {
            v_num.push_back(atoi(str.c_str()));
        }
        else {
            code = -1;
            break;
        }

        
    }
    if (code != 1) {
        QMessageBox::critical(this, "数据错误", "数据只能为数字且分隔符为英文逗号");
    }
    else {
        datapro mydata(v_num);
        vector<int> res;
        int sort_type = 1;
        int index = 0;
        //1.插入排序，2.希尔排序，3.冒泡排序，4.快速排序， 5. 简单选择排序，6.堆排序，7.归并排序，8.基数排序，9.鸡尾酒排序，10.Bogo排序
        int qtype = ui.com_alg->currentIndex() + 1;
        if (qtype == 10) {
            QMessageBox::StandardButton btn;
            btn = QMessageBox::question(this, "注意", "Bogo排序为随机排序方式，纯属娱乐，建议用10以下的数量尝试，数量过多排序时间可能无穷大，是否继续排序？", QMessageBox::Yes | QMessageBox::No);
            if (btn == QMessageBox::No) {
                return;
            }
        }
        state_label->setText("排序中，请稍后....");
        mydata.numSort(qtype);
        string re = "";
        mydata.getResult(re, ',');
        ui.text_num->setPlainText(str2qstr(re));
        int count = ui.tableWidget->rowCount();
        ui.tableWidget->insertRow(count);
        ui.tableWidget->setItem(count - 1, 0, new QTableWidgetItem(ui.com_alg ->currentText()));
        ui.tableWidget->setItem(count - 1, 1, new QTableWidgetItem(QString::number(v_num.size())));
        //1.插入排序，2.希尔排序，3.冒泡排序，4.快速排序， 5. 简单选择排序，6.堆排序，7.归并排序，8.计数排序，9.桶排序，10.基数排序，11.鸡尾酒排序，12.Bogo排序
        switch (qtype)
        {
        case 1:
            ui.tableWidget->setItem(count - 1, 2, new QTableWidgetItem(QString::number(mydata.getSortTime(0).Insertion / 1000.0, 10, 5)));
            break;
        case 2:
            ui.tableWidget->setItem(count - 1, 2, new QTableWidgetItem(QString::number(mydata.getSortTime(0).Shell / 1000.0, 10, 5)));
            break;
        case 3:
            ui.tableWidget->setItem(count - 1, 2, new QTableWidgetItem(QString::number(mydata.getSortTime(0).Bubble / 1000.0, 10, 5)));
            break;
        case 4:
            ui.tableWidget->setItem(count - 1, 2, new QTableWidgetItem(QString::number(mydata.getSortTime(0).Quick / 1000.0, 10, 5)));
            break;
        case 5:
            ui.tableWidget->setItem(count - 1, 2, new QTableWidgetItem(QString::number(mydata.getSortTime(0).Selection / 1000.0, 10, 5)));
            break;
        case 6:
            ui.tableWidget->setItem(count - 1, 2, new QTableWidgetItem(QString::number(mydata.getSortTime(0).Heap / 1000.0, 10, 5)));
            break;
        case 7:
            ui.tableWidget->setItem(count - 1, 2, new QTableWidgetItem(QString::number(mydata.getSortTime(0).Merge / 1000.0, 10, 5)));
            break;
        case 8:
            ui.tableWidget->setItem(count - 1, 2, new QTableWidgetItem(QString::number(mydata.getSortTime(0).Radix / 1000.0, 10, 5)));
            break;
        case 9:
            ui.tableWidget->setItem(count - 1, 2, new QTableWidgetItem(QString::number(mydata.getSortTime(0).cocktail / 1000.0, 10, 5)));
            break;
        case 10:
            ui.tableWidget->setItem(count - 1, 2, new QTableWidgetItem(QString::number(mydata.getSortTime(0).Bogo / 1000.0, 10, 5)));
            break;
        }
        ui.tableWidget->repaint();
        
    }
    
    
}

void SortComparison::btn_rand_click()
{
    Widget *fr = new Widget;
    connect(fr, SIGNAL(infoSend(QString)), this, SLOT(infoRecv(QString)));
    fr->setWindowModality(Qt::ApplicationModal);
    fr->show();
    
}

void SortComparison::btn_com_click() {
    int count = ui.spin_count->value();
    bool havecheck = false;
    sortcom sortsel = { false };
    vector<int> ve_num;
    datapro dp;
    if (count == 0) {
        QMessageBox::critical(this, "数据错误", "数量不能为空");
        return;
    }
    if (ui.check_Insertion->isChecked()) {
        sortsel.Insertion = true;
        havecheck = true;
    }
    if (ui.check_Shell->isChecked()) {
        sortsel.Shell = true;
        havecheck = true;
    }
    if (ui.check_Bubble->isChecked()) {
        sortsel.Bubble = true;
        havecheck = true;
    }
    if (ui.check_Quick->isChecked()) {
        sortsel.Quick = true;
        havecheck = true;
    }
    if (ui.check_Selection->isChecked()) {
        sortsel.Selection = true;
        havecheck = true;
    }
    if (ui.check_Heap->isChecked()) {
        sortsel.Heap = true;
        havecheck = true;
    }
    if (ui.check_Merge->isChecked()) {
        sortsel.Merge = true;
        havecheck = true;
    }
    if (ui.check_Radix->isChecked()) {
        sortsel.Radix = true;
        havecheck = true;
    }
    if (ui.check_cocktail->isChecked()) {
        sortsel.cocktail = true;
        havecheck = true;
    }
    if (ui.check_bogo->isChecked()) {
        QMessageBox::StandardButton btn;
        btn = QMessageBox::question(this, "注意", "Bogo排序为随机排序方式，纯属娱乐，排序时间可能无穷大，是否继续排序？", QMessageBox::Yes | QMessageBox::No);
        if (btn == QMessageBox::No) {
            ui.check_bogo->setCheckState(Qt::Unchecked);
            return;
        }
        else {
            sortsel.Bogo = true;
            havecheck = true;
        }
        
    }

    state_label->setText("生成中，请稍后.....");
    //ui.statusBar->showMessage(QString::fromStdString("生成中，请稍后....."), 1200);
    dp.getRandNum(count * 2, 0, count, 0, ve_num);
    dp.putNum(ve_num);
    state_label->setText("开始执行乱序排列.....");
    //ui.statusBar->showMessage(QString::fromStdString("开始执行乱序排列....."), 1200);
    dp.sortCompara(sortsel, 0);

    dp.getRandNum(count * 2, 0, count, 1, ve_num);
    dp.putNum(ve_num);
    state_label->setText("开始执行顺序排列.....");
    //ui.statusBar->showMessage(QString::fromStdString("开始执行顺序排列....."), 1200);
    dp.sortCompara(sortsel, 1);

    dp.getRandNum(count * 2, 0, count, -1, ve_num);
    dp.putNum(ve_num);
    state_label->setText("开始执行逆序排列.....");
    //ui.statusBar->showMessage(QString::fromStdString("开始执行逆序排列....."), 1200);
    dp.sortCompara(sortsel, -1);
    state_label->setText("执行完成");
    sorttime seqtime = dp.getSortTime(1);
    sorttime randtime = dp.getSortTime(0);
    sorttime retime = dp.getSortTime(-1);
    QChart *m_chart = new QChart();
    QBarCategoryAxis* axisX = new QBarCategoryAxis;
    QBarSet* set0 = new QBarSet("顺序");
    QBarSet* set1 = new QBarSet("逆序");
    QBarSet* set2 = new QBarSet("随机");
    if (sortsel.Insertion) {
        *set0 << (seqtime.Insertion / 1000.0);
        *set1 << (randtime.Insertion / 1000.0);
        *set2 << (retime.Insertion / 1000.0);
        axisX->append("插入排序");
    }
    if (sortsel.Shell) {
        *set0 << (seqtime.Shell / 1000.0);
        *set1 << (randtime.Shell / 1000.0);
        *set2 << (retime.Shell / 1000.0);
        axisX->append("希尔排序");
    }
    if (sortsel.Bubble) {
        *set0 << (seqtime.Bubble / 1000.0);
        *set1 << (randtime.Bubble / 1000.0);
        *set2 << (retime.Bubble / 1000);
        axisX->append("冒泡排序");
    }
    if (sortsel.Quick) {
        *set0 << (seqtime.Quick / 1000.0);
        *set1 << (randtime.Quick / 1000.0);
        *set2 << (retime.Quick / 1000.0);
        axisX->append("快速排序");
    }
    if (sortsel.Selection) {
        *set0 << (seqtime.Selection / 1000.0);
        *set1 << (randtime.Selection / 1000.0);
        *set2 << (retime.Selection / 1000.0);
        axisX->append("简单选择排序");
    }
    if (sortsel.Heap) {
        *set0 << (seqtime.Heap / 1000.0);
        *set1 << (randtime.Heap / 1000.0);
        *set2 << (retime.Heap / 1000.0);
        axisX->append("堆排序");
    }
    if (sortsel.Merge) {
        *set0 << (seqtime.Merge / 1000.0);
        *set1 << (randtime.Merge / 1000.0);
        *set2 << (retime.Merge / 1000.0);
        axisX->append("归并排序");
    }
    if (sortsel.Radix) {
        *set0 << (seqtime.Radix / 1000.0);
        *set1 << (randtime.Radix / 1000.0);
        *set2 << (retime.Radix / 1000.0);
        axisX->append("基数排序");
    }
    if (sortsel.cocktail) {
        *set0 << (seqtime.cocktail / 1000.0);
        *set1 << (randtime.cocktail / 1000.0);
        *set2 << (retime.cocktail / 1000.0);
        axisX->append("鸡尾酒排序");
    }
    if (sortsel.Bogo) {
        *set0 << (seqtime.Bogo / 1000.0);
        *set1 << (randtime.Bogo / 1000.0);
        *set2 << (retime.Bogo / 1000.0);
        axisX->append("Bogo排序");
    }
    axisX->setLabelsColor(QColor(7, 28, 96));
    QValueAxis* axisY = new QValueAxis;
    //axisY->setRange(0, 1);   //改为setRange(0,1);则表示坐标为动态计算大小的
    axisY->setTitleText("耗时(ms)");
    axisY->setLabelFormat("%10.5lf");


    set0->setLabelColor(QColor(0, 0, 255));       //设置条形数据颜色
    set1->setLabelColor(QColor(0, 0, 255));
    set2->setLabelColor(QColor(0, 0, 255));

    QBarSeries* series = new QBarSeries();
    series->append(set0);
    series->append(set1);
    series->append(set2);
    series->setVisible(true);
    series->setLabelsVisible(true);

    m_chart->setTheme(QChart::ChartThemeLight);//设置白色主题
    m_chart->setDropShadowEnabled(true);//背景阴影
    m_chart->addSeries(series);//添加系列到QChart上

    m_chart->setTitleBrush(QBrush(QColor(0, 0, 255)));//设置标题Brush
    m_chart->setTitleFont(QFont("微软雅黑"));//设置标题字体
    m_chart->setTitle("排序时间对比图");

    m_chart->setAxisX(axisX, series);
    m_chart->setAxisY(axisY, series);

    m_chart->legend()->setVisible(true);
    m_chart->legend()->setAlignment(Qt::AlignBottom);//底部对齐
    m_chart->legend()->setBackgroundVisible(true);//设置背景是否可视
    m_chart->legend()->setAutoFillBackground(true);//设置背景自动填充
    m_chart->legend()->setColor(QColor(222, 233, 251));//设置颜色
    m_chart->legend()->setLabelColor(QColor(0, 100, 255));//设置标签颜色
    m_chart->legend()->setMaximumHeight(50);

    QChartView* chartView = new QChartView(m_chart);
    chartView->setRenderHint(QPainter::Antialiasing);



    //resize(621, 371);
    //QPieSeries* series = new QPieSeries();
    //series->append("10%", 1);
    //series->append("20%", 2);
    //series->append("70%", 7);
    //series->setLabelsVisible();

    //QPieSlice* slice_red = series->slices().at(0);
    //QPieSlice* slice_green = series->slices().at(1);
    //QPieSlice* slice_blue = series->slices().at(2);
    //slice_red->setColor(QColor(255, 0, 0, 255));
    //slice_green->setColor(QColor(0, 255, 0, 255));
    //slice_blue->setColor(QColor(0, 0, 255, 255));

    //QChart* chart = new QChart();
    //chart->addSeries(series);
    //chart->setTitle("PieChart");
    //chart->legend()->hide();

    ////QChartView *chartview = new QChartView(chart);
    ////chartview->setRenderHint(QPainter::Antialiasing);
    //chartView->show();
    ui.graphicsView->setChart(m_chart);
    ui.graphicsView->setRenderHint(QPainter::Antialiasing);
}

void SortComparison::btn_export_click()
{
    //ui.statusBar->showMessage(QString::fromStdString("导出中....."), 1200);
    state_label->setText("导出中.....");
    QScreen* screen = QGuiApplication::primaryScreen();
    QPixmap p = screen->grabWindow(ui.graphicsView->winId());
    QImage image = p.toImage();
    image.save("compare.png");
    state_label->setText("导出成功");
    QMessageBox::about(this, "成功", "导出图像成功，位于程序目录下的compare.png");
    state_label->setText("");
}

void SortComparison::btn_clean_click()
{
    ui.check_Insertion->setCheckState(Qt::Unchecked);
    ui.check_bogo->setCheckState(Qt::Unchecked);
    ui.check_Bubble->setCheckState(Qt::Unchecked);
    ui.check_cocktail->setCheckState(Qt::Unchecked);
    ui.check_Heap->setCheckState(Qt::Unchecked);
    ui.check_Merge->setCheckState(Qt::Unchecked);
    ui.check_Quick->setCheckState(Qt::Unchecked);
    ui.check_Radix->setCheckState(Qt::Unchecked);
    ui.check_Selection->setCheckState(Qt::Unchecked);
    ui.check_Shell->setCheckState(Qt::Unchecked);
    ui.spin_count->setValue(0);

}

QString str2qstr(const string str)
{
    return QString::fromLocal8Bit(str.data());
}

string qstr2str(const QString qstr)
{
    QByteArray cdata = qstr.toLocal8Bit();
    return string(cdata);
}

bool AllisNum(string str)
{
    for (int i = 0; i < str.size(); i++)
    {
        int tmp = (int)str[i];
        if (tmp >= 48 && tmp <= 57)
        {
            continue;
        }
        else
        {
            return false;
        }
    }
    return true;
}
