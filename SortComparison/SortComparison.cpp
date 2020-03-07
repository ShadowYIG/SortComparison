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
        QMessageBox::critical(this, "���ݴ���", "���ݲ���Ϊ��");
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
        QMessageBox::critical(this, "���ݴ���", "����ֻ��Ϊ�����ҷָ���ΪӢ�Ķ���");
    }
    else {
        datapro mydata(v_num);
        vector<int> res;
        int sort_type = 1;
        int index = 0;
        //1.��������2.ϣ������3.ð������4.�������� 5. ��ѡ������6.������7.�鲢����8.��������9.��β������10.Bogo����
        int qtype = ui.com_alg->currentIndex() + 1;
        if (qtype == 10) {
            QMessageBox::StandardButton btn;
            btn = QMessageBox::question(this, "ע��", "Bogo����Ϊ�������ʽ���������֣�������10���µ��������ԣ�������������ʱ�����������Ƿ��������", QMessageBox::Yes | QMessageBox::No);
            if (btn == QMessageBox::No) {
                return;
            }
        }
        state_label->setText("�����У����Ժ�....");
        mydata.numSort(qtype);
        string re = "";
        mydata.getResult(re, ',');
        ui.text_num->setPlainText(str2qstr(re));
        int count = ui.tableWidget->rowCount();
        ui.tableWidget->insertRow(count);
        ui.tableWidget->setItem(count - 1, 0, new QTableWidgetItem(ui.com_alg ->currentText()));
        ui.tableWidget->setItem(count - 1, 1, new QTableWidgetItem(QString::number(v_num.size())));
        //1.��������2.ϣ������3.ð������4.�������� 5. ��ѡ������6.������7.�鲢����8.��������9.Ͱ����10.��������11.��β������12.Bogo����
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
        QMessageBox::critical(this, "���ݴ���", "��������Ϊ��");
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
        btn = QMessageBox::question(this, "ע��", "Bogo����Ϊ�������ʽ���������֣�����ʱ�����������Ƿ��������", QMessageBox::Yes | QMessageBox::No);
        if (btn == QMessageBox::No) {
            ui.check_bogo->setCheckState(Qt::Unchecked);
            return;
        }
        else {
            sortsel.Bogo = true;
            havecheck = true;
        }
        
    }

    state_label->setText("�����У����Ժ�.....");
    //ui.statusBar->showMessage(QString::fromStdString("�����У����Ժ�....."), 1200);
    dp.getRandNum(count * 2, 0, count, 0, ve_num);
    dp.putNum(ve_num);
    state_label->setText("��ʼִ����������.....");
    //ui.statusBar->showMessage(QString::fromStdString("��ʼִ����������....."), 1200);
    dp.sortCompara(sortsel, 0);

    dp.getRandNum(count * 2, 0, count, 1, ve_num);
    dp.putNum(ve_num);
    state_label->setText("��ʼִ��˳������.....");
    //ui.statusBar->showMessage(QString::fromStdString("��ʼִ��˳������....."), 1200);
    dp.sortCompara(sortsel, 1);

    dp.getRandNum(count * 2, 0, count, -1, ve_num);
    dp.putNum(ve_num);
    state_label->setText("��ʼִ����������.....");
    //ui.statusBar->showMessage(QString::fromStdString("��ʼִ����������....."), 1200);
    dp.sortCompara(sortsel, -1);
    state_label->setText("ִ�����");
    sorttime seqtime = dp.getSortTime(1);
    sorttime randtime = dp.getSortTime(0);
    sorttime retime = dp.getSortTime(-1);
    QChart *m_chart = new QChart();
    QBarCategoryAxis* axisX = new QBarCategoryAxis;
    QBarSet* set0 = new QBarSet("˳��");
    QBarSet* set1 = new QBarSet("����");
    QBarSet* set2 = new QBarSet("���");
    if (sortsel.Insertion) {
        *set0 << (seqtime.Insertion / 1000.0);
        *set1 << (randtime.Insertion / 1000.0);
        *set2 << (retime.Insertion / 1000.0);
        axisX->append("��������");
    }
    if (sortsel.Shell) {
        *set0 << (seqtime.Shell / 1000.0);
        *set1 << (randtime.Shell / 1000.0);
        *set2 << (retime.Shell / 1000.0);
        axisX->append("ϣ������");
    }
    if (sortsel.Bubble) {
        *set0 << (seqtime.Bubble / 1000.0);
        *set1 << (randtime.Bubble / 1000.0);
        *set2 << (retime.Bubble / 1000);
        axisX->append("ð������");
    }
    if (sortsel.Quick) {
        *set0 << (seqtime.Quick / 1000.0);
        *set1 << (randtime.Quick / 1000.0);
        *set2 << (retime.Quick / 1000.0);
        axisX->append("��������");
    }
    if (sortsel.Selection) {
        *set0 << (seqtime.Selection / 1000.0);
        *set1 << (randtime.Selection / 1000.0);
        *set2 << (retime.Selection / 1000.0);
        axisX->append("��ѡ������");
    }
    if (sortsel.Heap) {
        *set0 << (seqtime.Heap / 1000.0);
        *set1 << (randtime.Heap / 1000.0);
        *set2 << (retime.Heap / 1000.0);
        axisX->append("������");
    }
    if (sortsel.Merge) {
        *set0 << (seqtime.Merge / 1000.0);
        *set1 << (randtime.Merge / 1000.0);
        *set2 << (retime.Merge / 1000.0);
        axisX->append("�鲢����");
    }
    if (sortsel.Radix) {
        *set0 << (seqtime.Radix / 1000.0);
        *set1 << (randtime.Radix / 1000.0);
        *set2 << (retime.Radix / 1000.0);
        axisX->append("��������");
    }
    if (sortsel.cocktail) {
        *set0 << (seqtime.cocktail / 1000.0);
        *set1 << (randtime.cocktail / 1000.0);
        *set2 << (retime.cocktail / 1000.0);
        axisX->append("��β������");
    }
    if (sortsel.Bogo) {
        *set0 << (seqtime.Bogo / 1000.0);
        *set1 << (randtime.Bogo / 1000.0);
        *set2 << (retime.Bogo / 1000.0);
        axisX->append("Bogo����");
    }
    axisX->setLabelsColor(QColor(7, 28, 96));
    QValueAxis* axisY = new QValueAxis;
    //axisY->setRange(0, 1);   //��ΪsetRange(0,1);���ʾ����Ϊ��̬�����С��
    axisY->setTitleText("��ʱ(ms)");
    axisY->setLabelFormat("%10.5lf");


    set0->setLabelColor(QColor(0, 0, 255));       //��������������ɫ
    set1->setLabelColor(QColor(0, 0, 255));
    set2->setLabelColor(QColor(0, 0, 255));

    QBarSeries* series = new QBarSeries();
    series->append(set0);
    series->append(set1);
    series->append(set2);
    series->setVisible(true);
    series->setLabelsVisible(true);

    m_chart->setTheme(QChart::ChartThemeLight);//���ð�ɫ����
    m_chart->setDropShadowEnabled(true);//������Ӱ
    m_chart->addSeries(series);//���ϵ�е�QChart��

    m_chart->setTitleBrush(QBrush(QColor(0, 0, 255)));//���ñ���Brush
    m_chart->setTitleFont(QFont("΢���ź�"));//���ñ�������
    m_chart->setTitle("����ʱ��Ա�ͼ");

    m_chart->setAxisX(axisX, series);
    m_chart->setAxisY(axisY, series);

    m_chart->legend()->setVisible(true);
    m_chart->legend()->setAlignment(Qt::AlignBottom);//�ײ�����
    m_chart->legend()->setBackgroundVisible(true);//���ñ����Ƿ����
    m_chart->legend()->setAutoFillBackground(true);//���ñ����Զ����
    m_chart->legend()->setColor(QColor(222, 233, 251));//������ɫ
    m_chart->legend()->setLabelColor(QColor(0, 100, 255));//���ñ�ǩ��ɫ
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
    //ui.statusBar->showMessage(QString::fromStdString("������....."), 1200);
    state_label->setText("������.....");
    QScreen* screen = QGuiApplication::primaryScreen();
    QPixmap p = screen->grabWindow(ui.graphicsView->winId());
    QImage image = p.toImage();
    image.save("compare.png");
    state_label->setText("�����ɹ�");
    QMessageBox::about(this, "�ɹ�", "����ͼ��ɹ���λ�ڳ���Ŀ¼�µ�compare.png");
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
