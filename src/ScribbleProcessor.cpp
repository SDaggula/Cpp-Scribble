#include <iostream>
#include <stdbool.h>
#include <math.h>

#include <fstream>
#include <string>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <exception>
#include <algorithm>
#include "ScribbleProcessor.h"

using namespace std;


NDollarRecognizer ScribbleProcessor :: _rec = NDollarRecognizer();

ScribbleProcessor :: ScribbleProcessor(void){
	directionList = vector<int>();
	string samplesDir = NDollarParameters::SamplesDirectory;

	ifstream fin;

	string filepath;
  	int num; 
  	DIR *dp;
  	struct dirent *dirp;
  	struct stat filestat;

  	dp = opendir( samplesDir.c_str() );
  	if (dp == NULL)
 	{
 		cout << "Error(" << errno << ") opening " << samplesDir << endl;
    		return;
    	}

 	while ((dirp = readdir( dp )))
    	{
    		filepath = samplesDir + "/" + dirp->d_name;
				
		if(hasEnding(filepath, ".txt")){
			 _rec.LoadGesture(filepath);
		}
    		if (stat( filepath.c_str(), &filestat )) continue;
    		if (S_ISDIR( filestat.st_mode ))         continue;
		
    		
    	}

  	closedir( dp );
}

bool ScribbleProcessor :: hasEnding (std::string const &fullString, std::string const &ending) {
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}

void ScribbleProcessor :: setDigit(int d){
	digit = d;
}

void ScribbleProcessor :: resetToDefaults(){
        numberOfStrokes = 0;
        allPoints.clear();
        digit = -1;
        prevDigit = -1;
        pointerCount = 0;
}

void ScribbleProcessor :: resetConstants(){
        touch_west = false;
        touch_north = false;
        touch_east = false;
        touch_south = false;
        touch_northwest = false;
        touch_southeast = false;
        touch_southwest = false;
        touch_northeast = false;
        eastCount = 0;
        westCount = 0;
        northCount = 0;
        southCount = 0;
        northEastCount = 0;
        northWestCount = 0;
        southEastCount = 0;
        southWestCount = 0;
}

void ScribbleProcessor :: onActionDown(int x, int y, int count){
        pointerCount = count;
        if(numberOfStrokes == 1 && digit != -1){
	        prevDigit = digit;
        }
        allPoints.push_back(PointR(x, y));
        touch_start_x = touch_init_x = x;
        touch_start_y = touch_init_y = y;
        resetConstants();
        directionList.clear();
}

void ScribbleProcessor :: onActionUp(int x, int y, int count){
        allPoints.push_back(PointR(x, y));
        numberOfStrokes++;
        pointerCount = count;

        float dx = (x - touch_init_x);
        float dy = (y - touch_init_y);
        int length = (int)sqrt(dx * dx + dy * dy);
        //int angle = (int) (toDegrees(atan2(dy, dx)));
        int threshold_length = 25;
        int size = directionList.size();
        if(size>0){
 	      	//calculateDigit(directionList, angle);
        }else {
            if(length < threshold_length)
            	setDigit(1);
           // else
            //	calculateDigit(directionList, angle);
        }
        directionList.clear();
        //pointerCount = 0;
}

vector<string> ScribbleProcessor :: onTouchUp(int numStrokes, int pathLength){
        vector<string> data = vector<string>();
        if(pathLength >= 120  && numberOfStrokes == 2 && ((prevDigit == 5 && digit == 9 ) ||(prevDigit == 5 && digit == 13 )
                ||(prevDigit == 13 && digit == 5) ||(prevDigit == 9 && digit == 5 ))){
		cout<<"Cross"<<endl;
            data.push_back("11");
            data.push_back("100");
            resetToDefaults();
            return data;
        }else if (pathLength >= 120  && numberOfStrokes == 1 && digit == 13){
		cout<<"Back"<<endl;
            data.push_back("10");
            data.push_back("100");
            resetToDefaults();
            return data;
        }else if(pathLength >= 120){
		cout<<"Evaluated data"<<endl;
            data = evaluateResultData(numStrokes);
            resetToDefaults();
            return data;
        }else{
		cout<<"Error"<<endl;
            data.push_back("-1");
            data.push_back("100");
            resetToDefaults();
            return data;
        }
}

vector<string> ScribbleProcessor :: evaluateResultData(int numStrokes){
	vector<string> resultTxt;
        if (numStrokes > 0 && pointerCount == 1) {
            try {
		int siz = allPoints.size();
                if(allPoints.size()>5) {
                    //NBestList result1 = _rec.Recognize2(allPoints, numStrokes);
                    NBestList result = _rec.Recognize(allPoints, numStrokes);
		    resultTxt = vector<string>();
                    /*if (result1.getScore(0) != -1) {
                        int confidence = (int)(Utils::round(result1.getScore(0), 2) * 100);

                        if(confidence<90){
                            if (result.getScore(0) != -1) {
                                string data = result.getName(0);
                                resultTxt.push_back(data);

                                resultTxt.push_back(to_string(result.getScore(0)));

                            }
                        }else{
                            string data = result1.getName(0);
                            resultTxt.push_back(data);
                            resultTxt.push_back(to_string(result1.getScore(0)));

                        }
                    }else{
                        if (result.getScore(0) != -1) {
                            string data = result.getName(0);
                            resultTxt.push_back(data);

                            resultTxt.push_back(to_string(result.getScore(0)));
                        }
                    }*/

			if (result.getScore(0) != -1) {
                            string data = result.getName(0);
                            resultTxt.push_back(data);

                            resultTxt.push_back(to_string(result.getScore(0)));
                        }

                    return resultTxt;
                }
            }catch(exception& e){
		cout<<"An Exception Occured in evaluateDataResult. Exception: "<<endl;
	    }
        }
        return resultTxt;
}

void ScribbleProcessor :: calculateDigit(vector<int> dirList, int angle) {
        if (dirList.size() > 0) {

            if (dirList.size() == 1) {
                int direction = dirList.at(0);
                if (direction == northWest || direction == southEast) {
                    setDigit(5);
                } else if (direction == northEast || direction == southWest) {
                    setDigit(9);
                }else if (direction == west){
                    setDigit(13);
                }else{
                    setDigit(-1);
                }

            } else if (dirList.size() == 2) {
                if ((dirList.at(0)== southWest && dirList.at(1)==west)
                        || (dirList.at(0)== west && ((find(dirList.begin(), dirList.end(), southWest)!=dirList.end())||(find(dirList.begin(), dirList.end(), northWest)!=dirList.end())))) {
                    setDigit(13);
                }else if ((dirList.at(0) == east && dirList.at(1) == southEast)||(dirList.at(0) == southEast && dirList.at(1) == east)
                        ||(dirList.at(0) == west && dirList.at(1) == northWest)||(dirList.at(0) == northWest && dirList.at(1) == west)) {
                    if (((angle >= 20 && angle < 75) || (angle > -165 && angle < -120))) {
                        setDigit(5);
                    }
                } else if ((dirList.at(0) == southWest && dirList.at(1) == west) || (dirList.at(0) == west && dirList.at(1) == southWest)
                        ||(dirList.at(0) == northEast && dirList.at(1) == east) || (dirList.at(0) == east && dirList.at(1) == northEast)) {
                    if (((angle >= -75 && angle < -20) || (angle > 120 && angle < 165))) {
                        setDigit(9);
                    }
                }else{
                    setDigit(-1);
                }
            }
        }else {
            if (((angle >= 20 && angle < 75) || (angle > -165 && angle < -120))) {
                setDigit(5);
            }else if (((angle >= -75 && angle < -20) || (angle > 120 && angle < 165))) {
                setDigit(9);
            }else if (angle <= -160 || angle > 160) {
                setDigit(13);
            }
        }
}

void ScribbleProcessor :: onActionMove(int x, int y, int count){
    
	pointerCount = count;
        int COUNT_THRESHOLD = 0;
        float threshold = 1.0f;
        allPoints.push_back(PointR(x, y));

        int leftRightDiff =  (y - touch_start_y);
        int upDownDiff = (x - touch_start_x);
        if(pointerCount == 1) {
            if (leftRightDiff != 0 && upDownDiff != 0) {
                float ratioleftRightDiff = upDownDiff / leftRightDiff;
                float ratioupDownDiff = leftRightDiff / upDownDiff;
                int dist = (int) sqrt((upDownDiff * upDownDiff) + (leftRightDiff * leftRightDiff));
                if (ratioupDownDiff == 0 && abs(ratioleftRightDiff) > threshold && upDownDiff > 20 && abs(leftRightDiff) < 50) {
                    if (!touch_east) {
                        if ((dist > MAX_DISTANCE_THRESHOLD && eastCount == 0) || eastCount > COUNT_THRESHOLD) {
                            directionList.push_back(east);
                            eastCount = 0;
                            touch_east = true;
                        }
                    }
                    eastCount++;

                    touch_start_x = x;
                    touch_start_y = y;
                } else if (ratioupDownDiff == 0 && abs(ratioleftRightDiff) > threshold && upDownDiff < -20 && abs(leftRightDiff) < 50) {
                    if (!touch_west) {
                        if ((dist > MAX_DISTANCE_THRESHOLD && westCount == 0) || westCount > COUNT_THRESHOLD) {
                            directionList.push_back(west);
                            westCount = 0;
                            touch_west = true;
                        }
                    }

                    westCount++;
                    touch_start_x = x;
                    touch_start_y = y;
                } else if (ratioleftRightDiff == 0 && abs(ratioupDownDiff) > threshold && leftRightDiff > 20 && abs(upDownDiff) < 50) {
                    if (!touch_south) {
                        if ((dist > MAX_DISTANCE_THRESHOLD && southCount == 0) || southCount > COUNT_THRESHOLD) {
                            directionList.push_back(south);
                            southCount = 0;
                            touch_south = true;
                        }
                    }

                    southCount++;
                    touch_start_x = x;
                    touch_start_y = y;
                } else if (ratioleftRightDiff == 0 && abs(ratioupDownDiff) > threshold && leftRightDiff < -20 && abs(upDownDiff) < 50) {
                    if (!touch_north) {
                        if ((dist > MAX_DISTANCE_THRESHOLD && northCount == 0) || northCount > COUNT_THRESHOLD) {
                            directionList.push_back(north);
                            northCount = 0;
                            touch_north = true;
                        }
                    }

                    northCount++;
                    touch_start_x = x;
                    touch_start_y = y;
                } else if ((((ratioleftRightDiff == 0 || ratioleftRightDiff == 1) && ratioupDownDiff <= 0 && ratioupDownDiff >= -1 && leftRightDiff < -20 && upDownDiff > 20)
                        || ((ratioupDownDiff == 0 || ratioupDownDiff == 1) && (ratioleftRightDiff == 0 || ratioleftRightDiff == -1) && leftRightDiff < -20 && upDownDiff > 20))) {
                    if (!touch_northeast) {
                        if ((dist > MAX_DISTANCE_THRESHOLD && northEastCount == 0) || northEastCount > COUNT_THRESHOLD) {
                            directionList.push_back(northEast);
                            northEastCount = 0;
                            touch_northeast = true;
                        }
                    }

                    northEastCount++;
                    touch_start_x = x;
                    touch_start_y = y;
                } else if ((((ratioleftRightDiff == 0 || ratioleftRightDiff == 1) && ratioupDownDiff >= 0 && ratioupDownDiff <= 1 && leftRightDiff < -5 && upDownDiff < -5)
                        || ((ratioupDownDiff == 0 || ratioupDownDiff == 1) && (ratioleftRightDiff == 0 || ratioleftRightDiff == 1) && leftRightDiff < -5 && upDownDiff < -5))) {
                    if (!touch_northwest && ((dist > MAX_DISTANCE_THRESHOLD && northWestCount == 0) || northWestCount > COUNT_THRESHOLD)) {
                        directionList.push_back(northWest);
                        northWestCount = 0;
                        touch_northwest = true;
                    }
                    northWestCount++;

                    touch_start_x = x;
                    touch_start_y = y;
                } else if ((((ratioleftRightDiff == 0 || ratioleftRightDiff == 1 || ratioleftRightDiff == -1) && (ratioupDownDiff == 0 || ratioupDownDiff == 1)
                        && leftRightDiff > 20 && upDownDiff > 20)
                        || ((ratioupDownDiff == 0 || ratioupDownDiff == 1 || ratioupDownDiff == -1) && (ratioleftRightDiff == 0 || ratioleftRightDiff == -1)
                        && leftRightDiff < 20 && upDownDiff > 20))) {
                    if (!touch_southeast && ((dist > MAX_DISTANCE_THRESHOLD && southEastCount == 0) || southEastCount > COUNT_THRESHOLD)) {
                        directionList.push_back(southEast);
                        southEastCount = 0;
                        touch_southeast = true;
                    }

                    southEastCount++;
                    touch_start_x = x;
                    touch_start_y = y;
                } else if ((((ratioleftRightDiff == 0 || ratioleftRightDiff == 1 || ratioleftRightDiff == -1) && (ratioupDownDiff == 0 || ratioupDownDiff == -1)
                        && leftRightDiff > 20 && upDownDiff < -5)
                        || ((ratioupDownDiff == 0 || ratioupDownDiff == 1 || ratioupDownDiff == -1) && (ratioleftRightDiff == 0 || ratioleftRightDiff == -1)
                        && leftRightDiff < 80 && upDownDiff < -5))) {
                    if (!touch_southwest && ((dist > MAX_DISTANCE_THRESHOLD && southWestCount == 0) || southWestCount > COUNT_THRESHOLD)) {
                        directionList.push_back(southWest);
                        southWestCount = 0;
                        touch_southwest = true;
                    }
                    southWestCount++;

                    touch_start_x = x;
                    touch_start_y = y;
                }

            }
        }
}

/*
//Usage:
int main(){
	ScribbleProcessor s;
	
	return 0;
}*/
