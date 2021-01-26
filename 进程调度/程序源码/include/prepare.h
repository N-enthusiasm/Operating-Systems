#ifndef PREPARE_H_INCLUDED
#define PREPARE_H_INCLUDED
#include <cstring>
#include <vector>
#include <iomanip>

const int MAX = 100;

using namespace std;

class JCB
{
public:
	char jobName;   //进程名
	int arriveTime; //到达时间
	int runTime;    //服务时间
	int startTime;  //开始时间
	int endTime;    //结束时间
	int turnoverTime;   //周转时间
	float weightTime;   //带权周转时间
	int sign_completion;  //标志是否完成调用或是否已经到达（在SJF中）
	int FQ;             //优先级
	int remaining_time; //剩余服务时间
	int number;
};

class TCB
{
public:
    char tcbName;   //任务名
    int period; //周期
    int cputime;    //需要的CPU时间
    int remain; //剩余的CPU时间
    int pnum;   //所处周期数
    int laxity; //松弛度
    int deadtime[10];   //截止时间
    bool f; //判断进程是否运行
};


class Process
{
public:
    int readTCB(vector <TCB> &tcb,TCB &temp,ifstream &infile);
    static bool cmp(JCB jcb1,JCB jcb2);
    void printJCB(vector <JCB> jcb,int NUMBER,ofstream &outfile);
    void fcfs();
    void sjf();
    void hrrn();
    void srt();
    void rr();
    void fq();
    void qy();
    void edf();
    void llf();
};

#endif // PREPARE_H_INCLUDED
