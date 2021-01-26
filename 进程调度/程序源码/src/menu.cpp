#include "menu.h"
#include "prepare.h"
#include <iostream>
using namespace std;
void menu()
{
    Process process;

    typedef enum choose
    {
        fcfs = 1,
        sjf = 2,
        hrrn = 3,
        srt = 4,
        rr = 5,
        fq = 6,
        qy = 7,
        edf = 8,
        llf = 9,
        exit =0,
    };

    int choose,flag=1;

    cout << "请选择调度方式：" << endl;
    cout<<"--------作业调度--------"<<endl;
    cout<<"1、先来先服务FCFS"<<endl;
    cout<<"2、短作业优先调度SJF"<<endl;
    cout<<"3、高响应比优先调度HRRN"<<endl;
    cout<<"--------进程调度--------"<<endl;
    cout<<"4、最短剩余时间调度SRT"<<endl;
    cout<<"5、时间片调度RR"<<endl;
    cout<<"6、非抢占优先级FQ"<<endl;
    cout<<"7、抢占式优先级QY"<<endl;
    cout<<"--------实时调度--------"<<endl;
    cout<<"8、最早截止时间优先调度EDF"<<endl;
    cout<<"9、最低松弛度优先调度LLF"<<endl<<endl;
    cout<<"0、退出"<<endl;
     while(flag)
    {
        cin>>choose;
        switch (choose)
        {
            case fcfs : process.fcfs();break;
            case sjf : process.sjf();break;
            case hrrn : process.hrrn();break;
            case srt : process.srt();break;
            case rr : process.rr();break;
            case fq :process.fq();break;
            case qy : process.qy();break;
            case edf : process.edf();break;
            case llf : process.llf();break;
            case exit : flag=0;break;
            default:cout<<"ERROR!"<<endl;break;
        }
    }
}
