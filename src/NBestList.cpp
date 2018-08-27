#include <iostream>
#include <stdbool.h>
#include <string.h>
#include <vector>
#include <algorithm>
#include "NBestList.h"

using namespace std;

NBestList :: NBestList(void){
	_totalComparisons = 0;
	_actualComparisons = 0;
	_nBestList = vector<NBestResult>();
}

bool cmd(const NBestResult &n1, const NBestResult &n2){
	return n1._score> n2._score;

}

bool NBestList :: getIsEmpty() {
	return _nBestList.size() == 0;
}

void NBestList :: AddResult(string name, double score, double distance,double angle) {
	NBestResult r = NBestResult(name, score, distance, angle);
	_nBestList.push_back(r);
}

void NBestList :: SortDescending() {
	sort(_nBestList.begin(), _nBestList.end(),cmd);
}

int NBestList :: getTotalComparisons() {
	return _totalComparisons;
}

void NBestList :: setTotalComparisons(int n) {
	_totalComparisons = n;
}

int NBestList :: getActualComparisons() {
	return _actualComparisons;
}

void NBestList :: setActualComparisons(int n) {
	_actualComparisons = n;
}

string NBestList :: getName(int index) {
	if (_nBestList.size() > 0) {
		NBestResult r = (NBestResult) _nBestList.at(index);
		return r.getName();
	}
	return "";
}

double NBestList :: getScore(int index) {
	if (_nBestList.size() > 0) {
		NBestResult r = (NBestResult) _nBestList.at(index);
		return r.getScore();
	}
	return -1.0;
}

int NBestList :: getListSize() {
	return _nBestList.size();
}
	
double NBestList :: getDistance(int index) {
	if (_nBestList.size() > 0) {
		NBestResult r = (NBestResult) _nBestList.at(index);
		return r.getDistance();
	}
	return -1.0;
}

double NBestList :: getAngle(int index) {
	if (_nBestList.size() > 0) {
		NBestResult r = (NBestResult) _nBestList.at(index);
		return r.getAngle();
	}
	return 0.0;
}

NBestResult NBestList :: get(int index) {
	if (0 <= index && index < _nBestList.size()) {
		return (NBestResult) _nBestList.at(index);
	}
}

string *NBestList :: getNames() {
	string *s = new string[_nBestList.size()];
	if (_nBestList.size() > 0) {
		for (int i = 0; i < _nBestList.size(); i++) {
			s[i] = ((NBestResult) _nBestList.at(i)).getName();
		}
	}
	return s;
}

string NBestList :: getNamesString() {
	string s = "";		
	if (_nBestList.size() > 0) {
		for (int i = 0; i<_nBestList.size();i++) {
			NBestResult r = _nBestList.at(i);
			s += r.getName();
		}
	}
	return s;
}

double *NBestList :: getScores() {
	double *s = new double[_nBestList.size()];
	if (_nBestList.size() > 0) {
		for (int i = 0; i < _nBestList.size(); i++) {
			s[i] = ((NBestResult) _nBestList.at(i)).getScore();
		}
	}
	return s;
}

string NBestList :: getScoresString() {
	string s = "";
	if (_nBestList.size() > 0) {
		for (int i = 0; i<_nBestList.size();i++) {
			NBestResult r = _nBestList.at(i);
			string s1 = to_string(Utils::round(r.getScore(), 3));
			s1 = s1.substr(0,s1.find('.')+4);
			s += s1;
		}		
	}
	return s;
}

/*
//Usage:
int main(){
	NBestList nb1;
	nb1.AddResult("Sree", 90,10,30);
	nb1.AddResult("Lucky", 100.45577,10,40);
	cout<<"nb1 details  NameString= "<<nb1.getNamesString()<<endl;
	cout<<" ScoresString = "<<nb1.getScoresString()<<endl;
	
	nb1.SortDescending();
	cout<<"\nDescending  details  NameString= "<<nb1.getNamesString()<<endl;
	cout<<" ScoresString = "<<nb1.getScoresString()<<endl;
	return 0;
}
*/

