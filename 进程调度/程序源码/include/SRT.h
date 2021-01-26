#ifndef SRT_H_INCLUDED
#define SRT_H_INCLUDED

#include<iostream>
#include<fstream>
#include<algorithm>
#include<iomanip>
#include<vector>
#include "prepare.h"


using namespace std;

class SRT:public Process
{
private:
    vector <JCB> jcb;
    JCB temp;
public:
    void RunSRT();
    void SRTcul(int process_amount);
    void SRTProcess(struct JCB *h,int t,ofstream &outfile,int process_amount);


};
#endif // SRT_H_INCLUDED
