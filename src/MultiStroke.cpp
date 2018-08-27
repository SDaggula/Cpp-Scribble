#include <iostream>
#include <stdbool.h>
#include <string.h>
#include <algorithm>
#include "MultiStroke.h"

using namespace std;


MultiStroke :: MultiStroke(void){
	Name = "";
	User = "";
	Speed = "";
}

MultiStroke :: MultiStroke(string name, string user, string speed, vector<vector<PointR>> strokes){
	Name = name;
	User = user;
	Speed = speed;
	
	vector<PointR> points;
	for(int i=0;i<strokes.size();i++){
	    vector<PointR> pts = strokes.at(i); 
	    points.assign(pts.begin(), pts.end());
	}
	OriginalGesture = Gesture(name, points);

	NumStrokes = strokes.size();
		
		if (!NDollarParameters::ProcessUnistrokes
				&& NumStrokes == 1) {
			gestures = vector<Gesture>();
			gestures.push_back(OriginalGesture);
	
		} else {
			vector<int> defaultOrder = vector<int>(); 

			for (int i = 0; i < strokes.size(); i++) {
				defaultOrder.push_back(i); 
			}

			vector<vector<int>> allOrderings = vector<vector<int>>();

			HeapPermute(NumStrokes, defaultOrder, allOrderings);
			vector<vector<PointR>> unistrokes = MakeUnistrokes(strokes,
					allOrderings);

			gestures = vector<Gesture>();
			for (vector<PointR> entry : unistrokes) {
				Gesture newG = Gesture(Name, entry);
				gestures.push_back(newG);
			}
		}
}

void MultiStroke :: HeapPermute(int n, vector<int> currentOrder, vector<vector<int>> & allOrders) {

	if (n < 1)
		return;
	if (n == 1) 
	{
		allOrders.push_back(currentOrder); 

	} else {
			for (int i = 0; i < n; i++) {
			HeapPermute(n - 1, currentOrder, allOrders);
			if ((n % 2) == 1)
			{
				SwapStrokes(0, n - 1, currentOrder);
			} else 
			{
				SwapStrokes(i, n - 1, currentOrder);
			}
		}
	}
}

string MultiStroke :: toString() {
	string buf = "";
	buf = buf+"Multistring {name=" + Name + ", "+"user=" + User + ", "+"speed=" + Speed + ", "+"gestures=[";
	for (int i = 0; i < gestures.size(); ++i) {
		buf = buf+gestures.at(i).Name + " "; 
	}
	buf = buf + "]}";
	return buf;
}

void MultiStroke :: SwapStrokes(int first, int second, vector<int> order) {
		iter_swap(order.begin()+first, order.begin()+second);
	}

vector<vector<PointR>> MultiStroke :: MakeUnistrokes(vector<vector<PointR>> originalStrokes, vector<vector<int>> allOrderings) {
	vector<vector<PointR>> allUnistrokes = vector<vector<PointR>>(); 
	for (vector<int> ordering : allOrderings) {
		for (int b = 0; b < pow(2, ordering.size()); b++) 
																
		{
			vector<PointR> unistroke = vector<PointR>(); 
			for (int i = 0; i < ordering.size(); i++) 
			{
				vector<PointR> stroke = originalStrokes.at(ordering.at(i));
				if (((b >> i) & 1) == 1) 
				{
					reverse(stroke.begin(), stroke.end()); 
				}
				unistroke.assign(stroke.begin(), stroke.end()); 
			}
			allUnistrokes.push_back(unistroke);
		}
	}
	return allUnistrokes;
}

/*
//Usage:
int main(){
	PointR point1(10,20,11);
	PointR point2(10,30,11);
	PointR point3(10,40,11);

	vector<PointR> points;
	points.push_back(point1);
	points.push_back(point2);
	points.push_back(point3);

	vector<PointR> points2;
	points2.push_back(point1);
	points2.push_back(point2);
	points2.push_back(point3);

	vector<vector<PointR>> strokes;
	strokes.push_back(points);
	strokes.push_back(points2);

	MultiStroke point("Sree", "lucky", "10.08", strokes);
	
	cout<<"Point2 width "<<point1.X << endl;
	return 0;
}*/


