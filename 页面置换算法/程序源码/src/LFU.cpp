#include "LFU.h"
#include "Page.h"
#include <fstream>
#include <vector>
#include<conio.h>
#include <iostream>
#include<string.h>
//������δʹ���㷨LFU
using namespace std;

vector<int> flag;
vector<Page> pages_LFU;
vector<int> usePageNumList_LFU;
ifstream infile;
ofstream ofs_LFU;

bool LFU::search(int pageId)
{
    for (int i = 0; i < pages_LFU.size(); ++i)
    {
        if (pages_LFU[i].getId() == pageId)
        {
            return true;
        }
    }
    return false;
}

void LFU::replace(int pageId)
{
}

void LFU::running()
{
    count=0;
    lackTime=0;

    infile.open("./input.txt",ios::in);
    ofs_LFU.open("./result/resultLFU.txt",ios::out);

    Readfile(pages_LFU,usePageNumList_LFU,length,PRO_MEMORY,infile);

    int outPageId=-1;
    for (int i = 0; i < length; ++i)
    {
        int pageId = usePageNumList_LFU[i];
        for(int j=0;j<100;j++)
        {
            flag.push_back(0);
        }
        flag[pageId]++;

        if (search(pageId))
        {
            cout << "�ڴ�����IDΪ" << pageId << "��ҳ�棬�������û�" << '\n';
            ofs_LFU << "�ڴ�����IDΪ" << pageId << "��ҳ�棬�������û�"<<'\n';
        }
        else if(count < PRO_MEMORY)
        {
            pages_LFU[count].setId(pageId);
            cout<<"ȱҳ��ҳ��ID:"<<pageId<<"�����ڴ�"<<'\n';
            ofs_LFU<<"ȱҳ��ҳ��ID:"<<pageId<<"�����ڴ�"<<'\n';
            count++;
            lackTime++;
        }
        else
        {
            int min=1000;
            int tmp;
            for(int j=0; j<PRO_MEMORY; j++)
            {
                if(min>flag[pages_LFU[j].getId()])
                {
                    min=flag[pages_LFU[j].getId()];
                    tmp=j;
                }
            }
            outPageId=pages_LFU[tmp].getId();
            pages_LFU[tmp].setId(pageId);
            cout << "ȱҳ��ҳ��ID��" << pageId << "�����ڴ棬ҳ��ID��" << outPageId << "���滻" << '\n';
            ofs_LFU << "ȱҳ��ҳ��ID��" << pageId << "�����ڴ棬ҳ��ID��" << outPageId << "���滻"<<'\n';
            lackTime++;
        }
        Schedule::Writefile(pages_LFU,ofs_LFU);

    }
    cout << "ȱҳ����Ϊ��" << lackTime << ",ȱҳ��Ϊ��" << (float) lackTime / length<< endl;
    ofs_LFU << "ȱҳ����Ϊ��" << lackTime << ",ȱҳ��Ϊ��" << (float) lackTime / length<< "\n";
    ofs_LFU << "-----------------------------------------------------";
    ofs_LFU.close();
}

