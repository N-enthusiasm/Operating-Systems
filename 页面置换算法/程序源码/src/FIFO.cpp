#include "Page.h"
#include "FIFO.h"
#include <iostream>
#include <vector>
#include <fstream>
#include<conio.h>

using namespace std;

vector<Page> pages; //���������
vector<int> usePageNumList; //ҳ��ʹ�õ��б�

ifstream infile_FIFO;
ofstream ofs_FIFO;


bool FIFO::search(int pageId)
{
    for (int i = 0; i < pages.size(); i++)
    {
        if (pages[i].getId() == pageId)
            return true;
    }
    return false;
}

void FIFO::replace(int pageId)
{
    //�û����ڴ��д���ʱ����õ�ҳ��
    int outPageId = -1; //Ҫ���û���ҳ��ID
    outPageId = pages[countOldPoint].getId(); //countOldPoint��Ҫ���û���ҳ���±�
    pages[countOldPoint].setId(pageId); //��ǰλ�÷����µ�ҳ��
    cout << "ȱҳ��ҳ��ID��" << pageId << "�����ڴ棬ҳ��ID��" << outPageId << "���滻" << '\n';
    ofs_FIFO << "ȱҳ��ҳ��ID��" << pageId << "�����ڴ棬ҳ��ID��" << outPageId << "���滻"<<'\n';
}

void FIFO::running()
{
    count = 0;
    lackTime = 0;
    countOldPoint = 0;

    infile_FIFO.open("./input.txt",ios::in);
    ofs_FIFO.open("./result/resultFIFO.txt",ios::out);

    Readfile(pages,usePageNumList,length,PRO_MEMORY,infile_FIFO);

    for (int i = 0; i < length; i++)
    {
        countOldPoint = countOldPoint % PRO_MEMORY;
        int inPageId = usePageNumList[i]; //����ȡ��ҳ��ID
        if (search(inPageId))
        {
            cout << "�ڴ�����IDΪ" << inPageId << "��ҳ�棬�������û�" << '\n';
            ofs_FIFO << "�ڴ�����IDΪ" << inPageId << "��ҳ�棬�������û�"<<'\n';
        }
        else if (count < PRO_MEMORY)    //�п��������
        {
            pages[count].setId(inPageId); //�ѵ�ǰҳ����������
            cout << "ȱҳ��ҳ��ID��" << inPageId << "�����ڴ���" << '\n';
            ofs_FIFO << "ȱҳ��ҳ��ID��" << inPageId << "�����ڴ���"<<'\n';
            count++; //������±�++
            lackTime++; //ȱҳ����++
        }
        else    //�޿�������飬��Ҫ�滻
        {
            replace(inPageId);
            lackTime++; //ȱҳ����++
            countOldPoint++; //Ҫ���û���ҳ���±�++
        }
        Schedule::Writefile(pages,ofs_FIFO);
    }
    cout << "ȱҳ����Ϊ��" << lackTime << ",ȱҳ��Ϊ��" << (float) lackTime / length<< endl;
    ofs_FIFO << "ȱҳ����Ϊ��" << lackTime << ",ȱҳ��Ϊ��" << (float) lackTime / length<< "\n";
    ofs_FIFO << "-----------------------------------------------------";
    ofs_FIFO.close();


}
