#include <iostream>
#include <stdbool.h>
#include <math.h>
#include <limits>
#include <cstdlib>
#include "Utils.h"

#define PI 3.14159265

using namespace std;

RectangleR Utils :: FindBox(vector<PointR> points){

	double minX = numeric_limits<double> :: max();
	double maxX = numeric_limits<double> :: min();
	double minY = numeric_limits<double> :: max();
	double maxY = numeric_limits<double> :: min();

	for (int i = 0;i<points.size();i++) {
		PointR p = points.at(i);

		if (p.X < minX)
			minX = p.X;
		if (p.X > maxX)
			maxX = p.X;
		if (p.Y < minY)
			minY = p.Y;
		if (p.Y > maxY)
			maxY = p.Y;
	}
	return RectangleR(minX, minY, maxX - minX, maxY - minY);
}

double Utils :: round(double x, int d){
    return (double)roundf(x*10*d)/(10*d);
}

double Utils :: Distance(PointR p1, PointR p2) {
	double dx = p2.X - p1.X;
	double dy = p2.Y - p1.Y;
	return sqrt(dx * dx + dy * dy);
}

PointR Utils :: Centroid(vector<PointR> points) {
	double xsum = 0.0;
	double ysum = 0.0;
	for (int i = 0;i<points.size();i++) {
		PointR p = points.at(i);
		xsum += p.X;
		ysum += p.Y;
	}
	return PointR(xsum / points.size(), ysum / points.size());
}

double Utils :: PathLength(vector<PointR> points) {
	double length = 0;
	for (int i = 1; i < points.size(); i++) {
		length += Distance((PointR) points.at(i - 1),(PointR) points.at(i));
	}
	return length;
}

double Utils :: AngleInDegrees(PointR start, PointR end, bool positiveOnly) {
	double radians = AngleInRadians(start, end, positiveOnly);
	return Rad2Deg(radians);
}

double Utils :: AngleInRadians(PointR start, PointR end, bool positiveOnly) {
	double radians = 0.0;
	if (start.X != end.X) {
		radians = atan2(end.Y - start.Y, end.X - start.X);
	} else{
		if (end.Y < start.Y)
			radians = -PI / 2.0; // -90 degrees is straight up
		else if (end.Y > start.Y)
			radians = PI / 2.0; // 90 degrees is straight down
	}
	if (positiveOnly && radians < 0.0) {
		radians += PI * 2.0;
	}
	return radians;
}

double Utils :: Rad2Deg(double rad) {
	return (rad * 180 / PI);
}

double Utils :: Deg2Rad(double deg) {
	return (deg * PI / 180);
}

vector<PointR> Utils :: RotateByDegrees(vector<PointR> points, double degrees) {
	double radians = Deg2Rad(degrees);
	return RotateByRadians(points, radians);
}

vector<PointR> Utils :: RotateByRadians(vector<PointR> points, double radians) {

	vector<PointR> newPoints = vector<PointR>();
	PointR c = Centroid(points);
	double cosval = cos(radians);
	double sinval = sin(radians);
	double cx = c.X;
	double cy = c.Y;
	for (int i = 0; i < points.size(); i++) {
		PointR p = (PointR) points.at(i);
		double dx = p.X - cx;
		double dy = p.Y - cy;
		PointR q =  PointR();
		q.X = dx * cosval - dy * sinval + cx;
		q.Y = dx * sinval + dy * cosval + cy;
		newPoints.push_back(q);
	}
	return newPoints;
}

PointR Utils :: RotatePoint(PointR p, PointR c, double radians) {
	PointR q = PointR();
	q.X = (p.X - c.X) * cos(radians) - (p.Y - c.Y) * sin(radians)+ c.X;
	q.Y = (p.X - c.X) * sin(radians) + (p.Y - c.Y) * cos(radians)+ c.Y;
	return q;
}

PointR Utils :: CalcStartUnitvector(vector<PointR> points, int index) {
	PointR v = PointR(((PointR) points.at(index)).X- ((PointR) points.at(0)).X, ((PointR) points.at(index)).Y - ((PointR) points.at(0)).Y);
	double len = sqrt(v.X * v.X + v.Y * v.Y);
	return PointR(v.X / len, v.Y / len);
}

double Utils :: AngleBetweenUnitvectors(PointR v1, PointR v2){
	double test = v1.X * v2.X + v1.Y * v2.Y; 
	if (test < -1.0)
		test = -1.0; 
	if (test > 1.0)
		test = 1.0; 
	return acos(test);
}

vector<PointR> Utils :: TranslateBBoxTo(vector<PointR> points, PointR toPt) {
	vector<PointR> newPoints = vector<PointR>();
	RectangleR r = FindBox(points);
	for (int i = 0; i < points.size(); i++) {
		PointR p = (PointR) points.at(i);
		p.X += (toPt.X - r.getX());
		p.Y += (toPt.Y - r.getY());
		newPoints.push_back(p);
	}
	return newPoints;
}

vector<PointR> Utils :: TranslateCentroidTo(vector<PointR> points, PointR toPt) {
	vector<PointR> newPoints = vector<PointR>();
	PointR centroid = Centroid(points);
	for (int i = 0; i < points.size(); i++) {
		PointR p = (PointR) points.at(i);
		p.X += (toPt.X - centroid.X);
		p.Y += (toPt.Y - centroid.Y);
		newPoints.push_back(p);
	}
	return newPoints;
}

vector<PointR> Utils :: TranslateBy(vector<PointR> points, SizeR sz) {
	vector<PointR> newPoints = vector<PointR>();
	for (int i = 0; i < points.size(); i++) {
		PointR p = (PointR) points.at(i);
		p.X += sz.getWidth();
		p.Y += sz.getHeight();
		newPoints.push_back(p);
	}
	return newPoints;
}

vector<PointR> Utils :: ScaleTo(vector<PointR> points, SizeR sz) {
	vector<PointR> newPoints = vector<PointR>(points.size());
	RectangleR r = FindBox(points);
	for (int i = 0; i < points.size(); i++) {
		PointR p = (PointR) points.at(i);
		if (r.getWidth() != 0)
			p.X *= (sz.getWidth() / r.getWidth());
		if (r.getHeight() != 0)
			p.Y *= (sz.getHeight() / r.getHeight());
		newPoints.push_back(p);
	}
	return newPoints;
}

vector<PointR> Utils :: ScaleTo1D(vector<PointR> points, SizeR sz) {
	vector<PointR> newPoints = vector<PointR>(points.size());
	RectangleR r = FindBox(points);

	double scaleFactor = 0.0;
	if (r.getWidth() > r.getHeight())
			scaleFactor = r.getWidth();
	else
		scaleFactor = r.getHeight();
	for (int i = 0; i < points.size(); i++) {
			PointR p = (PointR) points.at(i);
		if (r.getWidth() != 0)
			p.X *= (sz.getWidth() / scaleFactor);
		if (r.getHeight() != 0)
			p.Y *= (sz.getHeight() / scaleFactor);
		newPoints.push_back(p);
	}
	return newPoints;
}

vector<PointR> Utils :: ScaleBy(vector<PointR> points, SizeR sz) {
	vector<PointR> newPoints = vector<PointR>(points.size());
	for (int i = 0; i < points.size(); i++) {
		PointR p = (PointR) points.at(i);
		p.X *= sz.getWidth();
		p.Y *= sz.getHeight();
		newPoints.push_back(p);
	}
	return newPoints;
}

vector<PointR> Utils :: ScaleToMax(vector<PointR> points, RectangleR box) {
	vector<PointR> newPoints = vector<PointR>(points.size());
	RectangleR r = FindBox(points);
	for (int i = 0; i < points.size(); i++) {
		PointR p = (PointR) points.at(i);
		p.X *= (box.getMaxSide() / r.getMaxSide());
		p.Y *= (box.getMaxSide() / r.getMaxSide());
		newPoints.push_back(p);
	}
	return newPoints;
}

vector<PointR> Utils :: ScaleToMin(vector<PointR> points, RectangleR box) {
	vector<PointR> newPoints = vector<PointR>(points.size());
	RectangleR r = FindBox(points);
	for (int i = 0; i < points.size(); i++) {
		PointR p = (PointR) points.at(i);
		p.X *= (box.getMinSide() / r.getMinSide());
		p.Y *= (box.getMinSide() / r.getMinSide());
		newPoints.push_back(p);
	}
	return newPoints;
}

double Utils :: PathDistance(vector<PointR> path1, vector<PointR> path2) {
	double distance = 0;
	if(path1.size()<=path2.size()){
		for (int i = 0; i < path1.size(); i++) {
			distance += Distance((PointR) path1.at(i),
				(PointR) path2.at(i));
		}
	}else{
		for (int i = 0; i < path2.size(); i++) {
			distance += Distance((PointR) path1.at(i),
				(PointR) path2.at(i));
		}
	}
	return distance / path1.size();
}

int Utils :: Random(int low, int high) {
	return low + (int) (((double) high - (double) low) * rand());
}

vector<int> Utils :: Random(int low, int high, int num) {
	vector<int> array = vector<int>(num);
	for (int i = 0; i < num; i++) {
		array[i] = Random(low, high + 1);
		for (int j = 0; j < i; j++) {
			if (array.at(i) == array.at(j)) {
				i--; // redo i
				break;
			}
		}
	}
	return array;
}

vector<PointR> Utils :: Scale(vector<PointR> pts, double oneDRatio,SizeR size){

	if (NDollarParameters::UseUniformScaling){
		PointR centroid = Centroid(pts);
		double radiusSquared = 1.0d;
		for (int i = 0; i < pts.size(); i++) {
			PointR point = PointR((PointR) pts.at(i));  
			double distanceSquared = pow((centroid.X - point.X), 2.0)
					+ pow((centroid.Y - point.Y), 2.0);
			if (distanceSquared > radiusSquared)
				radiusSquared = distanceSquared;
		}
		double factor = size.getWidth() / sqrt(radiusSquared);
		vector<PointR> scaledPts = vector<PointR>();
		for (int i = 0; i < pts.size(); i++) {
			PointR p = PointR((PointR) pts.at(i));
			p.X *= factor;
			p.Y *= factor;
			scaledPts.push_back(p);
		}
		return scaledPts;
	} else{
		return ScaleByDimension(pts, oneDRatio, size);
	}
}

vector<PointR> Utils :: ScaleByDimension(vector<PointR> points, double oneDRatio, SizeR size){
	RectangleR B = FindBox(points);
	bool uniformly = false; 

	if (NDollarParameters::TestFor1D)
		uniformly = (min(B.getWidth() / B.getHeight(), B.getHeight()/ B.getWidth()) <= oneDRatio); 
	vector<PointR> newpoints = vector<PointR>();
	for (int i = 0; i < points.size(); i++) {
		double qx = uniformly ? ((PointR) points.at(i)).X
				* (size.getWidth() / max(B.getWidth(), B.getHeight()))
				: ((PointR) points.at(i)).X
						* (size.getWidth() / B.getWidth());
		double qy = uniformly ? ((PointR) points.at(i)).Y
				* (size.getHeight() / max(B.getWidth(), B.getHeight()))
				: ((PointR) points.at(i)).Y
						* (size.getHeight() / B.getHeight());
		newpoints.push_back(PointR(qx, qy));
	}
	return newpoints;
}

vector<PointR> Utils :: Resample(vector<PointR> points, int n) {
	double I = PathLength(points) / (n - 1); 
	double D = 0.0;
	vector<PointR> srcPts = vector<PointR>();
	
	for (int j = 0; j < points.size(); j++) {
		srcPts.push_back(points.at(j));
	}

	vector<PointR> dstPts = vector<PointR>(n);
	dstPts.push_back(srcPts.at(0));
	
	for (int i = 1; i < srcPts.size(); i++) {

		PointR pt1 = (PointR) srcPts.at(i - 1);
		PointR pt2 = (PointR) srcPts.at(i);
		double d = Distance(pt1, pt2);

		if ((D + d) >= I) {
			double qx = pt1.X + ((I - D) / d) * (pt2.X - pt1.X);
			double qy = pt1.Y + ((I - D) / d) * (pt2.Y - pt1.Y);
			PointR q = PointR(qx, qy);
			dstPts.push_back(q); 

			vector<PointR> :: iterator it = srcPts.begin()+i;
			srcPts.insert(it, q);
			D = 0.0;
		} else {
			D += d;
		}
	}

	if (dstPts.size() == n - 1) {
		dstPts.push_back(srcPts.at(srcPts.size() - 1));
	}

	return dstPts;
}

bool Utils :: Is1DGesture(vector<PointR> rawPts){
	vector<PointR> pts = vector<PointR>(rawPts);
	double radians = AngleInRadians(Centroid(pts), (PointR) pts.at(0), false);
	pts = RotateByRadians(pts, -radians); 
	RectangleR r = FindBox(pts);
	
	if ((r.getWidth() == 0) || (r.getHeight() == 0))
		return true;
	else if ((r.getWidth() / r.getHeight()) < (r.getHeight() / r.getWidth())){
		if ((r.getWidth() / r.getHeight()) < NDollarParameters::_1DThreshold)
			return true;
		else
			return false;
	} else{
		if ((r.getHeight() / r.getWidth()) < NDollarParameters::_1DThreshold)
			return true;
		else
			return false;
	}
}

/*
//Usage
int main(){
	PointR point(10,20,11);
	vector<PointR> points;
	points.push_back(point);	
		

	Utils::FindBox(points);
	
	return 0;
}*/
