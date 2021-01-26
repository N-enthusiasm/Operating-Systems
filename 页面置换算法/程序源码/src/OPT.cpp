#include "OPT.h"
#include "Page.h"
#include <iostream>
#include<conio.h>
#include <vector>
#include <fstream>

using namespace std;

vector<Page>  pages_OPT; //物理块数组
vector<int> usePageNumList_OPT; //页面使用的列表
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
    /*max是最佳的页号ID，cur是最佳的物理块下标
      outPageId是要被置换出去的页号ID
      search_count数组
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

    //找出最佳的物理块下标及其存储的页号ID
    for (int k = 0; k < PRO_MEMORY; ++k)
    {
        perCount = search_count[k];
        if (max < perCount)
        {
            max = perCount;
            cur = k;
        }
    }

    outPageId = pages_OPT[cur].getId(); //要被置换出去的页号ID

    pages_OPT[cur].setId(pageId);
    cout << "缺页，页号ID：" << pageId << "放入内存，页号ID：" << outPageId << "被替换" <<'\n';
    ofs_OPT << "缺页，页号ID：" << pageId << "放入内存，页号ID：" << outPageId << "被替换"<<'\n';
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
            cout << "内存中有ID为" << pageId << "的页面，不进行置换" << '\n';
            ofs_OPT << "内存中有ID为" << pageId << "的页面，不进行置换"<<'\n';
        }
        else if (count < PRO_MEMORY)
        {
            pages_OPT[count].setId(pageId);
            cout << "缺页，页号ID:" << pageId << "放入内存" << '\n';
            ofs_OPT << "缺页，页号ID:" << pageId << "放入内存"<<'\n';
            count++;
            lackTime++;
        }
        else
        {
            replace(pageId); //传入当前下标确定需要遍历的未来输入列表
            lackTime++;
        }
        currentPoint++;
        Schedule::Writefile(pages_OPT,ofs_OPT);
    }

    cout << "缺页次数为：" << lackTime << ",缺页率为：" << (float) lackTime / length<< endl;
    ofs_OPT << "缺页次数为：" << lackTime << ",缺页率为：" << (float) lackTime / length<< "\n";
    ofs_OPT << "-----------------------------------------------------";
    ofs_OPT.close();
}
