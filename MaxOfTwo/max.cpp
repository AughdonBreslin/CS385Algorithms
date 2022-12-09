/*
 * max.cpp
 *
 *  Created on: Sep 2, 2020
 *      Author: user
 */

#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;
/**
 * Returns the max of two integers
 */
int max(int m, int n) {
	//Is m >n? Yes? m. No? n.
	return m > n ? m : n;
}



int main(int argc, char *argv[]) {
	int m, n;
	istringstream iss;

	//Checks
	if (argc != 3) {
		cerr << "Usage: " << argv[0] << " <integer m> <integer n>" << endl;
		return 1;
	}

	iss.str(argv[1]);
	if( !(iss >> m) ) {
		cerr << "Error: The first argument is not a valid integer." << endl;
		return 1;
	}
	iss.clear();
	
	iss.str(argv[2]);
	if( !(iss >> n) ) {
		cerr << "Error: The second argument is not a valid integer." << endl;
		return 1;
	}
	//Outputs the higher number
	cout << "max(" << m << ", " << n << ") = " << max(m, n) << endl;

	double d = 22.0/7;
	cout << fixed << setprecision(5) << d << endl;

	return 0;

}



