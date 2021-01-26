#include "SJF.h"

SJF::SJF()
{
    ifstream infile;
    int  NUMBER;
    char jobName;
    int arriveTime;
    int runTime;

    infile.open("./input/input.txt",ios::in);
    infile>>NUMBER;

    for(int i=0;i<NUMBER;i++){
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
	 	temp.sign_completion = 0; //0表示还没到，1表示已经到了但还未完成，-1表示已完成

	 	//temp结构体加入到JCB结构体类型的数组jcb中
	 	jcb.push_back(temp);
    }
    infile.close();

	sort(jcb.begin(),jcb.end(),cmp);//排序
 }

void SJF::RunSJF(){
    int NUMBER = jcb.size();
    vector<int> remaning(NUMBER,0); //记录运行剩余时间
    vector<char> JobOrder;//记录运行顺序


    for(int i=0; i<NUMBER;i++){
        remaning[i] = jcb[i].runTime;
    }

    int totalTime =0; //程序运行的当前时间
    int i=0;
    int finish = 0; //完成的进程数量
    int current = 0; //当前已经到达的、服务时间最短的进程的下标
    int flag = 1;
    while(totalTime >= 0){
        if((i<NUMBER) && (0 == jcb[i].sign_completion) && jcb[i].arriveTime <= totalTime){
            jcb[i].sign_completion = 1;
            i++;
        }

        if(flag == 1){
            int minValue = 1000;
            for(int k=0; k<NUMBER; k++){
                if((1 == jcb[k].sign_completion) && (minValue > jcb[k].runTime)){
                    minValue = jcb[k].runTime;
                    current = k;
                }
            }
            flag = 0;
        }

        if(remaning[current] == jcb[current].runTime){ //如果剩余时间=服务时间，说明还没运行
            jcb[current].startTime = totalTime;
        }

        JobOrder.push_back(jcb[current].jobName);

        remaning[current] -= 1;
        totalTime++;
        if(0 == remaning[current]){
            jcb[current].endTime = totalTime;
            jcb[current].turnoverTime=jcb[current].endTime-jcb[current].arriveTime;
		    jcb[current].weightTime=jcb[current].turnoverTime*1.0/jcb[current].runTime;

            jcb[current].sign_completion = -1;
            finish++;
            flag = 1;
        }

        if(finish == NUMBER){
            break;
        }
    }

    ofstream outfile;
    outfile.open("./output/outputSJF.txt",ios::out);
    outfile<<"运行顺序:"<<endl;
    cout<<"运行顺序:"<<endl;
    for(int i=0;i<JobOrder.size();i++)
    {
        outfile<<JobOrder[i]<<" ";
        cout<<JobOrder[i]<<" ";
    }
    cout<<endl;
    outfile<<endl;

    Process::printJCB(jcb,NUMBER,outfile);
}
