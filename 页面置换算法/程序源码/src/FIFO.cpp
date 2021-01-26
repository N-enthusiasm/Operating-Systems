#include "Page.h"
#include "FIFO.h"
#include <iostream>
#include <vector>
#include <fstream>
#include<conio.h>

using namespace std;

vector<Page> pages; //物理块数组
vector<int> usePageNumList; //页面使用的列表

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
    //置换在内存中呆的时间最久的页面
    int outPageId = -1; //要被置换的页号ID
    outPageId = pages[countOldPoint].getId(); //countOldPoint是要被置换的页面下标
    pages[countOldPoint].setId(pageId); //当前位置放入新的页面
    cout << "缺页，页号ID：" << pageId << "放入内存，页号ID：" << outPageId << "被替换" << '\n';
    ofs_FIFO << "缺页，页号ID：" << pageId << "放入内存，页号ID：" << outPageId << "被替换"<<'\n';
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
        int inPageId = usePageNumList[i]; //按序取出页号ID
        if (search(inPageId))
        {
            cout << "内存中有ID为" << inPageId << "的页面，不进行置换" << '\n';
            ofs_FIFO << "内存中有ID为" << inPageId << "的页面，不进行置换"<<'\n';
        }
        else if (count < PRO_MEMORY)    //有空闲物理块
        {
            pages[count].setId(inPageId); //把当前页放入该物理块
            cout << "缺页，页号ID：" << inPageId << "放入内存中" << '\n';
            ofs_FIFO << "缺页，页号ID：" << inPageId << "放入内存中"<<'\n';
            count++; //物理块下标++
            lackTime++; //缺页次数++
        }
        else    //无空闲物理块，需要替换
        {
            replace(inPageId);
            lackTime++; //缺页次数++
            countOldPoint++; //要被置换的页面下标++
        }
        Schedule::Writefile(pages,ofs_FIFO);
    }
    cout << "缺页次数为：" << lackTime << ",缺页率为：" << (float) lackTime / length<< endl;
    ofs_FIFO << "缺页次数为：" << lackTime << ",缺页率为：" << (float) lackTime / length<< "\n";
    ofs_FIFO << "-----------------------------------------------------";
    ofs_FIFO.close();


}
