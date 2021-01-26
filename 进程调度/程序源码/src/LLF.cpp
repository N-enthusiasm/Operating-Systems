#include "LLF.h"

void LLF::LLFProcess(int clock,ofstream &outfileLLF)//最低松弛度优先算法的核心部分
{

    int a=tcb[0].period*tcb[0].pnum;
	int b=tcb[1].period*tcb[1].pnum;
	if(0 == tcb[0].laxity)//表示如果当前A任务已经到达了临界条件即A任务松弛度为0时，此时要抢占处理机来执行任务A
	{
	    tcb[1].f=false;
	}
	if(0 == tcb[1].laxity)//表示如果当前B任务已经到达了临界条件即B任务松弛度为0时，此时要抢占处理机来执行任务B
	{
	    tcb[0].f=false;
	}
	if(a-clock > 20)//表示如果任务A当前周期内的运行任务已经完成，而且尚未进入下一周期，则任务A放弃处理机，让任务B执行任务
	{
	    tcb[1].f=true;
	}
	if(b-clock > 25)//表示如果任务B当前周期内的运行任务已经完成，而且尚未进入下一周期，则任务B放弃处理机，让任务A执行任务
	{
	    tcb[0].f=true;
	}


	tcb[0].laxity=a-tcb[0].remain-clock;//计算当前A任务的松弛度
    tcb[1].laxity=b-tcb[1].remain-clock;//计算当前B任务的松弛度
    //outfileLLF<<tcb[0].laxity<<"----"<<tcb[1].laxity<<endl;
    //outfileLLF<<tcb[0].f<<"----"<<tcb[1].f<<endl;
//如果A的松弛度小于B的松弛度且B没有在运行时，就是A运行
	if(tcb[0].laxity < false==tcb[1].laxity && tcb[1].f)//runb==false
	{
	   tcb[0].f=true;
		outfileLLF<<tcb[0].tcbName<<tcb[0].pnum<<"("<<tcb[0].cputime-tcb[0].remain+5<<")"<<'\t';
		cout<<tcb[0].tcbName<<tcb[0].pnum<<"("<<tcb[0].cputime-tcb[0].remain+5<<")"<<'\t';
		tcb[0].remain-=5;//运行时间
		if(0 == tcb[0].remain)
		{
		    tcb[0].f=true;
			tcb[0].remain=10;
			tcb[0].pnum++;
		}
	}
	else
	{
	    tcb[1].f=true;
        outfileLLF<<tcb[1].tcbName<<tcb[1].pnum<<"("<<tcb[1].cputime-tcb[1].remain+5<<")"<<'\t';
        cout<<tcb[1].tcbName<<tcb[1].pnum<<"("<<tcb[1].cputime-tcb[1].remain+5<<")"<<'\t';
		tcb[1].remain-=5;
		if(0 == tcb[1].remain)
		{
		    tcb[1].f=false;
			tcb[1].remain=25;
			tcb[1].pnum++;
		}

	}


}


int LLF::RunLLF()
{
    ifstream infile;
    ofstream outfileLLF;
    int clock=0;//clock中存放当前时间

    //读取文件
    infile.open("./input/input_LLF.txt",ios::in);
    int deadline=Process::readTCB(tcb,temp,infile); //读取要运行的总时间
    outfileLLF.open("./output/outputLLF.txt",ios::out);

    cout<<"进程运行顺序："<<endl;
	while(clock<=deadline)//在deadtime内进行最低松弛度优先的调用
	{
		LLFProcess(clock,outfileLLF);//调用最低松弛度优先算法
		clock+=5;//时间增加

		//clock++;
	}
	cout<<endl;
}
