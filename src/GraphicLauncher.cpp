#include <iostream>
#include <stdbool.h>
#include "GraphicLauncher.h"

using namespace std;



GraphicLauncher :: GraphicLauncher(void) {

}

int main(){

	ScribbleProcessor processor;

	//Points for gesture "0"

	processor.onActionDown(910,234,1);

	processor.onActionMove(885,239,1);
	processor.onActionMove(856,249,1);
	processor.onActionMove(830,264,1);
	processor.onActionMove(801,291,1);
	processor.onActionMove(771,330,1);

	processor.onActionMove(746,383,1);
	processor.onActionMove(729,438,1);
	processor.onActionMove(723,494,1);
	processor.onActionMove(728,548,1);
	processor.onActionMove(741,594,1);
	processor.onActionMove(762,635,1);

	processor.onActionMove(797,668,1);
	processor.onActionMove(846,698,1);
	processor.onActionMove(901,713,1);
	processor.onActionMove(956,716,1);
	processor.onActionMove(1009,708,1);
	processor.onActionMove(1053,687,1);

	processor.onActionMove(1088,656,1);
	processor.onActionMove(1116,605,1);
	processor.onActionMove(1129,547,1);
	processor.onActionMove(1124,491,1);
	processor.onActionMove(1107,441,1);
	processor.onActionMove(1088,397,1);

	processor.onActionMove(1060,354,1);
	processor.onActionMove(1027,312,1);
	processor.onActionMove(988,275,1);

	processor.onActionMove(946,249,1);
	processor.onActionMove(912,240,1);
	processor.onActionMove(881,252,1);

	processor.onActionUp(867, 264,1);
	vector<string> data = processor.onTouchUp(1, 200);// path formed by each stroke: num_strokes = 1; pathlength = 200
	cout<<"Vector size = "<<data.size()<<endl;
	if(data.size()>1){
		cout<<"Recognized: Name = "<<data.at(0)<<" Score = "<<data.at(1)<<endl;
	}
	return 0;
}















