#ifndef RR_H_INCLUDED
#define RR_H_INCLUDED

#include "prepare.h"
#include<iostream>
#include<fstream>//ÎÄ¼þÁ÷
#include<algorithm>
#include<iomanip>


using namespace std;

class RR:public Process
{
private:
    vector <JCB> processRR;
    JCB temp;
public:
    void RunRR();
    void RRProcess(int process_amount,ofstream &outfileRR,int Time);
};

#endif // RR_H_INCLUDED
