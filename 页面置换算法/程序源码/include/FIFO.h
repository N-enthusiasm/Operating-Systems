#ifndef FIFO_H
#define FIFO_H

#include "Page.h"
//�Ƚ��ȳ���ѡ���Ƚ����ڴ��ҳ��������̭
class FIFO : public Schedule
{
public:
    void running();
    bool search(int pageId);
    void replace(int pageId);

private:
    int PRO_MEMORY; //�������
    int countOldPoint; //Ҫ���û���ҳ���±�
    int count; //��ǰ�������±�
    int lackTime; //ȱҳ����
    int length; //ҳ����еĳ���
};

#endif // FIFO_H
