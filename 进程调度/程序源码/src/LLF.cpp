#include "LLF.h"

void LLF::LLFProcess(int clock,ofstream &outfileLLF)//����ɳڶ������㷨�ĺ��Ĳ���
{

    int a=tcb[0].period*tcb[0].pnum;
	int b=tcb[1].period*tcb[1].pnum;
	if(0 == tcb[0].laxity)//��ʾ�����ǰA�����Ѿ��������ٽ�������A�����ɳڶ�Ϊ0ʱ����ʱҪ��ռ�������ִ������A
	{
	    tcb[1].f=false;
	}
	if(0 == tcb[1].laxity)//��ʾ�����ǰB�����Ѿ��������ٽ�������B�����ɳڶ�Ϊ0ʱ����ʱҪ��ռ�������ִ������B
	{
	    tcb[0].f=false;
	}
	if(a-clock > 20)//��ʾ�������A��ǰ�����ڵ����������Ѿ���ɣ�������δ������һ���ڣ�������A�����������������Bִ������
	{
	    tcb[1].f=true;
	}
	if(b-clock > 25)//��ʾ�������B��ǰ�����ڵ����������Ѿ���ɣ�������δ������һ���ڣ�������B�����������������Aִ������
	{
	    tcb[0].f=true;
	}


	tcb[0].laxity=a-tcb[0].remain-clock;//���㵱ǰA������ɳڶ�
    tcb[1].laxity=b-tcb[1].remain-clock;//���㵱ǰB������ɳڶ�
    //outfileLLF<<tcb[0].laxity<<"----"<<tcb[1].laxity<<endl;
    //outfileLLF<<tcb[0].f<<"----"<<tcb[1].f<<endl;
//���A���ɳڶ�С��B���ɳڶ���Bû��������ʱ������A����
	if(tcb[0].laxity < false==tcb[1].laxity && tcb[1].f)//runb==false
	{
	   tcb[0].f=true;
		outfileLLF<<tcb[0].tcbName<<tcb[0].pnum<<"("<<tcb[0].cputime-tcb[0].remain+5<<")"<<'\t';
		cout<<tcb[0].tcbName<<tcb[0].pnum<<"("<<tcb[0].cputime-tcb[0].remain+5<<")"<<'\t';
		tcb[0].remain-=5;//����ʱ��
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
    int clock=0;//clock�д�ŵ�ǰʱ��

    //��ȡ�ļ�
    infile.open("./input/input_LLF.txt",ios::in);
    int deadline=Process::readTCB(tcb,temp,infile); //��ȡҪ���е���ʱ��
    outfileLLF.open("./output/outputLLF.txt",ios::out);

    cout<<"��������˳��"<<endl;
	while(clock<=deadline)//��deadtime�ڽ�������ɳڶ����ȵĵ���
	{
		LLFProcess(clock,outfileLLF);//��������ɳڶ������㷨
		clock+=5;//ʱ������

		//clock++;
	}
	cout<<endl;
}
