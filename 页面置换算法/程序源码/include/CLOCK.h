#ifndef CLOCK_H_INCLUDED
#define CLOCK_H_INCLUDED

#include "Page.h"

class CLOCK : public Schedule
{
public:
    void init();
    void running();
    bool search(int pageId);//判断当前时间内存中是否有该页面
    void replace(int pageId);//页面置换

private:
    int PRO_MEMORY; //物理块数 m
    int count;
    int lackTime; //缺页次数
    int length; //页面队列的长度 n

};


#endif // CLOCK_H_INCLUDED
