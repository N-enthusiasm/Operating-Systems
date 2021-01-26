#ifndef QY_H_INCLUDED
#define QY_H_INCLUDED

#include<iostream>
#include<fstream>
#include<algorithm>
#include<iomanip>
#include<vector>
#include "prepare.h"

using namespace std;

class QY:public Process
{
private:
    vector <JCB> process;
    JCB temp;

public:
    void RunQY();
    void QYProcess(int process_amount,ofstream &outfile);
};


#endif // QY_H_INCLUDED

