#ifndef FCFS_H_INCLUDED
#define FCFS_H_INCLUDED

#include<iostream>
#include<fstream>
#include<algorithm>
#include<iomanip>
#include <vector>
#include "prepare.h"


using namespace std;

class FCFS:public Process
{
private:
    vector <JCB> jcb;
    JCB temp;
public:
    void FCFScul(int process_amount,ofstream &outfileF);
    void RunFCFS();
};

#endif // FCFS_H_INCLUDED
