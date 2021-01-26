#ifndef LRU_H
#define LRU_H

#include "Page.h"
//������δʹ�ã�ѡ�����һ��ʱ���ʱ��û�б����ʹ���ҳ��������̭
class LRU : public Schedule
{
public:
    void running();
    bool search(int pageId);
    void reSet(int cur);
    void timeRefresh();
    void replace(int pageId);

private:
    int PRO_MEMORY; //�������
    int count;
    int lackTime; //ȱҳ����
    int length; //ҳ����еĳ���

};

#endif // LRU_H
