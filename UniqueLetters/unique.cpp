/*******************************************************************************
 * Name    : unique.cpp
 * Author  : Aughdon Breslin
 * Version : 1.0
 * Date    : Sep 22, 2020
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <cctype>

using namespace std;

bool is_all_lowercase(const string &s) {
	// TODO: returns true if all characters in string are lowercase
	// letters in the English alphabet; false otherwise.
	int i = 0;
	while (s[i]) {
		if(!islower(s[i])){
			return false;
		}
		i++;
	}
	return true;
}
bool all_unique_letters(const string &s) {
	// TODO: returns true if all letters in string are unique, that is
	// no duplicates are found; false otherwise.
	// You may use only a single int for storage and work with bitwise
	// and bitshifting operators.
	// No credit will be given for other solutions.
	unsigned int vector = 0;
	unsigned int setter = 0;
	int i = 0;
	while (s[i]) {
		char letter = s[i];
		setter = 1 << (letter - 'a');
		if((vector & setter) != 0){
			cout << "Duplicate letters found." << endl;
			return false;
		}
		vector = vector | setter;
		i++;
	}
	cout << "All letters are unique." << endl;
	return true;
}
int main(int argc, char * const argv[]) {
	// TODO: reads and parses command line arguments.
	string bob;
	// Calls other functions to produce correct output.

	//Too few/many arguments
	if (argc != 2) {
		cerr << "Usage: ./unique <string>" << endl;
		return 1;
	}
	//bob = second argument (the string)
	bob = argv[1];

	//Contains uppercase/non- letter
	if(!is_all_lowercase(bob)) {
		cerr << "Error: String must contain only lowercase letters." << endl;
		return 1;
	}

	all_unique_letters(bob);
	return 0;
} //nice.


