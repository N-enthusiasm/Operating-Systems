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
    int PRO_MEMORY; //�������
    int count;
    int lackTime; //ȱҳ����
    int length; //ҳ����еĳ���

};

#endif // LFU_H

