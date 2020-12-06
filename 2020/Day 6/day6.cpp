using namespace std;

#include <iostream>
#include <vector>
#include <fstream>

// Class that stores info on a particular groups answers to the Customs Declaration Form
class groupAnswers{
	// Store total unique questions answered as a group
	int totalAnswers;
	// Store the group size
	int groupSize;
	// Hashset that stores number of answers to a given question
	vector<int> hashSet;

	public:
	// Constructor that initializes the public variables
	groupAnswers(){
		hashSet.resize(26);
		totalAnswers = 0;
		groupSize = 0;
	}

	// Inserts a char into the hashset and increments count if it wasn't done before
	void insertAnswer(char n){
		// If this is the first time someone has answered this question, increment the totalAnswers tracker
		if(hashSet[n-'a'] == 0)
			totalAnswers++;
		// Increment the number of answer to the question
		hashSet[n-'a']++;
	}

	// function that increments the group size
	void incrementGroupSize(){
		groupSize++;
	}
	// returns the totalAnswers
	int getAnswers(){
		return totalAnswers;
	}
	// Calculates number answers everyone in the group answered yes to
	int getSharedAnswers(){
		int count = 0;
		for (int i = 0; i < 26; i++){
			// Only increment if everyone in the group answered the question
			if (hashSet[i] == groupSize)
				count++;
		}
		// Return the count
		return count;
	}
};

// Reads input file and return a vector<groupAnswers> from the input
vector<groupAnswers> readInput(string file){
	// Vector to store the result in
	vector<groupAnswers> allGroupAnswers;
	// Instantinate the input file object and open the file
	ifstream inFile;
	inFile.open(file);
	// Read line by line into a string and then push back into the allGroupAnswers vector when we hit a blank line
	string line;
	// Current group object
	groupAnswers *currGroup = new groupAnswers;
	while (getline(inFile,line)){
		// When we hit a blank line push back the current group to the vector and reset it
		if (line == ""){
			allGroupAnswers.push_back(*currGroup);
			currGroup = new groupAnswers;
		} else {
		// Increment the group size for every line
		currGroup->incrementGroupSize();
		// Insert every answer using groupAnswers->insertAnswer();
		for (int i = 0; i < line.size(); i++)
			currGroup->insertAnswer(line[i]);
		}
	}
	// Don't forget to push back the last group!
	allGroupAnswers.push_back(*currGroup);

	// Close the file
	inFile.close();
	// Return the allGroupAnswers vector
	return allGroupAnswers;
}

// Returns the sum of the number of answers that anyone in a particular group answered yes to
int sumAnswers(vector<groupAnswers> allGroupAnswers){
	int total = 0;
	for (int i = 0; i < allGroupAnswers.size(); i++){
		total += allGroupAnswers[i].getAnswers();
	}
	return total;
}

// Returns the sum of the number of answers that everyone in a group answered yes to
int sumSharedAnswers(vector<groupAnswers> allGroupAnswers){
	int total = 0;
	for (int i = 0; i < allGroupAnswers.size(); i++){
		total += allGroupAnswers[i].getSharedAnswers();
	}
	return total;
}

int main(){
	// Read the input into a vector of ints
	vector<groupAnswers> allGroupAnswers = readInput("input6.txt");
	
	// Output the results
	cout << "Part 1: " << sumAnswers(allGroupAnswers) << endl;
	cout << "Part 2: " << sumSharedAnswers(allGroupAnswers) << endl;
	return 0;
}
