#ifndef LLF_H_INCLUDED
#define LLF_H_INCLUDED


#include<stdio.h>
#include <iostream>
#include <fstream>
#include "prepare.h"

using namespace std;

class LLF:public Process
{
private:
    vector <TCB> tcb;
    TCB temp;
public:
    void LLFProcess(int clock,ofstream &outfileLLF);
    int RunLLF();
};



#endif // LLF_H_INCLUDED
