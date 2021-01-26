#include "QY.h"

void QY::QYProcess(int process_amount,ofstream &outfile)     //��ռ���ȼ����ù���
{
    int time = process[0].arriveTime;      //����ǰʱ�丳��ֵ
    //cout<<time<<endl;
    int number=0;    //��¼��ɵĽ�����
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
        vector<int> a(MAX,-1);//��¼��ĳʱ��֮ǰ������û���н����Ľ���
        int id=0;//a���±�
        int nextid=0;//��һʱ��Ҫ���еĽ���
        for(int i=process[0].arriveTime;i<sumTime;i++)
        {
            //cout<<process[0].jobName<<endl;
            for(int j=0;j<process_amount;j++){
                if(process[j].arriveTime<=i && 0!=rtime[j]){
                    a[id]=j;
                    id++;
                }
            }//��iʱ��֮ǰ���������δ���н����Ľ���
            int tmp=MAX;//��ǰ���еĽ��̵����ȼ�

            for(int j=0;j<id;j++){
                if(process[a[j]].FQ <= 0!=tmp&&rtime[a[j]]){
                    tmp=process[a[j]].FQ;
                    nextid=a[j];//�ҵ����ȼ���С�Ľ��̵��±�
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
void QY::RunQY()     //��ʼ�����̵���Ϣ
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
        //���������������ʱ�䡢����ʱ��
        infile>>jobName;
        infile>>arriveTime;
        infile>>runTime;
        infile>>FQ;

        //��ֵ��JCB���ͽṹ��temp
        temp.jobName=jobName;
        temp.arriveTime=arriveTime;
        temp.runTime=runTime;
        temp.FQ=FQ;
        temp.startTime=0;
	 	temp.endTime=0;
	 	temp.turnoverTime=0;
	 	temp.weightTime=0.0;
	 	temp.sign_completion = 0;

	 	//temp�ṹ����뵽JCB�ṹ�����͵�����process��
	 	process.push_back(temp);

    }
    infile.close();

    sort(process.begin(),process.end(),Process::cmp);//����
    outfile.open("./output/outputQY.txt",ios::out);

    outfile<<"��������˳��"<<endl;
    cout<<"��������˳��"<<endl;

    QYProcess(process_amount,outfile);
    cout<<endl;
    outfile<<endl;

    Process::printJCB(process,process_amount,outfile);

    outfile.close();
}
