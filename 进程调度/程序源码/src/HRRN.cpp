#include "HRRN.h"

HRRN::HRRN()
{
 	ifstream infile;
    char jobName;
    int arriveTime;
    int runTime;
    int process_amount;

    infile.open("./input/input.txt",ios::in);
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
 }


void HRRN::loop(int i,vector<char> JobArray,int &currentTime,int &finishNumber)
{
    int process_amount = jcb.size();
	jcb[i].startTime=currentTime;

	jcb[i].endTime=jcb[i].startTime+jcb[i].runTime;

	jcb[i].turnoverTime=jcb[i].endTime-jcb[i].arriveTime;

	jcb[i].weightTime=jcb[i].turnoverTime*1.0/jcb[i].runTime;

	ofstream outfile;
    outfile.open("./output/outputHRRN.txt",ios::out);

	while(1)
	{
		if(currentTime==jcb[i].endTime)
		{
			jcb[i].sign_completion=1;

			finishNumber++;
			if(finishNumber==process_amount)
			{
			    	outfile<<"运行顺序:"<<endl;
                    outfile<<jcb[0].jobName<<" "<<JobArray[1]<<" "<<JobArray[2]<<" "<<JobArray[3]<<" "<<JobArray[4]<<endl;
                    cout<<"运行顺序:"<<endl;
                    cout<<jcb[0].jobName<<" "<<JobArray[1]<<" "<<JobArray[2]<<" "<<JobArray[3]<<" "<<JobArray[4]<<endl;
                    Process::printJCB(jcb,process_amount,outfile);
			}
			currentTime--;
			break;
		}
		else
		{
			currentTime++;
		}
	}
}

void HRRN::RunHRRN()
{
    int process_amount=jcb.size();
    int currentTime=0;
    int finishNumber=0;
	int i=0,j=0;
	vector<float> priority(MAX,0.0);
	vector<char> JobArray(MAX,'A');

	for(; finishNumber!=process_amount;currentTime++)
	{
		float maxPriority=0.0;
		int indexPriority=0;
		for(i=0;i<process_amount;i++)
		{
			if(jcb[i].sign_completion != 1)
			{
				int waitTime=currentTime-jcb[i].arriveTime;
				 priority[i]=(waitTime + jcb[i].runTime)*1.0/jcb[i].runTime;
				 if(priority[i]>maxPriority)
				{
			 		maxPriority=priority[i];
			 		indexPriority=i;
			 	}
			}
		}
		JobArray[j++]=jcb[indexPriority].jobName;
		loop(indexPriority,JobArray,currentTime,finishNumber);
	}
}
