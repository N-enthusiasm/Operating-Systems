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

    cout << "��ѡ����ȷ�ʽ��" << endl;
    cout<<"--------��ҵ����--------"<<endl;
    cout<<"1�������ȷ���FCFS"<<endl;
    cout<<"2������ҵ���ȵ���SJF"<<endl;
    cout<<"3������Ӧ�����ȵ���HRRN"<<endl;
    cout<<"--------���̵���--------"<<endl;
    cout<<"4�����ʣ��ʱ�����SRT"<<endl;
    cout<<"5��ʱ��Ƭ����RR"<<endl;
    cout<<"6������ռ���ȼ�FQ"<<endl;
    cout<<"7����ռʽ���ȼ�QY"<<endl;
    cout<<"--------ʵʱ����--------"<<endl;
    cout<<"8�������ֹʱ�����ȵ���EDF"<<endl;
    cout<<"9������ɳڶ����ȵ���LLF"<<endl<<endl;
    cout<<"0���˳�"<<endl;
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
