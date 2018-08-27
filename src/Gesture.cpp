#include <iostream>
#include <stdbool.h>
#include <string.h>
#include <vector>
#include <math.h>
#include <cstddef>
#include "Gesture.h"

#define PI 3.14159265

using namespace std;


Gesture :: Gesture(void) {
	Name = "";
	Is1D = true; 
}

Gesture :: Gesture(string name, vector<PointR> points) {
	Name = name;
	RawPoints = points; 
	Points = RawPoints;
	ResampleScale = SizeR(DX,DX);
	ResampleOrigin = PointR(0,0);
	
	Points = Utils::Resample(Points,NDollarParameters::NumResamplePoints);
	double radians = Utils::AngleInRadians(Utils::Centroid(Points), Points.at(0), false);
	Points = Utils::RotateByRadians(Points, -radians);
	Is1D = Utils::Is1DGesture(RawPoints);
	Points = Utils::Scale(Points, NDollarParameters::_1DThreshold,ResampleScale);// Update with NDollarRecognizer::ResampleScale
	if (!NDollarParameters::RotationInvariant) {
		Points = Utils::RotateByRadians(points, +radians); 
	}
	
	Points = Utils::TranslateCentroidTo(Points,ResampleOrigin);// Update with NDollarRecognizer::ResampleOrigin	
	StartUnitvector = Utils::CalcStartUnitvector(Points,NDollarParameters::startAngleIndex);
	vectorVersion = vectorize(Points);
}

Gesture :: Gesture(vector<PointR> points) {
	Name = "";
	RawPoints = points; 
	Points = RawPoints;
	ResampleScale = SizeR(DX,DX);
	ResampleOrigin = PointR(0,0);
	
	Points = Utils::Resample(Points,NDollarParameters::NumResamplePoints);
	double radians = Utils::AngleInRadians(Utils::Centroid(Points), Points.at(0), false);
	Points = Utils::RotateByRadians(Points, -radians);
	Is1D = Utils::Is1DGesture(RawPoints);
	Points = Utils::Scale(Points, NDollarParameters::_1DThreshold,ResampleScale);// Update with NDollarRecognizer::ResampleScale
	if (!NDollarParameters::RotationInvariant) {
		Points = Utils::RotateByRadians(points, +radians); 
	}
	
	Points = Utils::TranslateCentroidTo(Points,ResampleOrigin);// Update with NDollarRecognizer::ResampleOrigin	
	StartUnitvector = Utils::CalcStartUnitvector(Points,NDollarParameters::startAngleIndex);
	vectorVersion = vectorize(Points);
}

int Gesture :: getDuration() {
	if (RawPoints.size() >= 2) {
		PointR p0 = (PointR) RawPoints.at(0);
		PointR pn = (PointR) RawPoints.at(RawPoints.size() - 1);
		return pn.T - p0.T;
	} else {
		return 0;
	}
}

vector<double> Gesture :: vectorize(vector<PointR> pts) {
	double cosval = 1.0;
	double sinval = 0.0;

	if (!params.RotationInvariant){
		double iAngle = atan2(pts.at(0).Y, pts.at(0).X);
		double baseOrientation = (PI / 4.0)* floor((iAngle + PI / 8.0) / (PI / 4.0));
		cosval = cos(baseOrientation - iAngle);
		sinval = sin(baseOrientation - iAngle);
	}
	double sum = 0.0;
	vector<double> vector;

	for (int i = 0; i < pts.size(); i++) {
		PointR p = pts.at(i);
		double newX = p.X * cosval - p.Y * sinval;
		double newY = p.Y * cosval + p.X * sinval;
		
		vector.push_back(newX);	
		vector.push_back(newY);
		sum += newX * newX + newY * newY;
	}
	
	double magnitude = sqrt(sum);

	for (int j = 0; j < vector.size(); j++) {
		vector[j] = vector.at(j) / magnitude;
	}
	
	return vector;
}

string Gesture :: ParseName(string filename) {
	int start = filename.find('\\');
	int end = filename.find('_');
	return filename.substr(start + 1, end);
}

/*
//Usage:
int main(){
	PointR point(10,20,11);
	PointR point2(100,200,11);

	vector<PointR> points;
	points.push_back(point);
	points.push_back(point2);

	Gesture gesture("Sree", points);

	
	return 0;
}*/







