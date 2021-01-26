#include "RR.h"

void RR::RRProcess(int process_amount,ofstream &outfileRR,int Time)
{
    int time = processRR[0].arriveTime;
    int sum = 0;
    int i,j;
    int id=0;               //就绪队列要发的“号码牌”，初始值为0
    int current_number = 0;   //当前执行的“号码牌”
    while(sum < process_amount)
    {
        for(i = 0;  i < process_amount; i++)
            if(current_number == processRR[i].number && 0 == processRR[i].sign_completion)
            {

                if(processRR[i].remaining_time <= Time)
                {
                    time = time + processRR[i].remaining_time;
                    processRR[i].sign_completion = 1;
                    processRR[i].endTime = time;
                    processRR[i].remaining_time = 0;

                    outfileRR<<processRR[i].jobName<<"  ";
                    cout<<processRR[i].jobName<<"  ";

                    sum++;
                    current_number++;
                    for(j = i + 1; j < process_amount; j++)
                        if(processRR[j].arriveTime <= time && 0 == processRR[j].number)
                        {
                            id++;
                            processRR[j].number = id;
                        }
                }

                else if(processRR[i].remaining_time > Time)
                {
                    time = time + Time;
                    processRR[i].remaining_time -= Time;

                    outfileRR<<processRR[i].jobName<<"  ";
                    cout<<processRR[i].jobName<<"  ";

                    current_number++;
                    for(j = i + 1; j < process_amount; j++)
                        if(processRR[j].arriveTime <= time && 0 == processRR[j].number)
                        {
                            id++;
                            processRR[j].number = id;
                        }
                    id++;
                    processRR[i].number = id;
                }
            }
        if(id < current_number && sum < process_amount)
        {
            for(i = 0; i <= process_amount; i++)
                if(0 == processRR[i].sign_completion)
                {
                    time = processRR[i].arriveTime;
                    id++;
                    processRR[i].number = id;
                    break;
                }
        }
    }
    for(int i = 0; i < process_amount; i++)
	{
		processRR[i].turnoverTime=processRR[i].endTime - processRR[i].arriveTime;
		processRR[i].weightTime =(float) processRR[i].turnoverTime/processRR[i].runTime;

	}
}
void RR::RunRR()     //初始化进程的信息
{
    ifstream infile;
    ofstream outfileRR;
    int process_amount;
    int Time;
    char jobName;
    int arriveTime;
    int runTime;

    infile.open("./input/inputRR.txt",ios::in);
    infile>>process_amount;
    infile>>Time;

    for(int i=0; i<process_amount; i++)
    {
        infile>>jobName;
        infile>>arriveTime;
        infile>>runTime;

        temp.jobName=jobName;
        temp.arriveTime=arriveTime;
        temp.runTime=runTime;
        temp.remaining_time = temp.runTime;
        temp.sign_completion = 0;
        temp.number = 0;

        //temp结构体加入到JCB结构体类型的数组processRR中
	 	processRR.push_back(temp);
    }
    infile.close();

    sort(processRR.begin(),processRR.end(),Process::cmp);//排序

    outfileRR.open("./output/outputRR.txt",ios::out);
    outfileRR<<"进程运行顺序："<<endl;
    cout<<"进程运行顺序："<<endl;

    RRProcess(process_amount,outfileRR,Time);
    cout<<endl;
    outfileRR<<endl;

    Process::printJCB(processRR,process_amount,outfileRR);

    outfileRR.close();
}
