#ifndef OPT_H
#define OPT_H

#include "Page.h"
//最佳置换算法，选择永远不再需要或者最长时间以后才需要访问的页面
class OPT : public Schedule
{
public:
    void running();
    bool search(int pageId);
    void replace(int pageId);

private:
    int PRO_MEMORY; //物理块数
    int count; //物理块下标
    int lackTime; //缺页次数
    int length; //页面队列的长度
};

#endif // OPT_H
