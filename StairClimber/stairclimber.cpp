/*******************************************************************************
 * Name    : stairclimber.cpp
 * Author  : Aughdon Breslin
 * Version : 1.0
 * Date    : Sep 29, 2020
 * Description : Lists the number of ways to climb n stairs.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

int num = 0;

vector<vector<int>> get_ways(int num_stairs) {
	// TODO: Return a vector of vectors of ints representing
	// the different combinations of ways to climb num_stairs
	// stairs, moving up either 1, 2, or 3 stairs at a time.

	vector<vector<int>> ways{};

	//if there are no stairs to climb, there are no ways to climb the stairs
	if(num_stairs <= 0){
		return  {{}};
	}
	//taking 1 step, 2 steps, and 3 steps at a time
	for(int i = 1; i < 4; i++) {
		//making sure we dont overstep (ha, get it) the number of stairs
		if (num_stairs >= i) {
			//get the paths for i less stairs
			vector<vector<int>> result = get_ways(num_stairs-i);
			//tack on the paths for the lesser stairs onto the paths for more stairs
			for (size_t j = 0; j < result.size(); j++) {
				result[j].insert(result[j].begin(), i);
			}
			// add result vector to end of ways vector
			ways.insert(ways.end(),result.begin(),result.end());
		}
	}
	return ways;
}
int num_digits(int num) {
	// TODO: write code to determine how many digits are in an integer
	// Hint: No strings are needed. Keep dividing by 10.
	int digs = 1;
	while(num>9){
		num /=10;
		digs++; //don't need the digits, just the number of them
	}
	return digs;
}
void display_ways(const vector<vector<int>> &ways) {
	// TODO: Display the ways to climb stairs by iterating over
	// the vector of vectors and printing each combination.

	//Cover grammar
	if(ways.size() == 1){
		cout << "1 way to climb 1 stair." << endl;

	} else {
		cout << ways.size() << " ways to climb " << num << " stairs." << endl;
	}

	//Output list
	for(size_t i = 0; i < ways.size(); i++) {
		cout << setw(num_digits(ways.size())) << i+1 << ". ["; // 1.[
		for(size_t j = 0; j < ways[i].size()-1; j++) {
			cout << ways[i][j] << ", "; // 1, 1, 1, 2, 2,
		}
		cout << ways[i][ways[i].size()-1] << "]" << endl; 	// 3]
	}

}

int main(int argc, char * const argv[]) {

	istringstream iss;

	//Too few/many arguments
	if (argc != 2) {
		cerr << "Usage: ./stairclimber <number of stairs>" << endl;
		return 1;
	}


	//Invalid input
	iss.str(argv[1]);
	if( !(iss >> num) || num <= 0) {
		cerr << "Error: Number of stairs must be a positive integer." << endl;
		return 1;
	}

	//get the ways and show them
	display_ways(get_ways(num));
	return 0;
}
