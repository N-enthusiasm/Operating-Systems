#include "FQ.h"

void FQ::FQProcess(int process_amount,ofstream &outfileFQ)     //非抢占优先级调用过程
{
    int time = process[0].arriveTime;      //给当前时间赋初值
    int number=0;    //记录完成的进程数
    while(number<process_amount)
    {
        vector<int> a(MAX,-1);
        int id=0;

        for(int i=0; i<process_amount; i++)
        {
            if((process[i].arriveTime<=time)&&(process[i].sign_completion==0))
            {
                a[id]=i;
                id++;
            }
        }
        int tmp=10000;
        int aim;

        for(int j=0; j<id; j++)
        {
            if(process[a[j]].FQ<tmp)
            {
                tmp=process[a[j]].FQ;
                aim=a[j];
            }
        }

        outfileFQ<<process[aim].jobName<<"  ";
        cout<<process[aim].jobName<<"  ";

        process[aim].sign_completion=1;
        process[aim].endTime=time+process[aim].runTime;
        time=time+process[aim].runTime;
        number++;
    }
    for(int i = 0; i < process_amount; i++)
	{
		process[i].turnoverTime=process[i].endTime - process[i].arriveTime;
		process[i].weightTime =(float) process[i].turnoverTime/process[i].runTime;

	}
}

void FQ::RunFQ()     //初始化进程的信息
{
    ifstream infile;
    int process_amount;
    char jobName;
    int arriveTime;
    int runTime;
    int FQ;

    infile.open("./input/inputFQ.txt",ios::in);

    infile>>process_amount;
    for(int i=0; i<process_amount; i++)
    {
        //读入进程名、到达时间、服务时间
        infile>>jobName;
        infile>>arriveTime;
        infile>>runTime;
        infile>>FQ;

        //赋值给JCB类型结构体temp
        temp.jobName=jobName;
        temp.arriveTime=arriveTime;
        temp.runTime=runTime;
        temp.FQ=FQ;
        temp.startTime=0;
	 	temp.endTime=0;
	 	temp.turnoverTime=0;
	 	temp.weightTime=0.0;
	 	temp.sign_completion = 0;

	 	//temp结构体加入到JCB结构体类型的数组process中
	 	process.push_back(temp);

    }
    infile.close();

    sort(process.begin(),process.end(),Process::cmp);//排序

    ofstream outfileFQ;
    outfileFQ.open("./output/outputFQ.txt",ios::out);

    outfileFQ<<"进程运行顺序："<<endl;
    cout<<"进程运行顺序："<<endl;

    FQProcess(process_amount,outfileFQ);
    cout<<endl;
    outfileFQ<<endl;

    Process::printJCB(process,process_amount,outfileFQ);

    outfileFQ.close();
}
