#include "EDF.h"

void EDF::EDFProcess(int &current,ofstream &outfile)
{
	int i,p;//i是被调度运行任务，p是所处周期的起始时间
	int runtime;//本次运行持续时间

	//选择最早截止时间的的任务.a、b是两个任务的最迟截止时间
	int a=tcb[0].period*tcb[0].pnum;
	int b=tcb[1].period*tcb[1].pnum;
	i = a<b?0:1;

	if(current<tcb[i].period*(tcb[i].pnum-1))//如果当前未进入最早截止时间任务的周期
	{
		p=tcb[i].period*(tcb[i].pnum-1);
		i=(i+1)%2;  //选择运行另一个任务

		if(current<tcb[i].period*(tcb[i].pnum-1))//如果未进入当前任务的周期
			current=p;

        /*如果当前任务的剩余运行时间小于等于下一周期的起始时间-当前时间，
        即能在当前周期运行完毕，那么就让他运行至结束*/
		else if(tcb[i].remain <= p-current)
			runtime = tcb[i].remain;

        /*如果当前任务的剩余运行时间大于下一周期的起始时间-当前时间，
        即不能在当前周期运行完毕，那么就让他运行到下个周期到来的时刻*/
		else
			runtime=p-current;

		tcb[i].remain-=runtime;

		outfile<<tcb[i].tcbName<<tcb[i].pnum<<"("<<runtime<<") ";
		cout<<tcb[i].tcbName<<tcb[i].pnum<<"("<<runtime<<") ";

		current+=runtime;//当前时间推进到下一调度时刻

		if(tcb[i].remain==0)//如果剩余运行时间为0，则说明本周期的任务已完成
		{
			tcb[i].pnum++;//任务编号推进到下一个
			tcb[i].remain=tcb[i].cputime;//设置初始剩余时间
		}
	}
	else //如果当前已经进入最早截止时间任务的周期
	{
		p=tcb[i].period*tcb[i].pnum;
		/*如果当前任务的剩余运行时间小于等于下一周期的起始时间-当前时间，
        即能在当前周期运行完毕，那么就让他运行至结束*/
		if(tcb[i].remain <= p-current)
			runtime = tcb[i].remain;

        /*如果当前任务的剩余运行时间大于下一周期的起始时间-当前时间，
        即不能在当前周期运行完毕，那么就让他运行到下个周期到来的时刻*/
		else
			runtime=p-current;

		tcb[i].remain -= runtime;//修改剩余时间

		outfile<<tcb[i].tcbName<<tcb[i].pnum<<"("<<runtime<<") ";
		cout<<tcb[i].tcbName<<tcb[i].pnum<<"("<<runtime<<") ";

		current+=runtime;//时间推进到下一调度时刻

		if(tcb[i].remain==0)
		{//本周期的任务已完成
			tcb[i].pnum++;//向前推进一个周期
			tcb[i].remain=tcb[i].cputime;//设置初始剩余时间
		}
	}
}

int EDF::RunEDF()
{
    int current=0; //当前时间

    ifstream infile;
    infile.open("./input/inputEDF.txt",ios::in);
	int totaltime = Process::readTCB(tcb,temp,infile); //读取要运行的总时间

    ofstream outfile;
    outfile.open("./output/outputEDF.txt",ios::out);

    cout<<"进程运行顺序："<<endl;
	while(current<totaltime)
        EDFProcess(current,outfile);
    cout<<endl;
}
