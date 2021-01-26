#include "prepare.h"
#include "SJF.h"
#include "HRRN.h"
#include "FQ.h"
#include "RR.h"
#include "FCFS.h"
#include "SRT.h"
#include "EDF.h"
#include "QY.h"
#include "LLF.h"
#include <fstream>

int Process::readTCB(vector <TCB> &tcb,TCB &temp,ifstream &infile)
{
    int totaltime;//总的运行时间
    char tcbName;
    int period;
    int cputime;
    infile>>totaltime;

    for(int i=0;i<2;i++){
        infile>>tcbName;
        infile>>period;
        infile>>cputime;

        temp.tcbName=tcbName;
        temp.period=period;
        temp.cputime=cputime;

        temp.remain = temp.cputime;
	 	temp.laxity = -1;
	 	temp.pnum=1; //初始周期号为1

	 	tcb.push_back(temp);
    }
    infile.close();

    return totaltime;
}
//排序
bool Process::cmp(JCB jcb1,JCB jcb2)
{
    return jcb1.arriveTime<jcb2.arriveTime;
}

void Process::printJCB(vector <JCB> jcb,int NUMBER,ofstream &outfile)
{
    //计算平均周转时间
    float sum1=0.0;
	for(int i=0;i<NUMBER;i++)
    {
		sum1+=jcb[i].turnoverTime;
	}
	sum1/=NUMBER;

	//计算平均带权周转时间
	float sum2=0.0;
	for(int i=0;i<NUMBER;i++)
    {
		sum2+=jcb[i].weightTime;
	}
	sum2/=NUMBER;

	outfile<<"----------------------------------------------------"<<endl;
	outfile<<"进程编号 到达时间 服务时间 结束时间 周转时间 带权周转时间"<<endl;
	int i;
	for(i=0;i<NUMBER;i++)
    {
        //用迭代器
        outfile<<setiosflags(ios::fixed)<<setprecision(2);
        outfile<<jcb[i].jobName<<'\t'<<jcb[i].arriveTime<<'\t'<<jcb[i].runTime
        <<'\t'<<jcb[i].endTime<<'\t'<<jcb[i].turnoverTime
        <<'\t'<<jcb[i].weightTime<<endl;
	}
	outfile<<"----------------------------------------------------"<<endl;

	outfile<<"平均周转时间："<<sum1<<endl;
	outfile<<"平均带权周转时间："<<sum2<<endl;
}

void Process::fcfs()
{
    FCFS fcfs;
    fcfs.RunFCFS();
}
void Process::sjf()
{
    SJF sjf;
    sjf.RunSJF();
}
void Process::hrrn()
{
    HRRN hrrn;
    hrrn.RunHRRN();
}
void Process::srt()
{
    SRT srt;
    srt.RunSRT();
}
void Process::rr()
{
    RR rr;
    rr.RunRR();
}
void Process::fq()
{
    FQ fq;
    fq.RunFQ();
}
void Process::qy()
{
    QY qy;
    qy.RunQY();
}
void Process::edf()
{
    EDF edf;
    edf.RunEDF();
}
void Process::llf()
{
    LLF llf;
    llf.RunLLF();
}
