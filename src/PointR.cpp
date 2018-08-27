#include <iostream>
#include <stdbool.h>
#include "PointR.h"

using namespace std;

PointR :: PointR(void){
    X = 0;
    Y = 0;
    T = 0;
}

PointR :: PointR(double x, double y){
    X = x;
    Y = y;
    T = 0;
} 

PointR :: PointR(double x, double y, double t){
    X = x;
    Y = y;
    T = t;
}


bool PointR :: equals(PointR p2){
    return (X == p2.X && Y == p2.Y);
}

bool PointR :: equals(PointR p1, PointR p2){
    return (p1.X == p2.X && p1.Y == p2.Y);
}

/*
//Usage
int main(){
	PointR point(10,20,11);
	PointR point2, point3;
	point2 = PointR(10,22,11);
	point3 = point;
	cout<<"Point2 == Point3 "<<"Is Equal? "<<point2.equals(point3) << endl;
	cout<<"Point1 == Point3 "<<"Is Equal? "<<point.equals(point3) << endl;
	return 0;
}*/
