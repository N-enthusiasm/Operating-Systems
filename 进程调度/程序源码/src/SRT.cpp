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
        //���������������ʱ�䡢����ʱ��
        infile>>jobName;
        infile>>arriveTime;
        infile>>runTime;

        //��ֵ��JCB���ͽṹ��temp
        temp.jobName=jobName;
        temp.arriveTime=arriveTime;
        temp.runTime=runTime;
        temp.startTime=0;
	 	temp.endTime=0;
	 	temp.turnoverTime=0;
	 	temp.weightTime=0.0;

	 	//temp�ṹ����뵽JCB�ṹ�����͵�����jcb��
	 	jcb.push_back(temp);
    }
    infile.close();

	sort(jcb.begin(),jcb.end(),Process::cmp);//����

	outfile.open("./output/outputSRT.txt",ios::out);

	outfile<<"��������˳��"<<endl;
	cout<<"��������˳��"<<endl;

    SRTProcess(h,0,outfile,process_amount);
    cout<<endl;
	outfile<<endl;

	SRTcul(process_amount);
    Process::printJCB(jcb,process_amount,outfile);
	outfile.close();
}
