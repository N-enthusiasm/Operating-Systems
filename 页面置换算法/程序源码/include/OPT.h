#ifndef OPT_H
#define OPT_H

#include "Page.h"
//����û��㷨��ѡ����Զ������Ҫ�����ʱ���Ժ����Ҫ���ʵ�ҳ��
class OPT : public Schedule
{
public:
    void running();
    bool search(int pageId);
    void replace(int pageId);

private:
    int PRO_MEMORY; //�������
    int count; //������±�
    int lackTime; //ȱҳ����
    int length; //ҳ����еĳ���
};

#endif // OPT_H
