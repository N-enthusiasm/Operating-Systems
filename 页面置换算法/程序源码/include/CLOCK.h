#ifndef CLOCK_H_INCLUDED
#define CLOCK_H_INCLUDED

#include "Page.h"

class CLOCK : public Schedule
{
public:
    void init();
    void running();
    bool search(int pageId);//�жϵ�ǰʱ���ڴ����Ƿ��и�ҳ��
    void replace(int pageId);//ҳ���û�

private:
    int PRO_MEMORY; //������� m
    int count;
    int lackTime; //ȱҳ����
    int length; //ҳ����еĳ��� n

};


#endif // CLOCK_H_INCLUDED
