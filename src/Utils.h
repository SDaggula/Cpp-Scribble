#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <stdbool.h>
#include <vector>
#include "RectangleR.h"
#include "PointR.h"
#include "SizeR.h"
#include "NDollarParameters.h"

using namespace std;

class Utils{
    public:

	static RectangleR FindBox(vector<PointR> points);
	static double round(double x, int d);
	static double Distance(PointR p1, PointR p2);
	static PointR Centroid(vector<PointR> points); 
	static double PathLength(vector<PointR> points);
	static double AngleInDegrees(PointR start, PointR end,	bool positiveOnly);
	static double AngleInRadians(PointR start, PointR end, bool positiveOnly);
	static double Rad2Deg(double rad); 
	static double Deg2Rad(double deg);
	static vector<PointR> RotateByDegrees(vector<PointR> points, double degrees);
	static vector<PointR> RotateByRadians(vector<PointR> points, double radians);
	static PointR RotatePoint(PointR p, PointR c, double radians);
	static PointR CalcStartUnitvector(vector<PointR> points, int index);
	static double AngleBetweenUnitvectors(PointR v1, PointR v2);
	static vector<PointR> TranslateBBoxTo(vector<PointR> points, PointR toPt);
	static vector<PointR> TranslateCentroidTo(vector<PointR> points, PointR toPt);   
	static vector<PointR> TranslateBy(vector<PointR> points, SizeR sz);
	static vector<PointR> ScaleTo(vector<PointR> points, SizeR sz);
	static vector<PointR> ScaleTo1D(vector<PointR> points, SizeR sz);
	static vector<PointR> ScaleBy(vector<PointR> points, SizeR sz);
	static vector<PointR> ScaleToMax(vector<PointR> points, RectangleR box);
	static vector<PointR> ScaleToMin(vector<PointR> points, RectangleR box);
	static double PathDistance(vector<PointR> path1, vector<PointR> path2);
	static int Random(int low, int high);
	static vector<int> Random(int low, int high, int num); 
	static vector<PointR> Scale(vector<PointR> pts, double oneDRatio,SizeR size);
	static vector<PointR> ScaleByDimension(vector<PointR> points, double oneDRatio, SizeR size);
	static vector<PointR> Resample(vector<PointR> points, int n);
	static bool Is1DGesture(vector<PointR> rawPts);
};


#endif
