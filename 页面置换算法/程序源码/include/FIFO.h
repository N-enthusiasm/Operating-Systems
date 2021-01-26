#ifndef FIFO_H
#define FIFO_H

#include "Page.h"
//先进先出：选择先进入内存的页面予以淘汰
class FIFO : public Schedule
{
public:
    void running();
    bool search(int pageId);
    void replace(int pageId);

private:
    int PRO_MEMORY; //物理块数
    int countOldPoint; //要被置换的页面下标
    int count; //当前物理块的下标
    int lackTime; //缺页次数
    int length; //页面队列的长度
};

#endif // FIFO_H
