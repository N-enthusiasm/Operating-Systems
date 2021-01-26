#include "LRU.h"
#include "Page.h"
#include <fstream>
#include <vector>
#include<conio.h>
#include <iostream>

using namespace std;

vector<Page> pages_LRU;
vector<int> usePageNumList_LRU;
int length = 0;
ifstream infile_LRU;
ofstream ofs_LRU;

void LRU::reSet(int cur)
{
    pages_LRU[cur].setCount(0);
}

void LRU::timeRefresh()
{
    for (int i = 0; i < pages_LRU.size(); ++i)
    {
        pages_LRU[i].inc();
    }
}


bool LRU::search(int pageId)
{
    for (int i = 0; i < pages_LRU.size(); ++i)
    {
        if (pages_LRU[i].getId() == pageId)
        {
            timeRefresh();
            reSet(i);
            return true;
        }
    }
    return false;
}

void LRU::replace(int pageId)
{
    int max = 0, perCount, outPageId = -1, cur = 0;
    for (int i = 0; i < pages_LRU.size(); ++i)
    {
        perCount = pages_LRU[i].getCount();
        if (max < perCount)
        {
            max = perCount;
            cur = i;
        }
    }
    outPageId = pages_LRU[cur].getId();
    timeRefresh();
    reSet(cur);
    pages_LRU[cur].setId(pageId);

    cout << "缺页，页号ID：" << pageId << "放入内存，页号ID：" << outPageId << "被替换" <<'\n';
    ofs_LRU << "缺页，页号ID：" << pageId << "放入内存，页号ID：" << outPageId << "被替换"<<'\n';
}

void LRU::running()
{
    count=0;
    lackTime=0;

    infile_LRU.open("./input.txt",ios::in);
    ofs_LRU.open("./result/resultLRU.txt",ios::out);

    Readfile(pages_LRU,usePageNumList_LRU,length,PRO_MEMORY,infile_LRU);

    for (int i = 0; i < length; ++i)
    {
        int pageId = usePageNumList_LRU[i];

        if (search(pageId))
        {
            cout << "内存中有ID为" << pageId << "的页面，不进行置换" <<'\n';
            ofs_LRU << "内存中有ID为" << pageId << "的页面，不进行置换"<<'\n';
        }
        else if (count < PRO_MEMORY)    //有空闲页
        {
            pages_LRU[count].setId(pageId);
            cout<<"缺页，页号ID:"<<pageId<<"放入内存"<<'\n';
            ofs_LRU<<"缺页，页号ID:"<<pageId<<"放入内存"<<'\n';
            timeRefresh();
            reSet(count);
            count++;
            lackTime++;
        }
        else
        {
            replace(pageId);
            lackTime++;
        }
        Schedule::Writefile(pages_LRU,ofs_LRU);
    }

    cout << "缺页次数为：" << lackTime << ",缺页率为：" << (float) lackTime / length << endl;
    ofs_LRU << "缺页次数为：" << lackTime << ",缺页率为：" << (float) lackTime / length<< "\n";
    ofs_LRU << "-----------------------------------------------------";
    ofs_LRU.close();
}
