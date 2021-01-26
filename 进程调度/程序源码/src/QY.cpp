#include "QY.h"

void QY::QYProcess(int process_amount,ofstream &outfile)     //抢占优先级调用过程
{
    int time = process[0].arriveTime;      //给当前时间赋初值
    //cout<<time<<endl;
    int number=0;    //记录完成的进程数
    int sumTime=time;
    for(int i=0;i<process_amount;i++){
        sumTime+=process[i].runTime;
    }
    vector<int> rtime(process_amount,0);
    for(int i=0;i<process_amount;i++){
        rtime[i]=process[i].runTime;
        //cout<<rtime[i];
    }
    //int tmp=100;
    while(number<process_amount)
    {
        vector<int> a(MAX,-1);//记录在某时刻之前到达且没运行结束的进程
        int id=0;//a的下标
        int nextid=0;//下一时刻要运行的进程
        for(int i=process[0].arriveTime;i<sumTime;i++)
        {
            //cout<<process[0].jobName<<endl;
            for(int j=0;j<process_amount;j++){
                if(process[j].arriveTime<=i && 0!=rtime[j]){
                    a[id]=j;
                    id++;
                }
            }//在i时刻之前到达的所有未运行结束的进程
            int tmp=MAX;//当前运行的进程的优先级

            for(int j=0;j<id;j++){
                if(process[a[j]].FQ <= 0!=tmp&&rtime[a[j]]){
                    tmp=process[a[j]].FQ;
                    nextid=a[j];//找到优先级最小的进程的下标
                }
            }
            //cout<<process[nextid].jobName<<endl;
            outfile<<process[nextid].jobName<<" ";
            cout<<process[nextid].jobName<<" ";

            rtime[nextid]--;
            if(0 == rtime[nextid]){
                process[nextid].endTime=i+1;
                number++;
            }
        }

    }
    for(int i = 0; i < process_amount; i++)
	{
		process[i].turnoverTime=process[i].endTime - process[i].arriveTime;
		process[i].weightTime =(float) process[i].turnoverTime/process[i].runTime;

	}

}
void QY::RunQY()     //初始化进程的信息
{
    ifstream infile;
    ofstream outfile;
    int process_amount;
    char jobName;
    int arriveTime;
    int runTime;
    int FQ;

    infile.open("./input/inputQY.txt",ios::in);

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
    outfile.open("./output/outputQY.txt",ios::out);

    outfile<<"进程运行顺序："<<endl;
    cout<<"进程运行顺序："<<endl;

    QYProcess(process_amount,outfile);
    cout<<endl;
    outfile<<endl;

    Process::printJCB(process,process_amount,outfile);

    outfile.close();
}
