#include "dataProcessing.h"
#include "SortingAl.h"
#include "mytime.h"
#include <time.h>
#include <sstream>
#include <iostream>
datapro::datapro()
{
    this->randnum = { 0,0,0,0,0,0,0,0,0,0 };
    this->badnum = { 0,0,0,0,0,0,0,0,0,0 };
    this->goodnum = { 0,0,0,0,0,0,0,0,0,0 };
}

datapro::datapro(const vector<int> num)
{
    this->num.assign(num.begin(), num.end());
    this->randnum = { 0,0,0,0,0,0,0,0,0,0 };
    this->badnum = { 0,0,0,0,0,0,0,0,0,0 };
    this->goodnum = { 0,0,0,0,0,0,0,0,0,0 };
}

bool datapro::putNum(const string str_num, const char separator)
{
    stringstream ss(str_num);
    string str;
    int a;
    vector<int>().swap(num);
    while (getline(ss, str, ',')) {
        ss << str;
        ss >> a;
        num.push_back(a);
    }
    return 0;
}

bool datapro::putNum(const vector<int> num)
{
    this->num.assign(num.begin(), num.end());
    return 1;
}

bool datapro::getRandNum(const int max, const int min, const int numsize, const int numtype, vector<int>& res)
{//µ±max-min=numsizeÊ±Éú³ÉÎÞÖØ¸´Êý
    vector<int>().swap(res);
    srand(time(0));
    if (numtype == 1) {
        for (int i = min; i < max; i++) {
            res.push_back(i);
        }
        if (max - min < numsize) {
            for (int i = max; i < numsize; i++) {
                res.push_back(rand() % (max - min) + min);
            }
        }
        return 1;
    }
    else if (numtype == -1) {
        for (int i = max; i > min; i--) {
            res.push_back(i);
        }
        if (max - min < numsize) {
            for (int i = max; i < numsize; i++) {
                res.push_back(rand() % (max - min) + min);
            }
        }
        return 1;
    }
    else if (numtype == 0) {
        for (int i = 0; i < numsize; i++) {
            res.push_back(rand() % (max - min) + min);
        }
        return 1;
    }
    return 0;
    
}

bool datapro::getResult(string &str_num, const char separator)
{
    str_num = "";
    bool isone = true;
    for (vector<int>::const_iterator iter = result.cbegin(); iter != result.cend(); iter++)
    {
        if (isone) {
            str_num = str_num + to_string((*iter));
            isone = false;
        }
        else {
            str_num = str_num + separator +  to_string((*iter));
        }
    }
    return 1;
}

sorttime datapro::getSortTime(const int numtype) // numtype = -1 badnum£¬numtype = 0 randnum, numtype = 1 goodnum
{
    if (numtype == -1) {
        return badnum;
    }
    else if (numtype == 0) {
        return randnum;
    }
    else {
        return goodnum;
    }
}

bool datapro::numSort(int sorttype)//, vector<int>& res
{
    int* int_num = new int[num.size()];
    if (!num.empty())
    {
        memcpy(int_num, &num[0], num.size() * sizeof(int));
    }
    else {
        return 0;
    }
    sortingAl sor;
    MyTimer usetime;
    usetime.Start();
    switch (sorttype)
    {
    case 1:
        sor.Insertion_Sort(int_num, num.size());
        usetime.End();
        randnum.Insertion = usetime.costTime;
        break;
    case 2:
        sor.shell_sort(int_num, num.size());
        usetime.End();
        randnum.Shell = usetime.costTime;
        break;
    case 3:
        sor.Bubble_Sort(int_num, num.size());
        usetime.End();
        randnum.Bubble = usetime.costTime;
        break;
    case 4:
        sor.QuickSort(int_num, num.size());
        usetime.End();
        randnum.Quick = usetime.costTime;
        break;
    case 5:
        sor.Selection_Sort(int_num, num.size());
        usetime.End();
        randnum.Selection = usetime.costTime;
        break;
    case 6:
        sor.HeapSort(int_num, num.size());
        usetime.End();
        randnum.Heap = usetime.costTime;
        break;
    case 7:
        sor.Merge_sort(int_num, num.size());
        usetime.End();
        randnum.Merge = usetime.costTime;
        break;
    case 8:
        sor.radixsort(int_num, num.size());
        usetime.End();
        randnum.Radix = usetime.costTime;
        break;
    case 9:
        sor.cocktailSort(int_num, num.size());
        usetime.End();
        randnum.cocktail = usetime.costTime;
        break;
    case 10:
        sor.bogoSort(int_num, num.size());
        usetime.End();
        randnum.Bogo = usetime.costTime;
        break;
    }
    vector<int> resu;
    for (int i = 0; i < num.size(); i++) {
        resu.push_back(int_num[i]);
    }
    result = resu;
    delete int_num;
    return 0;
}

bool datapro::sortCompara(const sortcom& sort_com, const int numtype)
{
    int* int_num = new int[num.size()];
    if (!num.empty())
    {
        memcpy(int_num, &num[0], num.size() * sizeof(int));
    }
    else {
        return 0;
    }
    sortingAl sor;
    MyTimer usetime;
    int length = num.size();
    //1.²åÈëÅÅÐò£¬
    if (sort_com.Insertion) {
        usetime.Reset();
        usetime.Start();
        sor.Insertion_Sort(int_num, length);
        usetime.End();
        if (numtype == 0) {
            randnum.Insertion = usetime.costTime;
        }
        else if (numtype == -1) {
            badnum.Insertion = usetime.costTime;
        }
        else {
            goodnum.Insertion = usetime.costTime;
        }
        
    }
    //2.Ï£¶ûÅÅÐò£¬
    if (sort_com.Shell) {
        usetime.Reset();
        usetime.Start();
        sor.shell_sort(int_num, length);
        usetime.End();
        if (numtype == 0) {
            randnum.Shell = usetime.costTime;
        }
        else if (numtype == -1) {
            badnum.Shell = usetime.costTime;
        }
        else {
            goodnum.Shell = usetime.costTime;
        }

    }
    //3.Ã°ÅÝÅÅÐò£¬
    if (sort_com.Bubble) {
        usetime.Reset();
        usetime.Start();
        sor.Bubble_Sort(int_num, length);
        usetime.End();
        if (numtype == 0) {
            randnum.Bubble = usetime.costTime;
        }
        else if (numtype == -1) {
            badnum.Bubble = usetime.costTime;
        }
        else {
            goodnum.Bubble = usetime.costTime;
        }

    }

    //4.¿ìËÙÅÅÐò£¬ 
    if (sort_com.Quick) {
        usetime.Reset();
        usetime.Start();
        sor.QuickSort(int_num, length);
        usetime.End();
        if (numtype == 0) {
            randnum.Quick = usetime.costTime;
        }
        else if (numtype == -1) {
            badnum.Quick = usetime.costTime;
        }
        else {
            goodnum.Quick = usetime.costTime;
        }

    }

    //5. ¼òµ¥Ñ¡ÔñÅÅÐò£¬
    if (sort_com.Selection) {
        usetime.Reset();
        usetime.Start();
        sor.Selection_Sort(int_num, length);
        usetime.End();
        if (numtype == 0) {
            randnum.Selection = usetime.costTime;
        }
        else if (numtype == -1) {
            badnum.Selection = usetime.costTime;
        }
        else {
            goodnum.Selection = usetime.costTime;
        }

    }

    //6.¶ÑÅÅÐò£¬
    if (sort_com.Heap) {
        usetime.Reset();
        usetime.Start();
        sor.HeapSort(int_num, length);
        usetime.End();
        if (numtype == 0) {
            randnum.Heap = usetime.costTime;
        }
        else if (numtype == -1) {
            badnum.Heap = usetime.costTime;
        }
        else {
            goodnum.Heap = usetime.costTime;
        }

    }

    //7.¹é²¢ÅÅ£¬
    if (sort_com.Merge) {
        usetime.Reset();
        usetime.Start();
        sor.Merge_sort(int_num, length);
        usetime.End();
        if (numtype == 0) {
            randnum.Merge = usetime.costTime;
        }
        else if (numtype == -1) {
            badnum.Merge = usetime.costTime;
        }
        else {
            goodnum.Merge = usetime.costTime;
        }

    }

    //8.»ùÊýÅÅÐò£¬
    if (sort_com.Radix) {
        usetime.Reset();
        usetime.Start();
        sor.radixsort(int_num, length);
        usetime.End();
        if (numtype == 0) {
            randnum.Radix = usetime.costTime;
        }
        else if (numtype == -1) {
            badnum.Radix = usetime.costTime;
        }
        else {
            goodnum.Radix = usetime.costTime;
        }

    }

    //9.¼¦Î²¾ÆÅÅÐò£¬
    if (sort_com.cocktail) {
        usetime.Reset();
        usetime.Start();
        sor.cocktailSort(int_num, length);
        usetime.End();
        if (numtype == 0) {
            randnum.cocktail = usetime.costTime;
        }
        else if (numtype == -1) {
            badnum.cocktail = usetime.costTime;
        }
        else {
            goodnum.cocktail = usetime.costTime;
        }

    }

    //10.BogoÅÅÐò
    if (sort_com.Bogo) {
        usetime.Reset();
        usetime.Start();
        sor.bogoSort(int_num, length);
        usetime.End();
        if (numtype == 0) {
            randnum.Bogo = usetime.costTime;
        }
        else if (numtype == -1) {
            badnum.Bogo = usetime.costTime;
        }
        else {
            goodnum.Bogo = usetime.costTime;
        }

    }
}
