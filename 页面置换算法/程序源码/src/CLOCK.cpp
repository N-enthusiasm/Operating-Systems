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
int page_in_block[200];//页面 i 在 block的下标索引
int index=0;//物理块下标

ifstream inFile_CLOCK;
ofstream ofs_CLOCK;

//判断页面是否在这个物理块中
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
            cout<<"缺页，页号ID："<<pageId<< "放入内存，页号ID：" <<pages_CLOCK[index].getId()<< "被替换" << '\n';
            ofs_CLOCK<<"缺页，页号ID："<<pageId<< "放入内存，页号ID：" <<pages_CLOCK[index].getId()<< "被替换"<<'\n';

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

    inFile_CLOCK >> PRO_MEMORY;//物理块数 m
    inFile_CLOCK >> length;//页面队列长度即总共有多少个页面 n

    int temp;
    for (int i = 0; i < length; i++)
    {
        inFile_CLOCK >> temp;//循环写入页面的排序
        usePageNumList_CLOCK.push_back(temp);//用堆栈的形式
    }

    for (int j = 0; j < PRO_MEMORY; j++)
    {
        Page *p = new Page(-1);
        pages_CLOCK.push_back(*p);
    }

    for (int i = 0; i < length; ++i)
    {
        int pageId = usePageNumList_CLOCK[i];//记录页面id号
        if (search(pageId))
        {
            cout <<"内存中有ID为" << pageId << "的页面，不进行置换" << '\n';
            ofs_CLOCK << "内存中有ID为" << pageId << "的页面，不进行置换"<<'\n';
        }

        else if (count < PRO_MEMORY)
        {//如果有空闲页就把当前页面放入到此物理块中，存储页面的id号
            pages_CLOCK[count].setId(pageId);
            cout<<"缺页，页号ID:"<<pageId<<"放入内存"<<'\n';
            ofs_CLOCK<<"缺页，页号ID:"<<pageId<<"放入内存"<<'\n';

            count++;
            lackTime++;//缺页次数增一，因为当此id页既不在内存页表中，物理块又有空闲页时，就一定是缺页的
        }

        //如果页面既不在页表中，又没有空闲页，那么就要进行页面置换，并将缺页次数加一
        else
        {
            replace(pageId);

        }
        Schedule::Writefile(pages_CLOCK,ofs_CLOCK);
    }

    cout << "缺页次数为：" << lackTime << ",缺页率为：" << (float) lackTime / length  << endl;
    ofs_CLOCK << "缺页次数为：" << lackTime << ",缺页率为：" << (float) lackTime / length  << "\n";
    ofs_CLOCK << "-----------------------------------------------------";
    ofs_CLOCK.close();
}
