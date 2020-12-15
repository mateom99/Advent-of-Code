using namespace std;

#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_map>

class memoryGame{
	// Track the current turn we are on
	int turn = 1;
	// Track the last spoken number
	int lastSpoken;
	// Maps a number to a vector of ints that stores each turn the number was spoken
	unordered_map<int, vector<int>> spoken;

	public:

	// Loads the starting numbers from the input file
	void loadStartingNumbers(string file){
		// Instantinate the input file object and open the file
		ifstream inFile;
		inFile.open(file);
		// Store the single line in a string
		string line;
		inFile >> line;
		// Track the index and vector for every turn the number appears
		int index = 0;
		vector<int> turns;
		// Store numbers until we hit the end of the line
		while (index < line.size()){
			string currNum;
			// Add to the current number until we hit a comma or hit the end of the line
			while (index < line.size() && line[index] != ','){
				currNum += line[index];
				index++;
			}
			index++;
			// Clear out the vector from anything in the previous iteration
			turns.clear();
			// Push back the current turn
			turns.push_back(turn);
			// Map the n umber to the turns vector
			spoken[stoi(currNum)] = turns;
			// Set the last spoken number to the current number
			lastSpoken = stoi(currNum);
			// Increment the turn
			turn++;
		}
		// Close the file
		inFile.close();
	}

	// Plays a turn and updates corresponding member variables
	void playTurn(){
		// Store the next number
		int nextNumber;
		// Set the iterator to the map pair of the last spoken number
		unordered_map<int, vector<int>>::iterator itr;
		itr = spoken.find(lastSpoken);
		// If the last spoken number was just spoken for the first ttime
		if (itr->second.size() == 1){
			// Set the next number to 0
			nextNumber = 0;
		} else{
			// Otherwise, set the number to the difference of the previous two times it was spoken
			nextNumber = itr->second[itr->second.size()-1] - itr->second[itr->second.size()-2];
		}
		
		// Check if the next number waqs spoken for the first time
		itr = spoken.find(nextNumber);
		if (itr == spoken.end()){
			// If so, map it to a vector of turns consisting of the current turn
			vector<int> turns;
			turns.push_back(turn);
			spoken[nextNumber] = turns;
		} else{
			// Otherwise, add the current turn to the numbers list of all turns
			itr->second.push_back(turn);
		}

		// Update the last spoken number
		lastSpoken = nextNumber;
		// Increment the turn
		turn++;
	}

	// Returns the 2020th number spoken
	int find2020thSpoken(){
		// play turns until we played the 2020th turn
		while (turn <= 2020)
			playTurn();

		return lastSpoken;
	}

	// Returns the 30 millionth number spoken
	int find30000000thSpoken(){
		// play turns until we played the 30,000,000th turn
		while (turn <= 30000000)
			playTurn();

		return lastSpoken;
	}
};



int main(){
	// Create the memoryGame object and load the starting numbers from the input file
	memoryGame game;
	game.loadStartingNumbers("input15.txt");

	// Output the results
	cout << "Part 1: " << game.find2020thSpoken() << endl;
	cout << "Part 2: " << game.find30000000thSpoken() << endl;
	return 0;
}
