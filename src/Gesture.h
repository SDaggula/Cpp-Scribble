#ifndef GESTURE_H
#define GESTURE_H

#include <iostream>
#include <stdbool.h>
#include <string.h>
#include <vector>
#include "PointR.h"
#include "NDollarParameters.h"
#include "Utils.h"
#include "SizeR.h"

using namespace std;


class Gesture{
	public:
	    string Name;
	    double DX = 250.0; //Remove once updated in NDollarRecognizer
	    vector<PointR> RawPoints; 
	    vector<PointR> Points; 						
	    bool Is1D; 
	    vector<double>::iterator it; 
	    SizeR ResampleScale;//Remove once updated in NDollarRecognizer
	    PointR ResampleOrigin;//Remove once updated in NDollarRecognizer
							
	    PointR StartUnitvector; 
	    NDollarParameters params;
	    vector<double> vectorVersion;
 
	    Gesture();
	    Gesture(string name, vector<PointR> points) ;
	    Gesture(vector<PointR> points) ;

	    vector<double> vectorize(vector<PointR> pts); 
	    int getDuration();
	    static string ParseName(string filename); 
};

#endif
