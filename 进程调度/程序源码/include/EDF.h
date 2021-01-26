#ifndef EDF_H_INCLUDED
#define EDF_H_INCLUDED

#include<stdio.h>
#include <iostream>
#include <fstream>
#include "prepare.h"

using namespace std;

class EDF:public Process
{
private:
    vector <TCB> tcb;
    TCB temp;
    Process p;
public:
    EDF(){

    }

    void EDFProcess(int &current,ofstream &outfile);
    int RunEDF();
};


#endif // EDF_H_INCLUDED
