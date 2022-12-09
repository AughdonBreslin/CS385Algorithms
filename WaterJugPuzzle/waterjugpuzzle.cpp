/*******************************************************************************
 * Name    : waterjugpuzzle.cpp
 * Author  : Aughdon Breslin
 * Version : 1.0
 * Date    : Oct 10, 2020
 * Description : Solves the water jug puzzle for any 3 jugs
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <queue>

using namespace std;


// Struct to represent state of water in the jugs.
struct State {
	int a, b, c;
	string directions;
	State *parent;

	State(int _a, int _b, int _c, string _directions) :
		a{_a}, b{_b}, c{_c}, directions{_directions}, parent{nullptr} { }

		// String representation of state in tuple form.
		string to_string() {
			ostringstream oss;
			oss << "(" << a << ", " << b << ", " << c << ")";
			return oss.str();
		}
};

//three global variables, but its okay cuz they're my backbone
int jugs[6];
State* victor = nullptr;
queue<State*> garbageCollection; //ill build my own damn garbage collector

void bfs(State* front, State*** board, State* goal) {
	queue<State*> order;
	order.push(front);

	/*******************************************
	 * ******* Memorial for my boy bob ******* *
	 * *** stolen by valgrind too young :( *** *
	 *******************************************/

	while(!order.empty()){
		//Pour from C to A
		//If C is not empty and A is not at full capacity
		if(order.front()->c != 0 && order.front()->a != jugs[0]){

			//the min between emptying C and filling up A
			int diff = min(order.front()->c,jugs[0] - order.front()->a);

			//make the directions string properly
			string cumul;
			if(diff == 1){
				cumul = "Pour 1 gallon from C to A. ";
			} else {
				stringstream ss;
				ss << diff;
				string num = ss.str();
				cumul = "Pour " + num + " gallons from C to A. ";
				ss.clear();
			}
			//if [a][b] points to null, we know its not a dupl
			if(board[order.front()->a+diff][order.front()->b] == nullptr) {
				//make our baby
				State* creation = new State(order.front()->a+diff,order.front()->b,order.front()->c-diff, cumul);

				//throw him in the dumpster
				garbageCollection.push(creation);

				//but track down that negligent parent
				creation->parent = order.front();

				//point [a][b] to its parent
				board[order.front()->a+diff][order.front()->b] = creation->parent;

				//push that state into the queue
				order.push(creation);

				//if we've reached the end goal
				if(creation->a == goal->a && creation->b == goal->b && creation->c == goal->c){
					victor = creation;
					return; //Mission Accomplished
				}
			}


		}

		//Pour from B to A
		//same exact module as Pour from C to A, refer to there for general comments
		if(order.front()->b != 0 && order.front()->a != jugs[0]){
			int diff = min(order.front()->b,jugs[0] - order.front()->a);

			string cumul;
			if(diff == 1){
				cumul = "Pour 1 gallon from B to A. ";
			} else {
				stringstream ss;
				ss << diff;
				string num = ss.str();
				cumul = "Pour " + num + " gallons from B to A. ";
				ss.clear();
			}

			if(board[order.front()->a+diff][order.front()->b-diff] == nullptr) {
				State* creation = new State(order.front()->a+diff,order.front()->b-diff,order.front()->c, cumul);
				garbageCollection.push(creation);
				creation->parent = order.front();
				board[order.front()->a+diff][order.front()->b-diff] = creation->parent;
				order.push(creation);

				if(creation->a == goal->b && creation->b == goal->c && creation->c == goal->c){
					victor = creation;
					return;
				}
			}


		}

		//Pour from C to B
		if(order.front()->c != 0 && order.front()->b != jugs[1]){
			int diff = min(order.front()->c,jugs[1] - order.front()->b);

			string cumul;
			if(diff == 1){
				cumul = "Pour 1 gallon from C to B. ";
			} else {
				stringstream ss;
				ss << diff;
				string num = ss.str();
				cumul = "Pour " + num + " gallons from C to B. ";
				ss.clear();
			}

			if(board[order.front()->a][order.front()->b+diff] == nullptr) {
				State* creation = new State(order.front()->a,order.front()->b+diff,order.front()->c-diff, cumul);
				garbageCollection.push(creation);
				creation->parent = order.front();
				board[order.front()->a][order.front()->b+diff] = creation->parent;
				order.push(creation);

				//if we've reached the end goal
				if(creation->a == goal->a && creation->b == goal->b && creation->c == goal->c){
					victor = creation;
					return;
				}
			}


		}

		//Pour from A to B
		if(order.front()->a != 0 && order.front()->b != jugs[1]){
			int diff = min(order.front()->a,jugs[1] - order.front()->b);

			string cumul;
			if(diff == 1){
				cumul = "Pour 1 gallon from A to B. ";
			} else {
				stringstream ss;
				ss << diff;
				string num = ss.str();
				cumul = "Pour " + num + " gallons from A to B. ";
				ss.clear();
			}

			if(board[order.front()->a-diff][order.front()->b+diff] == nullptr) {
				State* creation = new State(order.front()->a-diff,order.front()->b+diff,order.front()->c, cumul);
				garbageCollection.push(creation);
				creation->parent = order.front();
				board[order.front()->a-diff][order.front()->b+diff] = creation->parent;
				order.push(creation);

				//if we've reached the end goal
				if(creation->a == goal->a && creation->b == goal->b && creation->c == goal->c){
					victor = creation;
					return;
				}
			}
		}

		//Pour from B to C
		if(order.front()->b != 0 && order.front()->c != jugs[2]){
			int diff = min(order.front()->b,jugs[2] - order.front()->c);

			string cumul;
			if(diff == 1){
				cumul = "Pour 1 gallon from B to C. ";
			} else {
				stringstream ss;
				ss << diff;
				string num = ss.str();
				cumul = "Pour " + num + " gallons from B to C. ";
				ss.clear();
			}

			if(board[order.front()->a][order.front()->b-diff] == nullptr) {
				State* creation = new State(order.front()->a,order.front()->b-diff,order.front()->c+diff, cumul);
				garbageCollection.push(creation);
				creation->parent = order.front();
				board[order.front()->a][order.front()->b-diff] = creation->parent;
				order.push(creation);

				//if we've reached the end goal
				if(creation->a == goal->a && creation->b == goal->b && creation->c == goal->c){
					victor = creation;
					return;
				}
			}
		}

		//Pour from A to C
		if(order.front()->a != 0 && order.front()->c != jugs[2]){
			int diff = min(order.front()->a,jugs[2] - order.front()->c);

			string cumul;
			if(diff == 1){
				cumul = "Pour 1 gallon from A to C. ";
			} else {
				stringstream ss;
				ss << diff;
				string num = ss.str();
				cumul = "Pour " + num + " gallons from A to C. ";
				ss.clear();
			}

			if(board[order.front()->a-diff][order.front()->b] == nullptr) {
				State* creation = new State(order.front()->a-diff,order.front()->b,order.front()->c+diff, cumul);
				garbageCollection.push(creation);
				creation->parent = order.front();
				board[order.front()->a-diff][order.front()->b] = creation->parent;
				order.push(creation);

				//if we've reached the end goal
				if(creation->a == goal->a && creation->b == goal->b && creation->c == goal->c){
					victor = creation;
					return;
				}
			}
		}
		//We've added all that we can to the queue, now we move to the next State in the queue
		order.pop();
	}
}

//Reverse the output of victory road
void reverse(State* cur){
	if(cur != nullptr && cur->directions != ""){
		reverse(cur->parent);
		cout << cur->directions << cur->to_string() << endl;
	}
}

//Display victory road
void displayResult(State* initial, State* goal) {
	//or lack thereof
	if (victor == nullptr) {
		cout << "No solution." << endl;
	} else {
		//There's our victory road
		cout << "Initial state. " << initial ->to_string() << endl;
		State* current = victor;
		reverse(current);
	}
}

int main(int argc, char * const argv[]) {
	istringstream iss;

	//Too few/many arguments
	if (argc != 7) {
		cerr << "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
		delete victor;
		return 1;
	}

	//Invalid jug capacity inputs
	for(int i = 1; i < 4; ++i){
		iss.str(argv[i]);
		if( !(iss >> jugs[i-1]) || jugs[i-1] <= 0) {
			//ASCII FTW
			cerr << "Error: Invalid capacity '" << argv[i] << "' for jug "<< char(i-1 +65) << "." << endl;
			delete victor;
			return 1;
		}
		iss.clear();
	}

	//Invalid jug goal inputs
	for(int i = 4; i < 7; ++i) {
		iss.str(argv[i]);
		if( !(iss >> jugs[i-1]) || jugs[i-1] < 0) {
			//ASCII FTW
			cerr << "Error: Invalid goal '" << argv[i] << "' for jug " << char(i-4 +65) << "." << endl;
			delete victor;
			return 1;
		}
		iss.clear();
	}

	//Bad goal logic
	for(int i = 3; i < 6; ++i) {
		if(jugs[i] > jugs[i-3]){
			cerr << "Error: Goal cannot exceed capacity of jug " << char(i-3 +65) << "." << endl;
			delete victor;
			return 1;
		}
	}

	//Capacity of C must equal sum of goals
	if(jugs[2] != jugs[3] + jugs[4] + jugs[5]) {
		cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C." << endl;
		delete victor;
		return 1;
	}

	//Initialize start and end
	State* initState = new State(0,0,jugs[2],"");
	garbageCollection.push(initState);
	State* goalState = new State(jugs[3],jugs[4],jugs[5],"");
	garbageCollection.push(goalState);

	//and the bane of my existence too
	State*** memory = new State**[jugs[0]+1];
	for(int i = 0; i < jugs[0]+1; i++){ //why must i loop to make 2D array?
		memory[i] = new State*[jugs[1]+1];
		for(int j = 0; j < jugs[1]+1; j++){
			memory[i][j] = nullptr;
		}
	}

	//if init is the goal
	if(initState->a == goalState->a && initState->b == goalState->b && initState->c == goalState->c){
		victor = initState; //done lul
	} else { //do work
		bfs(initState, memory, goalState);
	}

	//Flex that victory, or flex that loss idk
	displayResult(initState, goalState);

	//Garbage man comes to clean up shop
	while(!garbageCollection.empty()){
		if(garbageCollection.front()!=nullptr){
			delete garbageCollection.front();
		}
		garbageCollection.pop();
	}

	//and to tear down the bane of my existence. my hero <3
	for (int i = 0;i < jugs[0]+1; i++){
		delete[] memory[i];
	}
	delete[] memory;

	//Ghost: Mission Accomplished.
	return 0;
	//this shit doo doo
}
