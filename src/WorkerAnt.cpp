// **************************************************************************
//  File       [main.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The implementation of worker ant function]
//  Modify     [2015/03/20 Yu-Hao Ho]
// **************************************************************************
#include <iostream>
#include "WorkerAnt.h"
#include "stdlib.h"
#include "math.h"
#include <limits.h>
WorkerAnt::WorkerAnt() {}
vector<int>* WorkerAnt::DP(int weight, vector<int>& x, vector<int>& y, vector<int>& w)
{  
    int Number_of_food = x.size();
    vector<int> d, last_go_home; //d[i] for shortest distance to pick up i-th food and go home.
    d.push_back(0);
    for (int i = 0; i < Number_of_food + 1; i++) {
        last_go_home.push_back(0);
    }

    int tmp;
    for (int i = 1; i < Number_of_food + 1; i++) {
        int min = INT_MAX;
        for (int j = 0; j < i; j++) {
            tmp = d[j] + (x[j] + y[j]) + dist(weight, j, i - 1, x, y, w) + (x[i-1] + y[i-1]);
            if (tmp < min) {
                min = tmp;
                last_go_home[i] = j;	//last_go_home[i] means the last time go home (aka formicary) before pick up i-th food and go home.
            }
        }
        d[i]=min;
    }
    
    cout << "1" << endl;
    vector<int>* result = new vector<int>();
    cout << result <<endl;
	result->push_back(Number_of_food);	//Go home after pick up last food
    cout << "2" << endl;
    tmp = Number_of_food;
    for (; last_go_home[tmp] > 0;) {
    	cout << tmp << endl;
        tmp = last_go_home[tmp];
        cout << tmp << endl;
        result->push_back(tmp);
    }
    //result has the result we want (without final lenght yet) in inverted order

    //Invert result
    tmp = result->size();
    vector<int> tmp_vector;
    tmp_vector.reserve(tmp);
    for (int i = 0; i < tmp; i++) {
        tmp_vector[i] = (*result)[tmp - 1 - i];
    }
    for (int i = 0; i < tmp; i++) {
        (*result)[i] = tmp_vector[i];
    }


    result->push_back(d[Number_of_food]);

    return result;
}

vector<int>* WorkerAnt::Greedy(int weight, vector<int>& x, vector<int>& y, vector<int>& w)
{

    vector<int>* result = new vector<int>();
    int distance = abs(x[0]) + abs(y[0]);
    int load = w[0];
    int Number_of_food = x.size();
    for (int i = 1; i < Number_of_food; i++) {
        load = load + w[i];

        if (load > weight) {
            //After picking up food[i-1], carry it back to the formicary, then pick up food[i]
            result->push_back(i); //food[i-1] is i-th food
            load = w[i];
            distance += abs(x[i - 1]) + abs(y[i - 1]);
            distance += abs(x[i]) + abs(y[i]);
        }
        else {
            //From food[i-1], go pick up food[i]
            distance += abs(x[i] - x[i - 1]) + abs(y[i] - y[i - 1]);
        }
    }
    //From food[Number_of_food-1](last food), go to the formicary
    result->push_back(Number_of_food);
    distance += abs(x[Number_of_food - 1]) + abs(y[Number_of_food - 1]);

    result->push_back(distance);

    return result;
}

//Return the distance from food[start] go to food[end] without going home
//Return int(INT_MAX/2) if the food wight too much
int WorkerAnt::dist(int weight, int start, int end, vector<int>& x, vector<int>& y, vector<int>& w)
{
	int load = w[end];
	int distance = 0;
	for(int i = start; i<end;i++){
		load = load + w[i];
		distance = distance + abs(x[i]-x[i+1]) + abs(y[i]-y[i+1]);
	}
	//load = w[start] + w[start+1] + ...... + w[end]
	if(load > weight){
		return int(INT_MAX/2);		//Fail to carry the food from start to end
	}
    return distance;
}
