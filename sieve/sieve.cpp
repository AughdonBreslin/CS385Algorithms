/*******************************************************************************
 * Name    : sieve.cpp
 * Author  : Aughdon Breslin
 * Date    : Sep 13, 2020
 * Description : Sieve of Eratosthenes
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <cmath>
#include <iomanip>
#include <sstream>

using namespace std;

class PrimesSieve {
public:
	PrimesSieve(int limit) : is_prime_{new bool[limit+1]}, limit_{limit} {
		//Just to shortcut for later, set 0 and 1 to not prime
		is_prime_[0] = false;
		is_prime_[1] = false;
		//and start the rest off as assuming its prime
		for(int i = 2; i <= limit; i++) {
			is_prime_[i] = true;
		}
		//Set up the array and metadata
		sieve();
		count_num_primes();
	}

	~PrimesSieve() {
		delete [] is_prime_;
	}

	inline int num_primes() const {
		return num_primes_;
	}

	void display_primes() {
		// TODO: write code to display the primes in the format specified in the
		// requirements document. CHECK
		const int max_prime_width = num_digits(max_prime_),
						primes_per_row = 80 / (max_prime_width + 1);
		int progress = 0;

		//Spits out the nums
		for(int i = 0; i <= limit_; i++) {
			if(is_prime_[i]){
				progress++;
				//If at the end of a line or at the end of the primes
				if(progress == primes_per_row or i == max_prime_){
					cout << setw(max_prime_width) << i;
				} else //if theres only one line
				if(primes_per_row > num_primes_) {
					cout << i << " ";
				} else {
					cout << setw(max_prime_width) << i << " ";
				}

			}
			//Reset the list
			if(progress == primes_per_row) {
				cout << endl;
				progress = 0;
			}
		}
	}

private:
	bool * const is_prime_;
	const int limit_;
	int num_primes_, max_prime_;

	int count_num_primes(){
		num_primes_ = 0;
		// TODO: write code to count the number of primes found
		for(int i = 0; i <= limit_; i++) {
			if(is_prime_[i]){
				num_primes_++;
				max_prime_ = i; //max prime is updated whenever a new prime is counted,
								//last prime = biggest
			}
		}
		return num_primes_;
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

	void sieve() {
		// TODO: write sieve algorithm
		for(int i = 2; i <= sqrt(limit_);i++) {
			if(is_prime_[i]) {
				for (int j = pow(i,2); j <= limit_; j+=i) {
					is_prime_[j] = false; //any multiples of the number are made composite
				}
			}
		}
	}
};

int main() {
	cout << "**************************** " <<  "Sieve of Eratosthenes" <<
			" ****************************" << endl;
	cout << "Search for primes up to: ";
	string limit_str;
	cin >> limit_str;
	int limit;

	// Use stringstream for conversion. Don't forget to #include <sstream>
	istringstream iss(limit_str);

	// Check for error.
	if ( !(iss >> limit) ) {
		cerr << "Error: Input is not an integer." << endl;
		return 1;
	}

	if (limit < 2) {
		cerr << "Error: Input must be an integer >= 2." << endl;
		return 1;
	}

	// TODO: write code that uses your class to produce the desired output.
	PrimesSieve bob = PrimesSieve(limit);
	cout << endl;
	cout << "Number of primes found: " << bob.num_primes() << endl;
	cout << "Primes up to " << limit << ":" << endl;
	bob.display_primes();
	cout << endl;
	return 0;
}


