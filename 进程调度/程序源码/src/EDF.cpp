#include "EDF.h"

void EDF::EDFProcess(int &current,ofstream &outfile)
{
	int i,p;//i�Ǳ�������������p���������ڵ���ʼʱ��
	int runtime;//�������г���ʱ��

	//ѡ�������ֹʱ��ĵ�����.a��b�������������ٽ�ֹʱ��
	int a=tcb[0].period*tcb[0].pnum;
	int b=tcb[1].period*tcb[1].pnum;
	i = a<b?0:1;

	if(current<tcb[i].period*(tcb[i].pnum-1))//�����ǰδ���������ֹʱ�����������
	{
		p=tcb[i].period*(tcb[i].pnum-1);
		i=(i+1)%2;  //ѡ��������һ������

		if(current<tcb[i].period*(tcb[i].pnum-1))//���δ���뵱ǰ���������
			current=p;

        /*�����ǰ�����ʣ������ʱ��С�ڵ�����һ���ڵ���ʼʱ��-��ǰʱ�䣬
        �����ڵ�ǰ����������ϣ���ô����������������*/
		else if(tcb[i].remain <= p-current)
			runtime = tcb[i].remain;

        /*�����ǰ�����ʣ������ʱ�������һ���ڵ���ʼʱ��-��ǰʱ�䣬
        �������ڵ�ǰ����������ϣ���ô���������е��¸����ڵ�����ʱ��*/
		else
			runtime=p-current;

		tcb[i].remain-=runtime;

		outfile<<tcb[i].tcbName<<tcb[i].pnum<<"("<<runtime<<") ";
		cout<<tcb[i].tcbName<<tcb[i].pnum<<"("<<runtime<<") ";

		current+=runtime;//��ǰʱ���ƽ�����һ����ʱ��

		if(tcb[i].remain==0)//���ʣ������ʱ��Ϊ0����˵�������ڵ����������
		{
			tcb[i].pnum++;//�������ƽ�����һ��
			tcb[i].remain=tcb[i].cputime;//���ó�ʼʣ��ʱ��
		}
	}
	else //�����ǰ�Ѿ����������ֹʱ�����������
	{
		p=tcb[i].period*tcb[i].pnum;
		/*�����ǰ�����ʣ������ʱ��С�ڵ�����һ���ڵ���ʼʱ��-��ǰʱ�䣬
        �����ڵ�ǰ����������ϣ���ô����������������*/
		if(tcb[i].remain <= p-current)
			runtime = tcb[i].remain;

        /*�����ǰ�����ʣ������ʱ�������һ���ڵ���ʼʱ��-��ǰʱ�䣬
        �������ڵ�ǰ����������ϣ���ô���������е��¸����ڵ�����ʱ��*/
		else
			runtime=p-current;

		tcb[i].remain -= runtime;//�޸�ʣ��ʱ��

		outfile<<tcb[i].tcbName<<tcb[i].pnum<<"("<<runtime<<") ";
		cout<<tcb[i].tcbName<<tcb[i].pnum<<"("<<runtime<<") ";

		current+=runtime;//ʱ���ƽ�����һ����ʱ��

		if(tcb[i].remain==0)
		{//�����ڵ����������
			tcb[i].pnum++;//��ǰ�ƽ�һ������
			tcb[i].remain=tcb[i].cputime;//���ó�ʼʣ��ʱ��
		}
	}
}

int EDF::RunEDF()
{
    int current=0; //��ǰʱ��

    ifstream infile;
    infile.open("./input/inputEDF.txt",ios::in);
	int totaltime = Process::readTCB(tcb,temp,infile); //��ȡҪ���е���ʱ��

    ofstream outfile;
    outfile.open("./output/outputEDF.txt",ios::out);

    cout<<"��������˳��"<<endl;
	while(current<totaltime)
        EDFProcess(current,outfile);
    cout<<endl;
}
