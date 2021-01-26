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
	 	temp.sign_completion = 0; //0��ʾ��û����1��ʾ�Ѿ����˵���δ��ɣ�-1��ʾ�����

	 	//temp�ṹ����뵽JCB�ṹ�����͵�����jcb��
	 	jcb.push_back(temp);
    }
    infile.close();

	sort(jcb.begin(),jcb.end(),cmp);//����
 }

void SJF::RunSJF(){
    int NUMBER = jcb.size();
    vector<int> remaning(NUMBER,0); //��¼����ʣ��ʱ��
    vector<char> JobOrder;//��¼����˳��


    for(int i=0; i<NUMBER;i++){
        remaning[i] = jcb[i].runTime;
    }

    int totalTime =0; //�������еĵ�ǰʱ��
    int i=0;
    int finish = 0; //��ɵĽ�������
    int current = 0; //��ǰ�Ѿ�����ġ�����ʱ����̵Ľ��̵��±�
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

        if(remaning[current] == jcb[current].runTime){ //���ʣ��ʱ��=����ʱ�䣬˵����û����
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
    outfile<<"����˳��:"<<endl;
    cout<<"����˳��:"<<endl;
    for(int i=0;i<JobOrder.size();i++)
    {
        outfile<<JobOrder[i]<<" ";
        cout<<JobOrder[i]<<" ";
    }
    cout<<endl;
    outfile<<endl;

    Process::printJCB(jcb,NUMBER,outfile);
}
