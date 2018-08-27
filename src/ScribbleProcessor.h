#ifndef SCRIBBLEPROCESSOR_H
#define SCRIBBLEPROCESSOR_H


#include <iostream>
#include <stdbool.h>
#include <vector>
#include "PointR.h"
#include "Utils.h"
#include "NBestList.h"
#include "NDollarRecognizer.h"
#include "NDollarParameters.h"

using namespace std;

class ScribbleProcessor{
    private:
	int touch_start_x = -1;
	int touch_start_y = -1;
	int touch_init_x = -1;
	int touch_init_y = -1;
	int eastCount = 0;
    	int westCount = 0;
    	int northCount = 0;
    	int southCount = 0;
    	int northEastCount = 0;
    	int northWestCount = 0;
    	int southEastCount = 0;
    	int southWestCount = 0;
	
	bool touch_west = false;
    	bool touch_north = false;
        bool touch_east = false;
    	bool touch_south = false;
    	bool touch_northwest = false;
    	bool touch_southeast = false;
    	bool touch_southwest = false;
    	bool touch_northeast = false;

    	vector<int> directionList;
    	int northEast = 4;
	int southEast = 7;
	int east = 0;
	int northWest = 5;
	int southWest = 6;
	int west = 2;
	int north = 1;
	int south = 3;

    	int numberOfStrokes = 0;
    	int digit = -1;
    	int prevDigit = -1;
    	int MAX_DISTANCE_THRESHOLD = 500;
    	int pointerCount = 0;

	vector<PointR> allPoints = vector<PointR>();
	
	void resetToDefaults();
 	vector<string> evaluateResultData(int numStrokes);
	void resetConstants();
	
    public:
	ScribbleProcessor();
	static NDollarRecognizer _rec;
	bool hasEnding (std::string const &fullString, std::string const &ending); 
	void onActionDown(int x, int y, int count);  
	void onActionUp(int x, int y, int count);
	void onActionMove(int x, int y, int count);
	vector<string> onTouchUp(int numStrokes, int pathLength);
	void calculateDigit(vector<int> dirList, int angle);
	void setDigit(int d);

};

#endif
