#include "Page.h"
#include "CLOCK.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <conio.h>
#include <cstdio>
#include <cstdio>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

vector<Page> pages_CLOCK;
vector<int> usePageNumList_CLOCK;
int nru[200];
int page_in_block[200];//ҳ�� i �� block���±�����
int index=0;//������±�

ifstream inFile_CLOCK;
ofstream ofs_CLOCK;

//�ж�ҳ���Ƿ�������������
bool CLOCK::search(int pageId)
{
    for (int i = 0; i < pages_CLOCK.size(); i++)
    {
        if (pages_CLOCK[i].getId() == pageId){
            return true;
        }
    }
    return false;
}

void CLOCK::replace(int pageId)
{
        if(nru[index] == 0)
        {
            nru[index] = 1;
            page_in_block[pages_CLOCK[index].getId()] = 0;
            cout<<"ȱҳ��ҳ��ID��"<<pageId<< "�����ڴ棬ҳ��ID��" <<pages_CLOCK[index].getId()<< "���滻" << '\n';
            ofs_CLOCK<<"ȱҳ��ҳ��ID��"<<pageId<< "�����ڴ棬ҳ��ID��" <<pages_CLOCK[index].getId()<< "���滻"<<'\n';

            page_in_block[pageId] = index;
            pages_CLOCK[index++].setId(pageId) ;
            lackTime++;
        }
        else
            nru[index++] = 0;
}


void CLOCK::running()
{
    inFile_CLOCK.open("./ClockInput.txt",ios::in);
    ofs_CLOCK.open("./result/resultCLOCK.txt",ios::out);

    count = 0;
    lackTime = 0;

    inFile_CLOCK >> PRO_MEMORY;//������� m
    inFile_CLOCK >> length;//ҳ����г��ȼ��ܹ��ж��ٸ�ҳ�� n

    int temp;
    for (int i = 0; i < length; i++)
    {
        inFile_CLOCK >> temp;//ѭ��д��ҳ�������
        usePageNumList_CLOCK.push_back(temp);//�ö�ջ����ʽ
    }

    for (int j = 0; j < PRO_MEMORY; j++)
    {
        Page *p = new Page(-1);
        pages_CLOCK.push_back(*p);
    }

    for (int i = 0; i < length; ++i)
    {
        int pageId = usePageNumList_CLOCK[i];//��¼ҳ��id��
        if (search(pageId))
        {
            cout <<"�ڴ�����IDΪ" << pageId << "��ҳ�棬�������û�" << '\n';
            ofs_CLOCK << "�ڴ�����IDΪ" << pageId << "��ҳ�棬�������û�"<<'\n';
        }

        else if (count < PRO_MEMORY)
        {//����п���ҳ�Ͱѵ�ǰҳ����뵽��������У��洢ҳ���id��
            pages_CLOCK[count].setId(pageId);
            cout<<"ȱҳ��ҳ��ID:"<<pageId<<"�����ڴ�"<<'\n';
            ofs_CLOCK<<"ȱҳ��ҳ��ID:"<<pageId<<"�����ڴ�"<<'\n';

            count++;
            lackTime++;//ȱҳ������һ����Ϊ����idҳ�Ȳ����ڴ�ҳ���У���������п���ҳʱ����һ����ȱҳ��
        }

        //���ҳ��Ȳ���ҳ���У���û�п���ҳ����ô��Ҫ����ҳ���û�������ȱҳ������һ
        else
        {
            replace(pageId);

        }
        Schedule::Writefile(pages_CLOCK,ofs_CLOCK);
    }

    cout << "ȱҳ����Ϊ��" << lackTime << ",ȱҳ��Ϊ��" << (float) lackTime / length  << endl;
    ofs_CLOCK << "ȱҳ����Ϊ��" << lackTime << ",ȱҳ��Ϊ��" << (float) lackTime / length  << "\n";
    ofs_CLOCK << "-----------------------------------------------------";
    ofs_CLOCK.close();
}
