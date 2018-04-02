// **************************************************************************
//  File       [main.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The main program of 2015 Spring Algorithm PA2]
//  Modify     [2015/03/20 Yu-Hao Ho]
// **************************************************************************

#include <cstring>
#include <iostream>
#include <fstream>
#include "../lib/tm_usage.h"
#include "WorkerAnt.h"

using namespace std;

void help_message()
{
    cout << "usage: WorkerAnt -[GD|DP] <input_file> <output_file>" << endl;
    cout << "options:" << endl;
    cout << "   GD  - Greedy" << endl;
    cout << "   DP  - Dynamic Programming" << endl;
}

int main(int argc, char* argv[])
{
    if (argc != 4) {
        help_message();
        return 0;
    }
    CommonNs::TmUsage tmusg;
    CommonNs::TmStat stat;

    //////////// read the input file /////////////
    int weight;
    fstream fin(argv[2]);
    fstream fout;
    fout.open(argv[3], ios::out);
    fin >> weight;
    int num1, num2, num3;
    fin >> num1; //Don't need Number of food
    vector<int> data1, data2, data3;
    while (fin >> num1 >> num2 >> num3) {
        data1.push_back(num1); //x-coordinate
        data2.push_back(num2); //y-coordinate
        data3.push_back(num3); //weight
    }

    //////////// find the solution to pick up the food ////
    tmusg.periodStart();
    WorkerAnt NTUWorkerAnt;
    vector<int>* result;
    if (strcmp(argv[1], "-GD") == 0) {
        result = NTUWorkerAnt.Greedy(weight, data1, data2, data3);
        // greedy
    }
    else if (strcmp(argv[1], "-DP") == 0) {
        result = NTUWorkerAnt.DP(weight, data1, data2, data3);
        // dynamic programming
    }
    else {
        help_message();
        return 0;
    }

    tmusg.getPeriodUsage(stat);
    //////////// write the output file ///////////
    for (int i = 0; i < result->size()-1; i++) {
        fout << (*result)[i] << endl;
    }
    fout << (*result)[result->size()-1];
    fin.close();
    fout.close();

    cout << "# run time = " << (stat.uTime + stat.sTime) / 1000000.0 << "sec" << endl;
    cout << "# memory =" << stat.vmPeak / 1000.0 << "MB" << endl;

    return 0;
}
