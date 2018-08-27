#include <iostream>
#include <stdbool.h>
#include "SizeR.h"

using namespace std;


SizeR :: SizeR(void){
    _cx = 0;
    _cy = 0;

}

SizeR :: SizeR(double cx, double cy){
    _cx = cx;
    _cy = cy;
}

double SizeR :: getWidth(){
    return _cx;

}

double SizeR :: getHeight(){
    return _cy;
}

void SizeR :: setWidth(double w){
     _cx = w;

}

void SizeR :: setHeight(double h){
    _cy = h;
}

bool SizeR :: equals(SizeR s){
    return (_cx == s._cx && _cy == s._cy);
}


/*int main(){
	SizeR point(10,20);
	SizeR point2, point3;
	point2 = SizeR(10,22);
	point3 = point;
	cout<<"Point2 width "<<point2.getWidth() << endl;
	cout<<"Point1 height "<<point.getHeight() << endl;
	cout<<"Point2 == Point3 "<<"Is Equal? "<<point2.equals(point3) << endl;
	cout<<"Point1 == Point3 "<<"Is Equal? "<<point.equals(point3) << endl;
	return 0;
}*/
