using namespace std;

#include <iostream>
#include <vector>
#include <fstream>

// Reads input file and return a vector<string> from the input
vector<string> readInput(string file){
	// Vector to store the result in
	vector<string> result;
	// Instantinate the input file object and open the file
	ifstream inFile;
	inFile.open(file);
	// Read line by line into a string and then push back into the result vector
	string line;
	while (inFile >> line){
		result.push_back(line);
	}
	// Close the file
	inFile.close();
	// Return the result vector
	return result;
}

// Returns how many trees we will encoutner with a specific slop
int calcTreeEncounters(vector<string> map, int right, int down){
	// Track the encounters in current coordinate
	int encounters = 0;
	int y = 0;
	int x = 0;
	// Loop until we hit the bottom
	while (y < map.size()){
		// Increment encounters if we are at a tree (#)
		if (map[y][x] == '#')
			encounters++;
		// Go down by the specified value
		y += down;
		// Go right by the specified value
		x += right;
		// Since the map repeats, if we hit the rightmost point, wrap around
		// by subtracting the size from or x coordinate
		if (x >= map[y].size()){
			x-=map[y].size();
		}
	}
	// Return the total number of encounters
	return encounters;
}

// Checks a variety of slopes and returns the total tree encounters of each multipled together
long checkSlopes(vector<string> map){
	// Track the result (start at 1 since we multiply)
	long result = 1;
	// Check all the slopes and multiply each by the total
	result *= calcTreeEncounters(map, 1, 1);
	result *= calcTreeEncounters(map, 3, 1);
	result *= calcTreeEncounters(map, 5, 1);
	result *= calcTreeEncounters(map, 7, 1);
	result *= calcTreeEncounters(map, 1, 2);
	// Return the result
	return result;
}

int main(){
	// Read the input into a vector of strings
	vector<string> map = readInput("input3.txt");
	// Output the result
	cout << "Part 1: " << calcTreeEncounters(map, 3, 1) << endl;
	cout << "Part 2: " << checkSlopes(map) << endl;

	return 0;
}
