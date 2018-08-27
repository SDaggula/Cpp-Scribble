#include <iostream>
#include <stdbool.h>
#include <string.h>
#include <vector>
#include "Category.h"

using namespace std;

Category :: Category(void){

}

Category :: Category(string name){
    _name = name;
}

Category :: Category(string name, MultiStroke firstExample){
    _name = name;
    _prototypes = vector<MultiStroke>();
    AddExample(firstExample);
}

Category :: Category(string name, vector<MultiStroke> examples){
    _name = name;
    _prototypes = vector<MultiStroke>();
    for(int i = 0; i < examples.size(); i++){
	MultiStroke p = examples.at(i);
	AddExample(p);
    }
}

string Category :: getName(){
    return _name;

}

int Category :: getNumExamples(){
    return _prototypes.size();
}

MultiStroke Category :: get(int i){
    if(0<=i && i< _prototypes.size()){
	return _prototypes.at(i);
    }
}

string Category :: ParseName(string s){
    string category = "";
    if(!s.find("~")){
	for(int i=s.length()-1; i>=0;i--){
	    if(!isdigit(s.at(i))){
		category = s.substr(0,i+1);
		break;
	    }
	}
    }else{
	category = s.substr(0,s.find("~"));
    }	
    return category;
}

void Category :: AddExample(MultiStroke p){
    bool success = true;
    try{
	string name = ParseName(p.Name);
	if(!name.compare(_name)==0) 
	    throw "prototype "+name+" does not equal the category "+_name+" to which it was added";
	for(int i = 0; i < _prototypes.size(); i++){
	    MultiStroke p0 = _prototypes.at(i);
	    if(p0.Name.compare(p.Name) == 0) 
		throw "prototype "+p0.Name+" was added more than once to its category";
	}
    }catch(string ex){
	cout<<"An Exception Occured. Exception "<<ex<<endl;
	success = false;
    }

    if(success){
	_prototypes.push_back(p);
    }
}

/*
//Usage:
int main(){
	PointR point1(10,20,11);
	PointR point2(10,30,11);
	PointR point3(10,40,11);

	vector<PointR> points;
	points.push_back(point1);
	points.push_back(point2);
	points.push_back(point3);

	vector<PointR> points2;
	points2.push_back(point1);
	points2.push_back(point2);
	points2.push_back(point3);

	vector<vector<PointR>> strokes;
	strokes.push_back(points);
	strokes.push_back(points2);

	MultiStroke point("Sree", "lucky", "10.08", strokes);
	Category cat("Sree",point);
	return 0;
}*/

