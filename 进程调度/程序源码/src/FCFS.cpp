#include "FCFS.h"

void FCFS::FCFScul(int process_amount,ofstream &outfileF)
{
	for(int i = 0; i < process_amount; i++)
	{
	    if(jcb[i].startTime<jcb[i].arriveTime)
        {
            jcb[i].startTime =jcb[i].arriveTime;
        }

        jcb[i].endTime=jcb[i].startTime+jcb[i].runTime;
        jcb[i].turnoverTime=jcb[i].endTime-jcb[i].arriveTime;
        jcb[i].weightTime=(float)jcb[i].turnoverTime/(float)jcb[i].runTime;

		jcb[i+1].startTime=jcb[i].endTime;
	}
}

void FCFS::RunFCFS()
{
    ifstream infile;
    ofstream outfileF;
    char jobName;
    int arriveTime;
    int runTime;
    int process_amount;
    infile.open("./input/input_fcfs.txt",ios::in);
    infile>>process_amount;
    for(int i=0;i<process_amount;i++){
        //读入进程名、到达时间、服务时间
        infile>>jobName;
        infile>>arriveTime;
        infile>>runTime;

        //赋值给JCB类型结构体temp
        temp.jobName=jobName;
        temp.arriveTime=arriveTime;
        temp.runTime=runTime;
        temp.startTime=0;
	 	temp.endTime=0;
	 	temp.turnoverTime=0;
	 	temp.weightTime=0.0;

	 	//temp结构体加入到JCB结构体类型的数组jcb中
	 	jcb.push_back(temp);
    }
    infile.close();

	sort(jcb.begin(),jcb.end(),Process::cmp);//排序

	outfileF.open("./output/outputFCFS.txt",ios::out);
	outfileF<<"进程运行顺序："<<endl;
	cout<<"进程运行顺序："<<endl;
    for(int i=0;i<process_amount;i++)
    {
        outfileF<<jcb[i].jobName<<"  ";
        cout<<jcb[i].jobName<<"  ";
    }
    cout<<endl;
	outfileF<<endl;
	FCFScul(process_amount,outfileF);
    Process::printJCB(jcb,process_amount,outfileF);
	outfileF.close();
 }
