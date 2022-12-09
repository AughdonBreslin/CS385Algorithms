/*******************************************************************************
 * Name    : triangle.cpp
 * Author  : Aughdon Breslin
 * Date    : Nov 16, 2022
 * Description : Fun personal project to create Sierpinski triangles!
 ******************************************************************************/

#include <iostream>
#include <sstream>
#include <iomanip>
#include <math.h>
#include <vector>
using namespace std;

void triangle(int level = 4) {
    vector<string> rowOutputs{" /\\ ","/__\\"};
    vector<string> copy;
    string spaces=" ";
    for (int i = 0; i < level; i++){
        spaces += spaces;
        for (string trianglePart : rowOutputs){
            copy.push_back(spaces + trianglePart + spaces);
        }
        for (string trianglePart : rowOutputs){
            copy.push_back(trianglePart + trianglePart);
        }
        rowOutputs = copy;
        copy.clear();
    }
    for (string row : rowOutputs) {
        cout << row << endl;
    }
}

int main(int argc, char* argv[]) {
	int levels;
	istringstream iss;

	if (argc < 1 or argc > 2) {
		cerr << "Usage: " << argv[0] << " <positive integer>." << endl;
		return 1;
	}

    if(argc == 2) {
        iss.str(argv[1]);
        if(!(iss >> levels) or levels <=0) {
            cerr << "Error: Value argument must be an int." << endl;
            return 1;
        }
        iss.clear();
    } else {
        levels = 1;
    }

    triangle(levels);
	return 0;
}