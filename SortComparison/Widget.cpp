#include "Widget.h"
#include "dataProcessing.h"
#include "SortComparison.h"


Widget::~Widget()
{
    delete &from;
}
Widget::Widget(QWidget* parent)
    : QWidget(parent)
{
    from.setupUi(this);
}

void Widget::btn_sure_click()
{
    int max = from.spin_max->value();
    int min = from.spin_min->value();
    int count = from.spin_num->value();
    int rand_type = 0;
    if (max <= min) {
        QMessageBox::critical(this, "�������", "����ֵ����С������ֵ�Ҳ���Ϊ0");
        return;
    }
    if (count <= 0) {
        QMessageBox::critical(this, "�������", "������������С�ڻ����0");
    }
    if (from.radio_confu->isChecked()) {
        rand_type = 0;
    }
    else if (from.radio_pos->isChecked()) {
        rand_type = 1;
    }
    else {
        rand_type = -1;
    }
    datapro mydata;
    vector<int> res;
    string str = "";
    int index = 0;
    QMessageBox::about(this, "��ʾ", "��ʼ��������");
    if (mydata.getRandNum(max, min, count, rand_type, res)) {
        for (vector<int>::const_iterator iter = res.cbegin(); iter != res.cend(); iter++)
        {
            if (index == 0) {
                str = str + to_string((*iter));
                index++;
            }
            else {
                str = str + "," + to_string((*iter));
            }

        }
        emit infoSend(QString::fromLocal8Bit(str.data()));
        //this->close();
        //this->setWindowModality(Qt::NonModal);
        this->hide();

    }
    else {
        QMessageBox::critical(this, "����", "����ʧ��");
    }


}