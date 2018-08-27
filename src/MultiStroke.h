#ifndef MULTISTROKE_H
#define MULTISTROKE_H

#include <iostream>
#include <stdbool.h>
#include <string.h>
#include <vector>
#include "Gesture.h"
#include "PointR.h"
#include "SizeR.h"

using namespace std;

class MultiStroke{
    public:
	string Name, User, Speed;
	int NumStrokes;
	vector<Gesture> gestures;
	Gesture OriginalGesture;

	MultiStroke();
	MultiStroke(string name, string user, string speed, vector<vector<PointR>> strokes); 
	string toString();  
	vector<vector<PointR>> MakeUnistrokes(
			vector<vector<PointR>> originalStrokes,
			vector<vector<int>> allOrderings) ;
	void SwapStrokes(int first, int second, vector<int> order);
	void HeapPermute(int n, vector<int> currentOrder,
			vector<vector<int>> & allOrders); 
};

#endif
