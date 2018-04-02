// **************************************************************************
//  File       [WorkerAnt.h]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The header file of worker ant]
//  Modify     [2015/03/20 Yu-Hao Ho]
// **************************************************************************

#ifndef _WORKERANT_H
#define _WORKERANT_H

#include <vector>
using namespace std;

class WorkerAnt {
public:
    WorkerAnt();
    vector<int>* DP(int, vector<int>&, vector<int>&, vector<int>&); //dynamic programming
    vector<int>* Greedy(int, vector<int>&, vector<int>&, vector<int>&);
private:
	int dist(int, int, int, vector<int>&, vector<int>&, vector<int>&);
};

#endif
