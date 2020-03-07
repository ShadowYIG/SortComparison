#pragma once
#include <string>
#include<vector>
using namespace std;
struct sortcom {
    bool Insertion;//²åÈëÅÅĞò
    bool Shell;//Ï£¶ûÅÅĞò
    bool Bubble;//Ã°ÅİÅÅĞò
    bool Quick;//¿ìËÙÅÅĞò
    bool Selection;//¼òµ¥Ñ¡ÔñÅÅĞò
    bool Heap;//¶ÑÅÅĞò
    bool Merge;//¹é²¢ÅÅĞò
    bool Counting;//¼ÆÊıÅÅĞò
    //bool Bucket;//Í°ÅÅĞò
    bool Radix;//»ùÊıÅÅĞò
    bool cocktail;//¼¦Î²¾ÆÅÅĞò
    bool Bogo;//BogoÅÅĞò£¨ºï×ÓÅÅĞò£©
};
struct sorttime {
    long Insertion;//²åÈëÅÅĞò
    long Shell;//Ï£¶ûÅÅĞò
    long Bubble;//Ã°ÅİÅÅĞò
    long Quick;//¿ìËÙÅÅĞò
    long Selection;//¼òµ¥Ñ¡ÔñÅÅĞò
    long Heap;//¶ÑÅÅĞò
    long Merge;//¹é²¢ÅÅĞò
    //long Counting;//¼ÆÊıÅÅĞò
    //long Bucket;//Í°ÅÅĞò
    long Radix;//»ùÊıÅÅĞò
    long cocktail;//¼¦Î²¾ÆÅÅĞò
    long Bogo;//BogoÅÅĞò£¨ºï×ÓÅÅĞò£©
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
    datapro();//¡Ì
    datapro(const vector<int> num);//¡Ì
    bool getRandNum(const int max, const int min, const int numsize, const int numtype, vector<int> &res);//numtype=1 ÕıĞò numtype=-1 ÄæĞò numtype=0Ëæ»ú//¡Ì
    bool putNum(const string str_num, const char separator);//¡Ì
    bool putNum(const vector<int> num);
    bool getResult(string &str_num, const char separator);
    bool numSort(int sorttype);//1.²åÈëÅÅĞò£¬2.Ï£¶ûÅÅĞò£¬3.Ã°ÅİÅÅĞò£¬4.¿ìËÙÅÅĞò£¬ 5. ¼òµ¥Ñ¡ÔñÅÅĞò£¬6.¶ÑÅÅĞò£¬7.¹é²¢ÅÅĞò£¬8.¼ÆÊıÅÅĞò£¬9.Í°ÅÅĞò£¬10.»ùÊıÅÅĞò£¬11.¼¦Î²¾ÆÅÅĞò£¬12.BogoÅÅĞò
    bool sortCompara(const sortcom &sort_com, const int numtype);
    sorttime getSortTime(const int numtype);//numtype=-1 badnum£¬numtype=0 randnum , numtype=1 goodnum//¡Ì
};
