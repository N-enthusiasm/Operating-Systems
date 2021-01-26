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
	char jobName;   //������
	int arriveTime; //����ʱ��
	int runTime;    //����ʱ��
	int startTime;  //��ʼʱ��
	int endTime;    //����ʱ��
	int turnoverTime;   //��תʱ��
	float weightTime;   //��Ȩ��תʱ��
	int sign_completion;  //��־�Ƿ���ɵ��û��Ƿ��Ѿ������SJF�У�
	int FQ;             //���ȼ�
	int remaining_time; //ʣ�����ʱ��
	int number;
};

class TCB
{
public:
    char tcbName;   //������
    int period; //����
    int cputime;    //��Ҫ��CPUʱ��
    int remain; //ʣ���CPUʱ��
    int pnum;   //����������
    int laxity; //�ɳڶ�
    int deadtime[10];   //��ֹʱ��
    bool f; //�жϽ����Ƿ�����
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
