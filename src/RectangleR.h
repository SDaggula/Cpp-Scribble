#ifndef RECTANGLER_H
#define RECTANGLER_H


#include <iostream>
#include <stdbool.h>
#include <math.h>
#include "PointR.h"

using namespace std;

class RectangleR{
    private:
	int Digits;
	double _x, _y;
	double _width, _height;

    public:
	RectangleR();
	RectangleR(double x, double y, double width, double height);  

	double getX();
	double getY();
	void setX(double x);
	void setY(double y);

	double getWidth();
	double getHeight();
	void setWidth(double w);
	void setHeight(double h);

	PointR getTopLeft();
	PointR getBottomRight();
	PointR getCenter();
	double getMaxSide();
	double getMinSide();

	double round(double x, int Digits);
 	bool equals(RectangleR s);

};

#endif
