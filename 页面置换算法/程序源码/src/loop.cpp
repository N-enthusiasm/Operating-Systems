#include "loop.h"
#include "Page.h"
#include "FIFO.h"
#include "LRU.h"
#include "LFU.h"
#include "OPT.h"
#include "CLOCK.h"
#include <iostream>

using namespace std;

void loop()
{
    enum choice
    {
        Opt = 1,
        Fifo = 2,
        Lru = 3,
        Lfu = 4,
        Clock = 5,
        EXIT = 0,
    };

    int select,flag=1;
    //父类指针指向子类对象
    OPT opt;
    FIFO fifo;
    LRU lru;
    LFU lfu;
    CLOCK clock;
    Schedule *sch;

    while(flag)
    {
        cout << "\n*************************\n";
        cout <<"1、最佳置换算法OPT"<<endl;
        cout <<"2、先进先出算法FIFO"<<endl;
        cout <<"3、最近最久未使用算法LRU"<<endl;
        cout <<"4、最近最少未使用算法LFU"<<endl;
        cout <<"5、CLOCK置换算法"<<endl;
        cout <<"6、输入0退出"<<endl;
        cout << "*************************\n";
        cin >> select;

        switch(select)
        {
        case Opt:
            cout << "----------最佳置换算法OPT----------" << endl;
            sch = &opt;
            sch->running();
            break;
        case Fifo:
            cout << "----------先进先出算法FIFO----------" << endl;
            sch = &fifo;
            sch->running();
            break;
        case Lru:
            cout << "--------最近最久未使用算法LRU--------" << endl;
            sch = &lru;
            //sch->init();
            sch->running();
            break;
        case Lfu:
            cout << "--------最近最少未使用算法LFU--------" << endl;
            sch = &lfu;
            sch->running();
            break;
        case Clock:
            cout << "------------CLOCK置换算法------------" << endl;
            sch = &clock;
            sch->running();
            break;
        case EXIT:
            flag = 0;
            break;
        default:
            cout <<"输入错误" << endl;
            break;
        }

    }

}
