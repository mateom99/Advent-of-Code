using namespace std;

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

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

// Given a "binary space partitioning" boarding pass format, return its boarding pass ID
int getBoardingPassID(string pass){
	// Row values
	int rowHigh = 127;
	int rowLow = 0;
	int row;

	// Use the first 6 to chars to eliminate eliminate rows
	for (int i = 0; i < 6; i++){
		// Keep the upper half
		if (pass[i] == 'F')
			rowHigh = (rowHigh+rowLow)/2;
		// Keep the lower half
		if (pass[i] == 'B'){
			rowLow = (rowHigh+rowLow)/2 + 1;
		}
	}
	// Finally, keep either the high or low row based on the 7th character
	if (pass[6] == 'F')
		row = rowLow;
	if (pass[6] == 'B')
		row = rowHigh;

	// Row values
	int colHigh = 7;
	int colLow = 0;
	int col;

	for (int i = 7; i < 9; i++){
		// Keep the upper half
		if (pass[i] == 'L')
			colHigh = (colHigh+colLow)/2;
		// Keep the lower half
		if (pass[i] == 'R')
			colLow = (colHigh+colLow)/2 + 1;
	}
	// Finally, keep either the high or low col based on the last character
	if (pass[9] == 'L')
		col = colLow;
	if (pass[9] == 'R')
		col = colHigh;

	// Return the boarding pass ID
	return row*8 + col;
}

/* Fast trick to getting the boarding pass ID
 * Convert each character to binary (B/R = 1, F/L = 0)
 * Then simply convert the binary to decimal */
int quickBoardingPassID(string pass){
	// For every character convert to 1 or 0
	for (int i = 0; i < 10 ; i++)
		if (pass[i] == 'B' || pass[i] == 'R')
			pass[i] = '1';
		else 
			pass[i] = '0';
	
	// Convert the binary string to decimal and return
	return stoi(pass, 0, 2);
}

// Checks all boarding passes and returns the one with the largest ID
int maxBoardingPassID(vector<string> boardingPasses){
	// Variable to hold the max
	int max = 0;
	// Loop through every boarding pass
	for (int i = 0; i < boardingPasses.size(); i++){
		// Get the current passes ID and check if it is the new max
		int id = quickBoardingPassID(boardingPasses[i]);
		if (id>max)
			max = id;
	}
	// Return the max
	return max;
}

// Uses process of elimination to find your boarding pass ID
int findMyBoardingPass(vector<string> boardingPasses){
	// Vector to store all the boarding pass IDs
	vector<int> passIDs;
	// Get the boarding pass ID from each pass and store it into the passIds vector
	for (int i = 0; i < boardingPasses.size(); i++)
		passIDs.push_back(getBoardingPassID(boardingPasses[i]));
	
	// Sort the boarding pass IDs
	sort(passIDs.begin(), passIDs.end());

	// Loop through every boarding pass ID and check check which one is missing - That's our seat
	for(int i = 1; i < passIDs.size(); i++)
		if (passIDs[i-1]+1 != (passIDs[i]))
			return passIDs[i]-1;

	// Return -1 if we didn't find one (error!)
	return -1;
}

int main(){
	// Read the input into a vector of ints
	vector<string> boardingPasses = readInput("input5.txt");

	// Output the result
	cout << "Part 1: " << maxBoardingPassID(boardingPasses) << endl;
	cout << "Part 2: " << findMyBoardingPass(boardingPasses) << endl;
	return 0;
}
