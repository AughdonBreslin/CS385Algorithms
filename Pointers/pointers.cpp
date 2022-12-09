/*******************************************************************************
 * Name    : pointers.cpp
 * Author  : Aughdon Breslin
 * Version : 1.0
 * Date    : Sep 4, 2020
 * Description : Intro to pointers
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>

using namespace std;

void display_array(int array[], const int length) {
	cout << "[";
	if (length >= 1) {
		cout << array[0];
	}
	for (int i = 1; i< length; ++i) {
		cout << ", " << array[i];
	}
	cout << "]" << endl;
}

void display_array_ptr(int array[], const int length) {
	cout << "[";
	if (length >= 1) {
		cout << *array;
	}
	for (int *ptr = array + 1, *end = array + length; ptr < end; ++ptr) {
		cout << ", " << *ptr;
	}
	cout << "]" << endl;

}

void pass_by_value(int x) {
	cout << "pass by value" << endl;
	x = 10;
}

void pass_by_pointer(int *x) { //pointer points to address
	cout << "pass by pointer" << endl;
	*x = 10; // this * says the value at this address now = 10
}

void pass_by_reference(int &x) { //gets address from value of 5
	cout << "pass by reference" << endl;
	x = 10; //sets value at that address to 10
}

int main() {
	int x = 5;
//	int *z =&x;
	int y = 6;
	cout << "Initial values:" << endl;
	cout << x << " " << y << endl;

//	//z is pointing to x's address, if you change the value of z, it changes x
//	cout << x << " " << *z << endl;
//
//	//7 6 7
//	cout << x << " " << y << " " << *z << endl;
//
//	z = &y;
//	// 7 6 6
//	cout << x << " " << y << " " << *z << endl;
//
//	// first addresses
//	cout << &x << " " << &y << " " << z << endl;
//
//	z--;
//	cout << &x << " " << &y << " " << z << endl;
//
//
//	z++;
//	//z++;
//	cout << *z << endl;
//	//z+= 30000;
//	//cout << *z << endl;
//	//*z = 700;
//
//	int *values = new int[y];
//	for (int i = 0; i < y; i++) {
//		*(values + i) = i;
//	}
//	display_array(values, y);
//	display_array_ptr(values, y);
//	delete [] values;

	x = 5;
	y = 6;
	pass_by_value(x); //pass...(5)
	cout << x << " " << y << endl;

	x = 5;
	y = 6;
	pass_by_pointer(&x); //pass...(address of x)
	cout << x << " " << y << endl;

	x = 5;
	y = 6;
	pass_by_reference(x); //pass...(5)
	cout << x << " " << y << endl;
	return 0;
}

