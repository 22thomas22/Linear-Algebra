#include <iostream>
#include <iomanip>
#include <random>
#include <chrono>
#include <string>
#include <sstream>
using namespace std;

void showMatrixEqn(const vector<vector<int>>& data, int x, int y) {
	//show the matrix in normal form
	for (int i = 0; i < data.size(); i++) {
		for (int j = 0; j < data[i].size(); j++) {
			cout << setw(4) << data[j][i];
		}
		cout << endl;
	}
	//show the matrix as a system of equations
	char options[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g' };
	for (int i = 0; i < data.size(); i++) {
		int j, size = data[i].size() - 1;
		for (j = 0; j < size; j++) {
			cout << setw(4) << data[i][j] << options[j];
			if (j < size - 1) {
				cout << setw(4) << " + ";
			}
		}
		cout << " = " << data[i][j];
		cout << endl;
	}
}

bool isInt(const std::string& s, int& value) {
	try {
		size_t idx;
		value = std::stoi(s, &idx);

		// Ensure the whole string was consumed
		return idx == s.size();
	}
	catch (...) {
		return false;
	}
}
bool isInt(const std::string& s) {
	int value;
	try {
		size_t idx;
		value = std::stoi(s, &idx);

		// Ensure the whole string was consumed
		return idx == s.size();
	}
	catch (...) {
		return false;
	}
}
bool toInt(const std::string& s) {
	return stoi(s);
}

int main() {
	random_device rd;
	mt19937 gen(rd());

	uniform_int_distribution<int> dist(1, 20);

	int vars, eqns; // x and y
	cout << "variables: ";
	cin >> vars; cout << endl; vars++; // add in for the right side of = sign
	eqns = vars - 1; // height spacing up/down, each one is an equation

	vector<vector<int>> data(eqns, vector<int>(vars));
	// fill the array
	for (int i = 0; i < eqns; i++) {
		for (int j = 0; j < vars; j++) {
			data[i][j] = dist(gen);
		}
	}

	showMatrixEqn(data, eqns, vars);

	

	
	/**
	* add 1 3: add row 1 to row 3 (row1→row1 + row3)
	* sub 2 4: subtract row 2 from row 4 (row2→row2 + row4)
	* mult div similar logic
	* swap 2 3: switch rows 2 and 3 to take each others places
	*  --- 
	* 1 mult 4: take row 1 and multiply by 4 (row1→row1 * 4)
	* 2 div 4: take row 2 and divide by 4 (row2→row2 / 4)
	*  ---
	* Taken from textbook
	* 
    *	(Replacement) Replace one row by the sum of itself and a multiple of another row.
	*	(Interchange) Interchange two rows.
	*	(Scaling) Multiply all entries in a row by a nonzero constant.
	* **/
	string input;
	bool end = false;
	int count = 0;
	string commands[10];
	int firstRow;

	while (!end) {
		cout << "enter command: ";
		getline(cin, input);
		istringstream stream(input);
		while (stream >> commands[count++]) {}
		if (isInt(commands[0], firstRow)) {
			bool isMult;
			// we are multiplying/dividing a matrix
			if (commands[1] == "div") {
				if (!isInt(commands[1])) { cout << "bad command"; continue; }
				isMult = false;
			}
			else if (commands[1] == "mult") {
				if (!isInt(commands[1])) { cout << "bad command"; continue; }
				isMult = true;
			}
			else { cout << "bad something"; continue; }
			int value;
			if (isInt(commands[2], value)) { cout << "bad number"; continue; }
			
			float valueF = isMult ? (float)value : 1.0 / (float)value;

			for (int i = 0; i < vars; i++) {
				data[firstRow][vars] = (int)( (float)data[firstRow][vars] * valueF );
			}
			
		} else {
			// we are doing something between matricies, or swapping matricies
			if (commands[0] == "swap") {
				int first, second;
				if (!isInt(commands[1], first) || !isInt(commands[2], second)) {
					cout << "bad row numbers for swap\n";
					continue;
				}
				swap(data[first], data[second]);
			}
		}
	}
}