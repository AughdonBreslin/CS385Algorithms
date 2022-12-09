/*******************************************************************************
 * Name    : sqrt.cpp
 * Author  : Aughdon Breslin
 * Version : 1.0
 * Date    : Sep 2, 2020
 * Description : Compute the square root approximation of a number.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <iomanip>
#include <limits>

using namespace std;

double sqrt(double num, double epsilon = .0000001) {
	double last_guess = num;
	double next_guess = 0;
	double temp = last_guess;
	if (num < 0) {
		return numeric_limits<double>::quiet_NaN();
	}
	if (num == 0 or num == 1) {
		return num;
	}
	while (abs(temp - next_guess) > epsilon) {
		temp = last_guess;
		next_guess = (last_guess + num/last_guess) / 2;
		last_guess = next_guess;
	}
	return next_guess;
}

int main(int argc, char* argv[]) {
	double num, epsilon;
	istringstream iss;

	if (argc < 2 or argc > 3) {
		cerr << "Usage: " << argv[0] << " <value> [epsilon]" << endl;
		return 1;
	}

	iss.str(argv[1]);
	if( !(iss >> num) ) {
		cerr << "Error: Value argument must be a double." << endl;
		return 1;
	}

	iss.clear();
	if (argc == 3) {
		iss.str(argv[2]);
		if( !(iss >> epsilon) or epsilon <= 0) {
			cerr << "Error: Epsilon argument must be a positive double." << endl;
			return 1;
		}
	}
	cout << fixed << setprecision(8) << sqrt(num,epsilon) << endl;
	return 0;
}

