#include "Page.h"
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;
Page::Page(int id)
{
    this->id = id;
}

int Page::getId() const
{
    return this->id;
}

int Page::getCount() const
{
    return count;
}

void Page::inc()
{
    count++;
}

void Page::setId(int id)
{
    this->id = id;
}


void Page::setCount(int count)
{
    this->count = count;
}

void Schedule::Readfile(vector<Page> &pages,vector<int> &usePageNumList,int &length,int &PRO_MEMORY,ifstream &infile)
{
    int memory,len;
    infile >> memory;
    infile >> len;
    PRO_MEMORY = memory;
    length = len;

    int temp;
    for (int i = 0; i < length; i++)
    {
        infile >> temp;
        usePageNumList.push_back(temp);
    }

    for (int j = 0; j < PRO_MEMORY; j++)
    {
        Page *p = new Page(-1);
        pages.push_back(*p);
    }
}

void Schedule::Writefile(vector<Page> pages,ofstream &outfile)
{

    cout << "当前物理块中存储的页面是：";
    outfile << "当前物理块中存储的页面是：";
    for (int i = 0; i < pages.size(); i++)
    {
        cout << pages[i].getId() << " ";
        outfile << pages[i].getId() << " ";
    }
    cout << "\n----------------------------------------------\n";
    outfile << "\n----------------------------------------------\n";
}
