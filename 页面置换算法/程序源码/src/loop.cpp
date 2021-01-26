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
    //����ָ��ָ���������
    OPT opt;
    FIFO fifo;
    LRU lru;
    LFU lfu;
    CLOCK clock;
    Schedule *sch;

    while(flag)
    {
        cout << "\n*************************\n";
        cout <<"1������û��㷨OPT"<<endl;
        cout <<"2���Ƚ��ȳ��㷨FIFO"<<endl;
        cout <<"3��������δʹ���㷨LRU"<<endl;
        cout <<"4���������δʹ���㷨LFU"<<endl;
        cout <<"5��CLOCK�û��㷨"<<endl;
        cout <<"6������0�˳�"<<endl;
        cout << "*************************\n";
        cin >> select;

        switch(select)
        {
        case Opt:
            cout << "----------����û��㷨OPT----------" << endl;
            sch = &opt;
            sch->running();
            break;
        case Fifo:
            cout << "----------�Ƚ��ȳ��㷨FIFO----------" << endl;
            sch = &fifo;
            sch->running();
            break;
        case Lru:
            cout << "--------������δʹ���㷨LRU--------" << endl;
            sch = &lru;
            //sch->init();
            sch->running();
            break;
        case Lfu:
            cout << "--------�������δʹ���㷨LFU--------" << endl;
            sch = &lfu;
            sch->running();
            break;
        case Clock:
            cout << "------------CLOCK�û��㷨------------" << endl;
            sch = &clock;
            sch->running();
            break;
        case EXIT:
            flag = 0;
            break;
        default:
            cout <<"�������" << endl;
            break;
        }

    }

}
