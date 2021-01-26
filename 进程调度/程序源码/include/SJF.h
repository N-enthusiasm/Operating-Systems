#ifndef SJF_H_INCLUDED
#define SJF_H_INCLUDED

#include <iostream>
#include <fstream>//ÎÄ¼þÁ÷
#include <cstring>
#include <algorithm>
#include <iomanip>
#include "prepare.h"

using namespace std;

class SJF:public Process
{
private:
    vector <JCB> jcb;
    JCB temp;

public:
    SJF();
    void RunSJF();
};


#endif // SJF_H_INCLUDED
