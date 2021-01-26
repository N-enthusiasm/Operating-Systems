#include "OPT.h"
#include "Page.h"
#include <iostream>
#include<conio.h>
#include <vector>
#include <fstream>

using namespace std;

vector<Page>  pages_OPT; //���������
vector<int> usePageNumList_OPT; //ҳ��ʹ�õ��б�
int currentPoint;
ifstream infile_OPT;
ofstream ofs_OPT;

/*
void OPT::init()
{
    count = 0;
    lackTime = 0;
    Readfile(pages,PRO_MEMORY,infile)
}*/

bool OPT::search(int pageId)
{
    for (int i = 0; i < PRO_MEMORY; ++i)
    {
        if (pages_OPT[i].getId() == pageId)
        {
            return true;
        }
    }
    return false;
}

void OPT::replace(int pageId)
{
    /*max����ѵ�ҳ��ID��cur����ѵ�������±�
      outPageId��Ҫ���û���ȥ��ҳ��ID
      search_count����
    */
    int max = 0, perCount, outPageId = -1, cur = 0;
    int search_count[PRO_MEMORY];

    for (int i = 0; i < PRO_MEMORY; i++)
    {
        for (int j = currentPoint + 1; j < length; j++)
        {
            if (pages_OPT[i].getId() == usePageNumList_OPT[j])
            {
                search_count[i] = j;
                break;
            }
        }
        if (search_count[i] == 0)
        {
            search_count[i] = length;
        }
    }

    //�ҳ���ѵ�������±꼰��洢��ҳ��ID
    for (int k = 0; k < PRO_MEMORY; ++k)
    {
        perCount = search_count[k];
        if (max < perCount)
        {
            max = perCount;
            cur = k;
        }
    }

    outPageId = pages_OPT[cur].getId(); //Ҫ���û���ȥ��ҳ��ID

    pages_OPT[cur].setId(pageId);
    cout << "ȱҳ��ҳ��ID��" << pageId << "�����ڴ棬ҳ��ID��" << outPageId << "���滻" <<'\n';
    ofs_OPT << "ȱҳ��ҳ��ID��" << pageId << "�����ڴ棬ҳ��ID��" << outPageId << "���滻"<<'\n';
}

void OPT::running()
{
    count=0;
    lackTime=0;

    infile_OPT.open("./input.txt",ios::in);
    ofs_OPT.open("./result/resultOPT.txt", ios::out);

    Readfile(pages_OPT,usePageNumList_OPT,length,PRO_MEMORY,infile_OPT);

    for (int i = 0; i < length; ++i)
    {
        int pageId = usePageNumList_OPT[i];

        if (search(pageId))
        {
            cout << "�ڴ�����IDΪ" << pageId << "��ҳ�棬�������û�" << '\n';
            ofs_OPT << "�ڴ�����IDΪ" << pageId << "��ҳ�棬�������û�"<<'\n';
        }
        else if (count < PRO_MEMORY)
        {
            pages_OPT[count].setId(pageId);
            cout << "ȱҳ��ҳ��ID:" << pageId << "�����ڴ�" << '\n';
            ofs_OPT << "ȱҳ��ҳ��ID:" << pageId << "�����ڴ�"<<'\n';
            count++;
            lackTime++;
        }
        else
        {
            replace(pageId); //���뵱ǰ�±�ȷ����Ҫ������δ�������б�
            lackTime++;
        }
        currentPoint++;
        Schedule::Writefile(pages_OPT,ofs_OPT);
    }

    cout << "ȱҳ����Ϊ��" << lackTime << ",ȱҳ��Ϊ��" << (float) lackTime / length<< endl;
    ofs_OPT << "ȱҳ����Ϊ��" << lackTime << ",ȱҳ��Ϊ��" << (float) lackTime / length<< "\n";
    ofs_OPT << "-----------------------------------------------------";
    ofs_OPT.close();
}
