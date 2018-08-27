#include <iostream>
#include <stdbool.h>
#include <string.h>
#include <vector>
#include "NBestResult.h"

using namespace std;


NBestResult :: NBestResult(void) {
	_name = "";
	_score = -1;
	_distance = -1;
	_angle = 0;
}

NBestResult :: NBestResult(string name, double score, double distance, double angle) {
	_name = name;
	_score = score;
	_distance = distance;
	_angle = angle;
}

string NBestResult :: getName() {
	return _name;
}

double NBestResult :: getScore() {
	return _score;
}

double NBestResult :: getDistance() {
	return _distance;
}

double NBestResult :: getAngle() {
	return _angle;
}

bool NBestResult :: getIsEmpty() {
	return _score == -1;
}


int NBestResult :: compareTo(NBestResult r) {
	if (_score < r._score)
		return 1;
	else if (_score > r._score)
		return -1;
	return 0;
}

/*
//Usage:
int main(){
	NBestResult n1;
	NBestResult n2("S",90,10,30);
	NBestResult n3("L",100,11, 45);

	cout<<"n1 details  Name= "<<n1.getName()<<" Socre = "<<n1.getScore()<<" dist= "<<n1.getDistance()<<" Angle = "<<n1.getAngle()<<endl;
	cout<<"n2 details  Name= "<<n2.getName()<<" Socre = "<<n2.getScore()<<" dist= "<<n2.getDistance()<<" Angle = "<<n2.getAngle()<<endl;
	return 0;
}*/


