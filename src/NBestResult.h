#ifndef NBESTRESULT_H
#define NBESTRESULT_H

#include <iostream>
#include <stdbool.h>
#include <string.h>
#include <vector>

using namespace std;

class NBestResult{
    public:
	string _name;
	double _score;
	double _distance;
	double _angle;

    public:
	NBestResult();
	NBestResult(string name, double score, double distance, double angle); 

	string getName();
	double getScore();
	double getDistance();
	double getAngle();
	bool getIsEmpty();
	int compareTo(NBestResult r);
};

#endif
