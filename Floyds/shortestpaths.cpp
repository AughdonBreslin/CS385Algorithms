/*******************************************************************************
 * Name    : shortestpaths.cpp
 * Author  : Aughdon Breslin
 * Version : 1.0
 * Date    : Nov 30, 2020
 * Description : For all vertices, find the shortest paths to other vertices.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <queue>

using namespace std;

int num_vertices = 0;
//2^63-1, the largest possible long
long INF = 9223372036854775807;

void floyd(long** matrix, long** inter){
	for(int k = 0; k < num_vertices; k++){
		for(int i = 0; i < num_vertices; i++){
			for(int j = 0; j < num_vertices; j++){
				// No overflow and connected path is shorter than direct
				if(matrix[i][k]+matrix[k][j] > 0 &&
						matrix[i][k] + matrix[k][j] < matrix[i][j]){
					matrix[i][j] = matrix[i][k] + matrix[k][j];
					inter[i][j] = k;
				}
			}
		}
	}
}

/**
 * Displays the matrix on the screen formatted as a table.
 */
void display_table(long** const matrix, const string &label,
		const bool use_letters = false) {
	cout << label << endl;
	long max_val = 0;
	for (int i = 0; i < num_vertices; i++) {
		for (int j = 0; j < num_vertices; j++) {
			long cell = matrix[i][j];
			if (cell < INF && cell > max_val) {
				max_val = matrix[i][j];
			}
		}
	}
	int max_cell_width = use_letters ? to_string(max_val).length() :
			to_string(max(static_cast<long>(num_vertices), max_val)).length();
	cout << ' ';
	for (int j = 0; j < num_vertices; j++) {
		cout << setw(max_cell_width + 1) << static_cast<char>(j + 'A');
	}
	cout << endl;
	for (int i = 0; i < num_vertices; i++) {
		cout << static_cast<char>(i + 'A');
		for (int j = 0; j < num_vertices; j++) {
			cout << " " << setw(max_cell_width);
			if (matrix[i][j] == INF) {
				cout << "-";
			} else if (use_letters) {
				cout << static_cast<char>(matrix[i][j] + 'A');
			} else {
				cout << matrix[i][j];
			}
		}
		cout << endl;
	}
	cout << endl;
}

void pathfind(int from, int to, queue<char>* path, long** inter){
	// gets everything except very start and end
	if(inter[from][to] != INF){
		pathfind(from, inter[from][to], path, inter);
		path->push(char(inter[from][to]+65));
		pathfind(inter[from][to], to, path, inter);
	}
}

void display_paths(long** matrix, long** inter){
	queue<char> path;
	for(int i = 0; i < num_vertices; i++){
		for(int j = 0; j < num_vertices; j++){

			// if theres no path
			if(matrix[i][j] == INF){
				cout << char(i+65) << " -> " << char(j+65)
					<< ", distance: infinity, path: none"
					<< endl;
			} else {
				// add the beginning
				path.push(char(i+65));
				// add the middle
				pathfind(i,j,&path,inter);
				// add the end (if its not the beginning)
				if(i != j){
					path.push(char(j+65));
				}

				// turn it into a string
				string list = "";
				while(!path.empty()){
					list += path.front();
					path.pop();
					// if last one, dont add arrow
					if(!path.empty()){
						list.append(" -> ");
					}
				}

				// write A -> B, distance: 1, path: A -> B
				cout << char(i+65) << " -> " << char(j+65)
					<< ", distance: " << matrix[i][j]
					<< ", path: " << list << endl;
			}
		}
	}
}

int main(int argc, const char *argv[]) {
	long** dist_matrix;
	long** path_lengths;
	long** inter_vertices;

	// Make sure the right number of command line arguments exist.
	if (argc != 2) {
		cerr << "Usage: " << argv[0] << " <filename>" << endl;
		return 1;
	}

	// Create an ifstream object.
	ifstream input_file(argv[1]);

	// If it does not exist, print an error message.
	if (!input_file) {
		cerr << "Error: Cannot open file '" << argv[1] << "'." << endl;
		return 1;
	}

	// Add read errors to the list of exceptions the ifstream will handle.
	input_file.exceptions(ifstream::badbit);
	string line;

	try {
		unsigned int line_number = 1;

		// First line of file
		getline(input_file,line);
		stringstream ss(line);
		ss >> num_vertices;

		// Invalid number of vertices
		if(num_vertices < 1 || num_vertices > 26){
			cerr << "Error: Invalid number of vertices '" << line << "' on line 1.";
			return 1;
		}

		// Initialize distance matrix
		dist_matrix = new long*[num_vertices];
		for(int i = 0; i < num_vertices; i++){
			dist_matrix[i] = new long[num_vertices];
			for(int j = 0; j < num_vertices; j++){
				if(i == j){
					dist_matrix[i][j] = 0;
				} else {
					dist_matrix[i][j] = INF;
				}
			}
		}
		++line_number;

		// Use getline to read in a line.
		// See http://www.cplusplus.com/reference/string/string/getline/
		while (getline(input_file, line)) {

			stringstream tt(line);
			string letter1, letter2;
			long num;

			// Invalid edge data
			if(line.length() < 5){
				cerr << "Error: Invalid edge data '" << line <<
						"' on line " << line_number << "." << endl;
				return 1;
			}

			// Error: Starting vertex 'X' on line 2 is not among valid values A-C.
			if(!(tt >> letter1) || letter1.length() != 1
					|| (letter1[0] < 65 || letter1[0] > 64+num_vertices)){
				cerr << "Error: Starting vertex '" << letter1 <<
						"' on line " << line_number <<
						" is not among valid values A-" << char(64+num_vertices) << "." << endl;
				return 1;
			}

			// Error: Ending vertex '.' on line 3 is not among valid values A-F.
			if(!(tt >> letter2) || letter2.length() != 1
					|| (letter2[0] < 65 || letter2[0] > 64+num_vertices)){
				cerr << "Error: Ending vertex '" << letter2 <<
						"' on line " << line_number <<
						" is not among valid values A-" << char(64+num_vertices) << "." << endl;
				return 1;
			}

			// Error: Invalid edge weight '-7' on line 4.
			stringstream::pos_type pos = tt.tellg();
			if(!(tt >> num)){
				string bad = tt.str().substr(4);
				cerr << "Error: Invalid edge weight '" << bad <<
						"' on line " << line_number << "." << endl;
				return 1;
			} else
				if(num < 1){
					cerr << "Error: Invalid edge weight '" << num <<
							"' on line " << line_number << "." << endl;
					return 1;
				}
			//cout << line_number << ":\t" << line << endl;
			// fill in the distance matrix w valid data
			dist_matrix[int(letter1[0]-65)][int(letter2[0]-65)] = num;
			++line_number;
		}

		// Initialize path lengths
		path_lengths = new long*[num_vertices];
		for(int i = 0; i < num_vertices; i++){
			path_lengths[i] = new long[num_vertices];
			for(int j = 0; j < num_vertices; j++){
				path_lengths[i][j] = dist_matrix[i][j];
			}
		}

		// Initialize intermediate vertices
		inter_vertices = new long*[num_vertices];
		for(int i = 0; i < num_vertices; i++){
			inter_vertices[i] = new long[num_vertices];
			for(int j = 0; j < num_vertices; j++){
				inter_vertices[i][j] = INF;
			}
		}

		// Don't forget to close the file.
		input_file.close();
	} catch (const ifstream::failure &f) {
		cerr << "Error: An I/O error occurred reading '" << argv[1] << "'.";
		return 1;
	}

	// Done w errors, now we gotta do the thing
	floyd(path_lengths,inter_vertices);

	// display results
	display_table(dist_matrix, "Distance matrix:", false);
	display_table(path_lengths, "Path lengths:", false);
	display_table(inter_vertices, "Intermediate vertices:", true);

	display_paths(path_lengths, inter_vertices);

	// delete dist_matrix, path lengths, inter vertices
	for(int i = 0; i < num_vertices; i++){
		delete[] dist_matrix[i];
		delete[] path_lengths[i];
		delete[] inter_vertices[i];
	}
	delete[] dist_matrix;
	delete[] path_lengths;
	delete[] inter_vertices;

	// Bingo, bango, bongo.
	return 0;
}
