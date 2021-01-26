#include "SRT.h"

void SRT::SRTProcess(struct JCB *h,int t,ofstream &outfile,int process_amount)
{
    int i,n,m,p,k,flag;
    vector<int> buff(process_amount,-1);
    vector<int> runtime(process_amount,-1);

    t=0;
    flag=0;
    m=0;
    for(i=0; i<process_amount; i++)
    {
        runtime[i]=jcb[i].runTime;
    }
    while(1)
    {
        for(n=0; n<process_amount; n++)
        {
            if(jcb[n].arriveTime==t)
            {
                buff[flag++]=n;
                break;
            }
        }
        if(runtime[buff[m]]==0)
        {
            jcb[buff[m]].endTime=t;
            flag--;
            if(flag==0)break;
            for(n=m; n<flag; n++)buff[n]=buff[n+1];
        }
        m=0;
        for(n=0; n<flag; n++)if(runtime[buff[n]]<runtime[buff[m]])m=n;
        h[t]=jcb[buff[m]];
        runtime[buff[m]]--;
        t++;
    }

    for(k=0; k<t; k++)
    {
        outfile<<h[k].jobName<<"  ";
    }
     for(k=0; k<t; k++)
    {
        cout<<h[k].jobName<<"  ";
    }

}
void SRT::SRTcul(int process_amount)
{
	for(int i = 0; i < process_amount; i++)
	{
	    if(jcb[i].startTime<jcb[i].arriveTime)
        {
            jcb[i].startTime =jcb[i].arriveTime;
        }

        jcb[i].turnoverTime=jcb[i].endTime-jcb[i].arriveTime;
        jcb[i].weightTime=(float)jcb[i].turnoverTime/(float)jcb[i].runTime;

		jcb[i+1].startTime=jcb[i].endTime;
	}
}


void SRT::RunSRT()
{
    ifstream infile;
    ofstream outfile;
    struct JCB h[MAX];
    char jobName;
    int arriveTime;
    int runTime;
    int process_amount;

    infile.open("./input/input_srt.txt",ios::in);

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

	outfile.open("./output/outputSRT.txt",ios::out);

	outfile<<"进程运行顺序："<<endl;
	cout<<"进程运行顺序："<<endl;

    SRTProcess(h,0,outfile,process_amount);
    cout<<endl;
	outfile<<endl;

	SRTcul(process_amount);
    Process::printJCB(jcb,process_amount,outfile);
	outfile.close();
}
