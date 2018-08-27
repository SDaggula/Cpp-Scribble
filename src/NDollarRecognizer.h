#ifndef NDOLLARRECOGNIZER_H
#define NDOLLARRECOGNIZER_H


#include <iostream>
#include <fstream>
#include <stdbool.h>
#include <unordered_map>
#include "PointR.h"
#include "SizeR.h"
#include "MultiStroke.h"
#include "NBestList.h"
#include "NDollarParameters.h"

using namespace std;

class NDollarRecognizer{
    private:
	static string NAMESPACE;
	static string VERSION;
	static const int _MinExamples = 5; 
	static double Phi;
	static int cnt;
	static constexpr double _RotationBound = 45.0; 
	static constexpr double DX = 250.0;
	static const int NumRandomTests = 100;
	unordered_map<string, MultiStroke> _gestures;
	unordered_map<string, MultiStroke> _gestures2;

    public:
	static SizeR ResampleScale;
	static double Diagonal;
	static double HalfDiagonal;
	static PointR ResampleOrigin;
	static constexpr double _1DThreshold = 0.30; 	
	
	NDollarRecognizer();
	NBestList Recognize(vector<PointR> points, int numStrokes);
	NBestList Recognize2(vector<PointR> points, int numStrokes);
	double *OptimalCosineDistance(vector<double> v1, vector<double> v2);
	double *GoldenSectionSearch(vector<PointR> pts1,vector<PointR> pts2, double a, double b, double threshold);
	int getGesturesSize();
	int getGestures2Size();
	void ClearGestures();
	void ClearGestures2();
	bool SaveGesture(string filename, vector<vector<PointR>> strokes, vector<int> numPtsInStroke); 

	bool LoadGesture(string filename) ;
	bool LoadGesture2(string filename);
	MultiStroke ReadGesture(string filename);

};

#endif
