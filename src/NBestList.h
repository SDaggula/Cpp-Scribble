#ifndef NBESTLIST_H
#define NBESTLIST_H

#include <iostream>
#include <stdbool.h>
#include <string.h>
#include <vector>
#include "NBestResult.h"
#include "Utils.h"

using namespace std;

class NBestList{
    private:
	string _name;
	
	vector<NBestResult> _nBestList;
	int _totalComparisons;
 	int _actualComparisons;

    public:
	NBestList();

	double *getScores();
	string getNamesString();
	string *getNames();
	NBestResult get(int index);
	double getAngle(int index);
	double getDistance(int index);
	int getListSize();
	double getScore(int index);
	string getName(int index);
	void setActualComparisons(int n);
	int getActualComparisons();
	void setTotalComparisons(int n);
	int getTotalComparisons();
	void SortDescending();
	void AddResult(string name, double score, double distance,double angle);
	bool getIsEmpty(); 
	string getScoresString();
};

#endif
