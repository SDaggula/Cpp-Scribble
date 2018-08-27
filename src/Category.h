#ifndef CATEGORY_H
#define CATEGORY_H

#include <iostream>
#include <stdbool.h>
#include <string.h>
#include <vector>
#include "MultiStroke.h"

using namespace std;

class Category{
    private:
	string _name;
	vector<MultiStroke> _prototypes;

    public:
	Category();
	Category(string name); 
	Category(string name, MultiStroke firstExample);  
	Category(string name, vector<MultiStroke> examples);  

	string getName();
	int getNumExamples();
	MultiStroke get(int i);
	void AddExample(MultiStroke p);
	string ParseName(string s);
};

#endif
