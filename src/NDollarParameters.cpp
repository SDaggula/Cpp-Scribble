#include <iostream>
#include <stdbool.h>
#include <string.h>
#include <cmath>
#include "NDollarParameters.h"

using namespace std;

string NDollarParameters :: SamplesDirectory = "samples";
string NDollarParameters :: GestureSet = "unistrokes";
string NDollarParameters :: AlgorithmName = "vDraw";
NDollarParameters :: NDollarParameters(void){
    
}

double NDollarParameters :: Deg2Rad(double deg){
    return (deg * M_PI / 180); 
}

double NDollarParameters :: Rad2Deg(double rad){
    return (rad * 180/ M_PI); 
}

/*
//Usage:
int main(){
	NDollarParameters point;
	cout<<"Point SearchMethod =  "<<point.SearchMethod << endl;
	cout<<"Point StartAngleThreshold =  "<<point.Deg2Rad(30)<< endl;
	//cout<<"Point StartAngleThreshold2 =  "<<point.StartAngleThreshold2 << endl;
	return 0;
}*/



