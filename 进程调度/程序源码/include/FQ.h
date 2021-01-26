#ifndef FQ_H_INCLUDED
#define FQ_H_INCLUDED

#include<iostream>
#include<fstream>
#include<algorithm>
#include<iomanip>
#include<vector>
#include "prepare.h"



using namespace std;

class FQ:public Process
{
private:
    vector <JCB> process;
    JCB temp;
public:
    void RunFQ();
    void FQProcess(int process_amount,ofstream &outfileFQ);
};


#endif // FQ_H_INCLUDED
