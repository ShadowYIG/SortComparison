#pragma once
#include <string>
#include<vector>
using namespace std;
struct sortcom {
    bool Insertion;//��������
    bool Shell;//ϣ������
    bool Bubble;//ð������
    bool Quick;//��������
    bool Selection;//��ѡ������
    bool Heap;//������
    bool Merge;//�鲢����
    bool Counting;//��������
    //bool Bucket;//Ͱ����
    bool Radix;//��������
    bool cocktail;//��β������
    bool Bogo;//Bogo���򣨺�������
};
struct sorttime {
    long Insertion;//��������
    long Shell;//ϣ������
    long Bubble;//ð������
    long Quick;//��������
    long Selection;//��ѡ������
    long Heap;//������
    long Merge;//�鲢����
    //long Counting;//��������
    //long Bucket;//Ͱ����
    long Radix;//��������
    long cocktail;//��β������
    long Bogo;//Bogo���򣨺�������
};

class datapro
{
private:
    vector<int> num;
    vector<int> result;
    sorttime randnum;
    sorttime badnum;
    sorttime goodnum;

public:
    datapro();//��
    datapro(const vector<int> num);//��
    bool getRandNum(const int max, const int min, const int numsize, const int numtype, vector<int> &res);//numtype=1 ���� numtype=-1 ���� numtype=0���//��
    bool putNum(const string str_num, const char separator);//��
    bool putNum(const vector<int> num);
    bool getResult(string &str_num, const char separator);
    bool numSort(int sorttype);//1.��������2.ϣ������3.ð������4.�������� 5. ��ѡ������6.������7.�鲢����8.��������9.Ͱ����10.��������11.��β������12.Bogo����
    bool sortCompara(const sortcom &sort_com, const int numtype);
    sorttime getSortTime(const int numtype);//numtype=-1 badnum��numtype=0 randnum , numtype=1 goodnum//��
};
