#ifndef LFU_H
#define LFU_H

#include "Page.h"

class LFU : public Schedule
{
public:
    void running();
    bool search(int pageId);
    void reSet(int cur);
    void timeRefresh();
    void replace(int pageId);
    //void display();

private:
    int PRO_MEMORY; //物理块数
    int count;
    int lackTime; //缺页次数
    int length; //页面队列的长度

};

#endif // LFU_H

