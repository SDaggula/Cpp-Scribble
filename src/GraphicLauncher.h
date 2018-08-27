#ifndef GRAPHICLAUNCHER_H
#define GRAPHICLAUNCHER_H


#include <iostream>
#include <stdbool.h>
#include "PointR.h"
#include "NDollarRecognizer.h"
#include "ScribbleProcessor.h"

using namespace std;

class GraphicLauncher{
    	
	vector<PointR> points = vector<PointR>();
	vector<vector<PointR>> strokes = vector<vector<PointR>>();
	
    public:
	GraphicLauncher();

};

#endif
