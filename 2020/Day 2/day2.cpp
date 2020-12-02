using namespace std;

#include <iostream>
#include <vector>
#include <fstream>

// tobogganPass: Abstract data type that stores a password and
// North Pole's Toboggan corporate password policy
struct tobogganPass{
	char requiredLetter;
	int min;
	int max;
	string pass;
};

// Reads input file and return a vector of tobogganPass
vector<tobogganPass> readInput(string file){
	// Vector to store the result in
	vector<tobogganPass> passList;
	// Instantinate the input file object and open the file
	ifstream inFile;
	inFile.open(file);
	// Read line by line into an int and then push back into the passList
	string line;
	while (getline(inFile, line)){
		// New tobogganPass object
		tobogganPass currentPass;
		// Start at the beginning of the line
		int index = 0;
		// String to hold the current value
	    string currVal = "";
		// Add numbers to the current Value until we hit a -
		while (line[index] != '-'){
			currVal += line[index];
			index++;
		}
		// Store the completed minimum value (convert to int first)
		currentPass.min = stoi(currVal);
		
		// Jump over the '-'
		index++;
		// String to hold the current value
	    currVal = "";
		// Add numbers to the current Value until we hit a space
		while (line[index] != ' '){
			currVal += line[index];
			index++;
		}
		// Store the completed maximum value (convert to int first)
		currentPass.max = stoi(currVal);

		// Jump over the space
		index++;
		// Store the requiredLetter
		currentPass.requiredLetter = line[index];

		// Jump over the letter, -, and space
		index += 3;
		// store the pass as a substring from the index to the end
		currentPass.pass = line.substr(index);
		// Jump over the space
		index++;
		// finally push the built object to the vector
		passList.push_back(currentPass);
	}
	// Close the file
	inFile.close();
	// Return the passList
	return passList;
}

// Checks passwords according to Official Toboggan standards
int checkPasswords(vector<tobogganPass> passList){
	// Track the number of good passwords
	int goodPasswords = 0;
	
	// Loop through every password
	for (int i = 0; i < passList.size(); i++){
		// Track the number of times the specified character appears
		int charCount = 0;
		for (int j = 0; j < passList[i].pass.size(); j++){
			if (passList[i].pass[j] == passList[i].requiredLetter)
				charCount++;
		}
		// Check if the password meets the requirments and if so increment the goodPasswords count
		if (charCount >= passList[i].min && charCount <= passList[i].max)
			goodPasswords++;
	}

	// Return the number of good passwords
	return goodPasswords;
}

// Checks passwords according to revised Official Toboggan standards
int checkPasswordsFixed(vector<tobogganPass> passList){
	// Track the number of good passwords
	int goodPasswords = 0;
	// Loop through every password
	for (int i = 0; i < passList.size(); i++){
		// Store the requiredChar and index positions
		char requiredChar = passList[i].requiredLetter;
		int firstPos = passList[i].min-1;
		int secondPos = passList[i].max-1;
		
		// Increment goodPasswords if the character matches for only one of the positions
		if (passList[i].pass[firstPos] == requiredChar && passList[i].pass[secondPos] != requiredChar)
			goodPasswords++;
		if (passList[i].pass[firstPos] != requiredChar && passList[i].pass[secondPos] == requiredChar)
			goodPasswords++;
	}

	// Return the number of good passwords
	return goodPasswords;
}

int main(){
	// Read the input into a vector of ints
	vector<tobogganPass> passList = readInput("input2.txt");

	// Output the result
	cout << "Part 1: " << checkPasswords(passList) << endl;
	cout << "Part 2: " << checkPasswordsFixed(passList) << endl;

	return 0;
}
