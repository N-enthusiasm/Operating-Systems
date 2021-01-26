#ifndef PAGE_H
#define PAGE_H
#include <fstream>
#include <vector>
using namespace std;

class Page
{
public:
    Page(int id); //构造函数
    int getId() const;
    int getCount() const;
    void inc(); //count自增一
    void setId(int id);
    void setCount(int count);
private:
    int id; //页号ID
    int count;
};

class Schedule
{
public:
    virtual void running() = 0; //具体实现过程
    virtual bool search(int pageId) = 0; //判断当前时间内存中是否有该页面
    virtual void replace(int pageId) = 0; //页面置换

    //读取文件
    void Readfile(vector<Page> &pages,vector<int> &usePageNumList,int &PRO_MEMORY,int &length,ifstream &infile);
    void Writefile(vector<Page> pages,ofstream &ofs);
};
#endif // PAGE_H
