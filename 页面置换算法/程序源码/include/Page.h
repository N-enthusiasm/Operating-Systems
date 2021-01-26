#ifndef PAGE_H
#define PAGE_H
#include <fstream>
#include <vector>
using namespace std;

class Page
{
public:
    Page(int id); //���캯��
    int getId() const;
    int getCount() const;
    void inc(); //count����һ
    void setId(int id);
    void setCount(int count);
private:
    int id; //ҳ��ID
    int count;
};

class Schedule
{
public:
    virtual void running() = 0; //����ʵ�ֹ���
    virtual bool search(int pageId) = 0; //�жϵ�ǰʱ���ڴ����Ƿ��и�ҳ��
    virtual void replace(int pageId) = 0; //ҳ���û�

    //��ȡ�ļ�
    void Readfile(vector<Page> &pages,vector<int> &usePageNumList,int &PRO_MEMORY,int &length,ifstream &infile);
    void Writefile(vector<Page> pages,ofstream &ofs);
};
#endif // PAGE_H
