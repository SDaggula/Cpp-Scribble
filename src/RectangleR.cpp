#include <iostream>
#include <stdbool.h>
#include <math.h>
#include "RectangleR.h"

using namespace std;

RectangleR :: RectangleR(void){
    _x = 0;
    _y = 0;
    _width = 0;
    _height = 0;
    Digits = 4;

}

RectangleR :: RectangleR(double x, double y, double width, double height){
    _x = x;
    _y = y;
    _width = width;
    _height = height;
    Digits = 4;
}


double RectangleR :: getX(){
    return round(_x, Digits);

}

double RectangleR :: getY(){
    return round(_y, Digits);
}

void RectangleR :: setX(double x){
     _x = x;

}

void RectangleR :: setY(double y){
    _y = y;
}


double RectangleR :: getWidth(){
    return round(_width, Digits);

}

double RectangleR :: getHeight(){
    return round(_height, Digits);
}

void RectangleR :: setWidth(double w){
     _width = w;

}

void RectangleR :: setHeight(double h){
    _height = h;
}

double RectangleR :: round(double x, int d){
    return (double)roundf(x*10*d)/(10*d);
}

PointR RectangleR :: getTopLeft(){
    return PointR(getX(), getY());

}

PointR RectangleR :: getBottomRight(){
    return PointR(getX()+getWidth(), getY()+getHeight());
}

PointR RectangleR :: getCenter(){
    return PointR(getX()+getWidth()/2, getY()+getHeight()/2);
}

double RectangleR :: getMaxSide(){
    return max(_width, _height);

}

double RectangleR :: getMinSide(){
    return min(_width, _height);
}

bool RectangleR :: equals(RectangleR r){
    return (_x == r._x && _y == r._y && _width == r._width && _height == r._height);
}


/*
//Usage:
int main(){
	RectangleR point(10,20.1, 30.66652, 40.227654);
	RectangleR point2, point3;
	point2 = RectangleR(10,22, 12, 13);
	point3 = point;
	cout<<"Point2 width "<<point2.getWidth() << endl;
	cout<<"Point1 height "<<point.getHeight() << endl;
	cout<<"Point2 == Point3 "<<"Is Equal? "<<point.equals(point3) << endl;
	cout<<"Point1 x = "<<point.getX() <<", y = "<<point.getY() <<", width = "<<point.getWidth() <<", height = "<<point.getHeight() << endl;
	return 0;
}*/

