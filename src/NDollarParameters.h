#ifndef NDOLLARPARAMETERS_H
#define NDOLLARPARAMETERS_H


#include <iostream>
#include <stdbool.h>
#include <string.h>
#include <cmath>

using namespace std;

class NDollarParameters{
    public:
	NDollarParameters();
	static double Deg2Rad(double deg);
	static double Rad2Deg(double rad);
	static constexpr double _1DThreshold = 0.30;

	static string GestureSet;
	static string AlgorithmName;
	static const int AlgorithmVersion = 105;
	static string SamplesDirectory;
	static const bool RotationInvariant = false;
	static const bool ProcessUnistrokes = true;
	static const bool Include1D = true;
	static const bool Include2D = true;
	static const bool TestFor1D = true;
	static const bool UseUniformScaling = false;
	static const bool MatchOnlyIfSameNumberOfStrokes = true;
	static const bool DoStartAngleComparison = false;
	static const int startAngleIndex = 8;
	static constexpr double StartAngleThreshold = 0.523599;  //value of Deg2Rad(30);
	static const int NumResamplePoints = 32;
	enum PossibleSearchMethods {
		Protractor, 
		GSS
	};
	static const PossibleSearchMethods SearchMethod = GSS;
	
};

#endif
