#ifndef LRU_H
#define LRU_H

#include "Page.h"
//最近最久未使用，选择最近一段时间最长时间没有被访问过的页面予以淘汰
class LRU : public Schedule
{
public:
    void running();
    bool search(int pageId);
    void reSet(int cur);
    void timeRefresh();
    void replace(int pageId);

private:
    int PRO_MEMORY; //物理块数
    int count;
    int lackTime; //缺页次数
    int length; //页面队列的长度

};

#endif // LRU_H
