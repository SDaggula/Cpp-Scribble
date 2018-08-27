#ifndef SIZER_H
#define SIZER_H


#include <iostream>
#include <stdbool.h>

using namespace std;

class SizeR{
    private:
	double _cx, _cy;

    public:
	SizeR();
	SizeR(double cx, double cy);  

	double getWidth();
	double getHeight();
	void setWidth(double w);
	void setHeight(double h);
 	bool equals(SizeR s);

};

#endif
