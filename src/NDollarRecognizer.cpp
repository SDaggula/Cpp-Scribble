#include <iostream>
#include <stdbool.h>
#include <math.h>
#include <exception>
#include "NDollarRecognizer.h"

using namespace std;

double NDollarRecognizer :: Phi = 0.5 * (-1 + sqrt(5));
SizeR NDollarRecognizer :: ResampleScale = SizeR(DX, DX);
double NDollarRecognizer :: Diagonal = sqrt(DX * DX + DX * DX);
double NDollarRecognizer :: HalfDiagonal = 0.5 * Diagonal;
PointR NDollarRecognizer :: ResampleOrigin = PointR(0, 0);
string NDollarRecognizer :: NAMESPACE = "";
string NDollarRecognizer :: VERSION = "1.0";
int NDollarRecognizer :: cnt = 0;

NDollarRecognizer :: NDollarRecognizer(void){

}

NBestList NDollarRecognizer :: Recognize(vector<PointR> points, int numStrokes){
	Gesture candidate = Gesture(points);
	NBestList nbest = NBestList();
	int totalComparisons = 0;
	int actualComparisons = 0;
	for (auto gest : _gestures) {
		MultiStroke ms = gest.second;
		if (!NDollarParameters::MatchOnlyIfSameNumberOfStrokes || numStrokes == ms.NumStrokes) {
			NBestList thisMSnbest = NBestList(); 
			for (Gesture p : ms.gestures) {
				totalComparisons++;
				if (!NDollarParameters::DoStartAngleComparison
						|| (NDollarParameters::DoStartAngleComparison && 
							Utils::AngleBetweenUnitvectors(candidate.StartUnitvector,p.StartUnitvector) 
								<= NDollarParameters::StartAngleThreshold)) {
					actualComparisons++;
					double score = -1;
					double *best;
					if (NDollarParameters::SearchMethod == NDollarParameters::PossibleSearchMethods::GSS) {
						double a = Utils::Deg2Rad(-_RotationBound);
						double b = Utils::Deg2Rad(+_RotationBound);
						double c = Utils:: Deg2Rad(2.0);						
						best = GoldenSectionSearch(candidate.Points, p.Points, a, b,c);
						score = 1 - best[0] / HalfDiagonal;
					} else if (NDollarParameters::SearchMethod == NDollarParameters::PossibleSearchMethods::Protractor) {
						best = OptimalCosineDistance(p.vectorVersion,candidate.vectorVersion); 
						score = 1 / best[0]; 
					}
					thisMSnbest.AddResult(p.Name, score, best[0], best[1]);
				}
			}
			thisMSnbest.SortDescending();
			nbest.AddResult(thisMSnbest.getName(0), thisMSnbest.getScore(0),
					thisMSnbest.getDistance(0), thisMSnbest.getAngle(0)); 
		}
	}
	nbest.SortDescending(); 
	nbest.setTotalComparisons(totalComparisons);
	nbest.setActualComparisons(actualComparisons);
	return nbest;
}

NBestList NDollarRecognizer :: Recognize2(vector<PointR> points, int numStrokes){
	Gesture candidate = Gesture(points);
	NBestList nbest = NBestList();
	int totalComparisons = 0;
	int actualComparisons = 0;
	for (auto gest : _gestures2) {
		MultiStroke ms = gest.second;
		if (!NDollarParameters::MatchOnlyIfSameNumberOfStrokes
				|| numStrokes == ms.NumStrokes) {
			NBestList thisMSnbest = NBestList(); 
			for (Gesture p : ms.gestures) {
				totalComparisons++;
				if (!NDollarParameters::DoStartAngleComparison
						|| (NDollarParameters::DoStartAngleComparison && Utils::AngleBetweenUnitvectors(
								candidate.StartUnitvector,
								p.StartUnitvector) <= NDollarParameters::StartAngleThreshold)) {
					actualComparisons++;
					double score = -1;
					double *best;
					if (NDollarParameters::SearchMethod == NDollarParameters::PossibleSearchMethods::GSS) {
						best = GoldenSectionSearch(candidate.Points, 
								p.Points, 
								Utils::Deg2Rad(-_RotationBound), 
								Utils::Deg2Rad(+_RotationBound), 
								Utils::Deg2Rad(2.0));
						score = 1 - best[0] / HalfDiagonal;
					} else if (NDollarParameters::SearchMethod == NDollarParameters::PossibleSearchMethods::Protractor) {
						best = OptimalCosineDistance(p.vectorVersion,
								candidate.vectorVersion);
						score = 1 / best[0]; 
					}
					thisMSnbest.AddResult(p.Name, score, best[0], best[1]); 
				}
			}
			thisMSnbest.SortDescending();
			nbest.AddResult(thisMSnbest.getName(0), thisMSnbest.getScore(0),
					thisMSnbest.getDistance(0), thisMSnbest.getAngle(0)); 
		}
	}
	nbest.SortDescending(); 
	nbest.setTotalComparisons(totalComparisons);
	nbest.setActualComparisons(actualComparisons);
	
	return nbest;
}

int NDollarRecognizer :: getGesturesSize() {
	return _gestures.size();
}

int NDollarRecognizer :: getGestures2Size() {
	return _gestures2.size();
}

void NDollarRecognizer :: ClearGestures() {
	_gestures.clear();
}

void NDollarRecognizer :: ClearGestures2() {
	_gestures2.clear();
}

bool NDollarRecognizer :: LoadGesture(string filename) {
	bool success = true;
	try {
		MultiStroke p = ReadGesture(filename); 
		unordered_map<string, MultiStroke>:: const_iterator found = _gestures.find(p.Name);
		if (found!=_gestures.end()){
			p.Name = (p.Name+"-"+(to_string(++cnt)));
		}
		cout<<"FilePath = "<<filename<<" add "<<p.Name<<endl;
		pair<string, MultiStroke> point(p.Name, p);
		_gestures.insert(point);
		
	}catch(exception& e){
		success = false;
		cout<<"An Exception Occured while loading gesture. Exception: "<<endl;
	}
	return success;
}

bool NDollarRecognizer :: LoadGesture2(string filename) {
	bool success = true;
	try {
		MultiStroke p = ReadGesture(filename); 
		unordered_map<string, MultiStroke>:: const_iterator found2 = _gestures2.find(p.Name);
		if (found2!=_gestures2.end()){
			p.Name = (p.Name+"-"+(to_string(++cnt)));
		}
		cout<<"add "<<p.Name<<endl;
		pair<string, MultiStroke> point(p.Name, p);
		_gestures2.insert(point);
	
	}catch(exception& e){
		success = false;
		cout<<"An Exception Occured wile loading gesture2. Exception: "<<endl;
	} 
	return success;
}


bool NDollarRecognizer :: SaveGesture(string filename, vector<vector<PointR>> strokes, vector<int> numPtsInStroke) {
	string name = Gesture::ParseName(filename);

	MultiStroke newPrototype = MultiStroke(name, "test", "test", strokes);
	unordered_map<string, MultiStroke>:: const_iterator found = _gestures.find(name);
	unordered_map<string, MultiStroke>:: const_iterator found2 = _gestures2.find(name);
	if ((found!=_gestures.end()) || (found2!=_gestures2.end())){
		newPrototype.Name = (newPrototype.Name+"-"+(to_string(++cnt)));
	}
	vector<PointR> points = newPrototype.OriginalGesture.RawPoints;
	PointR p0 = points.at(0);
	PointR pn = points.at(points.size() - 1);

	bool success = true;
	bool indentation = true;
	
	try {	
		string::size_type sz;
		ofstream fwriter;
		fwriter.open("samples/sree.txt");
		fwriter<<"Name:\""<<name<<"\" ";
		fwriter<<"User:\"test\" ";
		fwriter<<"Speed:\"0.0\" ";
		fwriter<<"NumPts:\""<<to_string(points.size())<<"\" ";
		fwriter<<"Time:\""<<to_string((pn.T - p0.T))<<"\"\n";
		
		int numStrokesWritten = 0;

		for (int i=0;i<strokes.size();i++) {
			vector<PointR> pts = strokes.at(i);
			fwriter<<"Stroke:"<<(numStrokesWritten + 1)<<"\n";
			numStrokesWritten++;
			for (int j=0;j<pts.size();j++) {
				PointR p = pts.at(j);
				fwriter<<"x:"<<p.X<<" y:"<<p.Y<<" t:"<<p.T<<"\n";
			}
		}
		fwriter.close();
	} catch(exception& e){
		success = false;
		cout<<"An Exception Occured while saving gesture. Exception: "<<endl;
	}
	return success; 
}

double *NDollarRecognizer :: GoldenSectionSearch(vector<PointR> pts1, vector<PointR> pts2, double a, double b, double threshold) {
	double x1 = Phi * a + (1 - Phi) * b;
	vector<PointR> newPoints = Utils::RotateByRadians(pts1, x1);
	double fx1 = Utils::PathDistance(newPoints, pts2);
	double x2 = (1 - Phi) * a + Phi * b;
	newPoints = Utils::RotateByRadians(pts1, x2);
	double fx2 = Utils::PathDistance(newPoints, pts2);
	
	double i = 2.0; 
	while (abs(b - a) > threshold) {
		if (fx1 < fx2) {
			b = x2;
			x2 = x1;
			fx2 = fx1;
			x1 = Phi * a + (1 - Phi) * b;
			newPoints = Utils::RotateByRadians(pts1, x1);
			fx1 = Utils::PathDistance(newPoints, pts2);
		} else {
			a = x1;
			x1 = x2;
			fx1 = fx2;
			x2 = (1 - Phi) * a + Phi * b;
			newPoints = Utils::RotateByRadians(pts1, x2);
			fx2 = Utils::PathDistance(newPoints, pts2);
		}
		i++;
	}
	double *result = new double[3];
	result[0] = min(fx1, fx2);
	result[1] = Utils::Rad2Deg((b + a) / 2.0);
	result[2] = i;
	return result; 
}

double *NDollarRecognizer :: OptimalCosineDistance(vector<double> v1, vector<double> v2) {
	double a = 0;
	double b = 0;
	for (int i = 0; i < v1.size(); i = i + 2) {
		a = a + v1.at(i) * v2.at(i) + v1.at(i + 1)
				* v2.at(i + 1);
		b = b + v1.at(i) * v2.at(i + 1) - v1.at(i + 1)
				* v2.at(i);
	}
	double angle = atan(b / a);
	double *result = new double[3];
	result[0] = acos(a * cos(angle) + b * sin(angle));
	result[1] = Utils::Rad2Deg(angle);
	result[2] = 0; 
	return result;
}

MultiStroke NDollarRecognizer :: ReadGesture(string filename) {
	string name = "", user = "", speed = "", numpts = "", time = "";
	
	vector<PointR> points = vector<PointR>();
	vector<vector<PointR>> strokes = vector<vector<PointR>>();
	try {
		char data[1000];
		ifstream freader(filename.c_str(), ios::in); 
		if(freader){
			string line;
			while(getline(freader,line)){
				size_t found = line.find("Name:");
				size_t found2 = line.find("Stroke:");
				if(found!=string::npos){
					line = line.substr(6);
					name = line.substr(0,line.find(" ")-1);
					found = line.find("User:");
					if(found!=string::npos){
						line = line.substr(found+6);
						user = line.substr(0,line.find(" ")-1);
						found = line.find("Speed:");
						if(found!=string::npos){
							line = line.substr(found+7);
							speed = line.substr(0,line.find(" ")-1);
							found = line.find("NumPts:");
							if(found!=string::npos){
								line = line.substr(found+8);
								numpts = line.substr(0,line.find("\""));
								found = line.find("Time:");
								if(found!=string::npos){
									line = line.substr(found+6);
									time = line.substr(0,line.find("\"")-1);
								}
							}
						}
					}
				}else if(found2!=string::npos){	
					if(points.size() > 0) {
						strokes.push_back(points);
						points.clear();
					}
				}else{	
					string::size_type sz;	
					PointR p = PointR();	
					found = line.find("x:");
					if(found!=string::npos){
						string x = line.substr(found+2,line.find(" ")-1);
						p.X = stod(x, &sz);;
						found = line.find("y:");
						if(found!=string::npos){
							line = line.substr(found+2);
							string y = line.substr(0,line.find(" "));
							p.Y = stod(y, &sz);
							found = line.find("t:");
							if(found!=string::npos){
								line = line.substr(found+2);
								string t = line.substr(0,line.find(" ")-1);
								p.T = stoi(t, &sz);
							}
						}
					}
					points.push_back(p);					
				}
			}
		}
		
	}catch(exception& e){
		cout<<"An Exception Occured. Exception: "<<endl;
	}
	strokes.push_back(points);
	return MultiStroke(name, user, speed, strokes); 
}

/*
//Usage:
int main(){
	NDollarRecognizer n1;
	cout<<"Added gesture: "<<n1.LoadGesture("samples/test.txt")<<endl;
	return 0;
}*/
