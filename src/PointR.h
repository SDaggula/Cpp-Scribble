#ifndef POINTR_H
#define POINTR_H

#include <iostream>
#include <stdbool.h>

using namespace std;

class PointR{
    public:
	double X, Y;
	int T;

	PointR();
	PointR(double x, double y);  
	PointR(double x, double y, double t);  

 	bool equals(PointR p2);
	bool equals(PointR p1, PointR p2);
};


#endif
