#ifndef HRRN_H_INCLUDED
#define HRRN_H_INCLUDED

#include <iostream>
#include <fstream>//ÎÄ¼þÁ÷
#include <cstring>
#include <algorithm>
#include <iomanip>
#include "prepare.h"


using namespace std;

class HRRN:public Process
{
private:
    vector <JCB> jcb;
    JCB temp;
public:
    HRRN();
    void RunHRRN();
    void loop(int i,vector<char> JobArray,int &currentTime,int &finishNumber);
};



#endif // HRRN_H_INCLUDED
