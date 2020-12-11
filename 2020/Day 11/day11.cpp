using namespace std;

#include <iostream>
#include <vector>
#include <fstream>

// Class that stores and models seat occupation of the ferry
class ferrySeating{
	vector<string> seats;

	public:

	// Loads inital seating layout from text file
	void loadSeats(string file){
		// Clear the old seat layout (if any)
		seats.clear();
		// Instantinate the input file object and open the file
		ifstream inFile;
		inFile.open(file);
		// Read line by line into a string and push it back to the seats vector
		string line;
		while (inFile >> line){
			seats.push_back(line);
		}
		// Close the file
		inFile.close();
	}

	// Helper function that will print the seating layout to the terminal (useful for debugging)
	void printSeats(){
		for (int row = 0; row < seats.size(); row++){
			for (int col = 0; col < seats[row].size(); col++){
				cout << seats[row][col];
			}
			cout << endl;
		}
		cout << endl;
	}

	// Returns the number of occupied seats adjacent to the passed seat
	int adjacentOccupiedSeats(int row, int col){
		int count = 0;

		// Check seat above
		if (row-1 >= 0 && seats[row-1][col] == '#')
			count++;
		// Check seat below
		if (row+1 < seats.size() && seats[row+1][col] == '#')
			count++;
		// Check seat to right
		if (col+1 < seats[row].size() && seats[row][col+1] == '#')
			count++;
		// Check seat to left
		if (col-1 >= 0 && seats[row][col-1] == '#')
			count++;
		// Check upper left corner
		if (row-1 >= 0 && col-1 >= 0 && seats[row-1][col-1] == '#')
			count++;
		// Check lower left corner
		if (row+1 < seats.size() && col-1 >= 0 && seats[row+1][col-1] == '#')
			count++;
		// Check upper right corner
		if (row-1 >= 0 && col+1 < seats[row].size() && seats[row-1][col+1] == '#')
			count++;
		// Check lower right corner
		if (row+1 < seats.size() && col+1 < seats[row].size() && seats[row+1][col+1] == '#')
			count++;

		// Return the total adjacent seats
		return count;
	}

	// Updates seats based on predictable set of seating rules
	// Returns true if there was changes made
	bool updateSeats(){
		// Create a new vector to store the new seating layout
		vector<string> newSeats = seats;
		// Variable to track if we made any changes
		bool changed = false;
		// Go through each seat and update according to the rules
		for (int row = 0; row < seats.size(); row++){
			for (int col = 0; col < seats[row].size(); col++){
				if (seats[row][col] == 'L' && adjacentOccupiedSeats(row, col) == 0){
					newSeats[row][col] = '#';
					changed = true;
				}
				if (seats[row][col] == '#' && adjacentOccupiedSeats(row, col) >= 4){
					newSeats[row][col] = 'L';
					changed = true;
				}
			}
		}
		// Set the seats to the newSeats layout
		seats = newSeats;
		// Return whether or not we made any changes
		return changed;
	}

	// Returns the number of occupied seats after the searting area has stablized
	int finalOccupiedSeats(){
		int occupied = 0;
		// Update seats until they no longer change
		while (updateSeats());

		// Get the count of occupied seats
		for (int row = 0; row < seats.size(); row++)
			for (int col = 0; col < seats[row].size(); col++)
				if (seats[row][col] == '#')
					occupied++;

		return occupied;
	}

	/* Part 2 */

	// Enumuration for all 8 directions
	enum directions {N, E, S, W, NE, NW, SE, SW};

	// Returns true if an occupied seat is seen in a given direction before an empty seat
	bool checkDirection(int row, int col, directions dir){
		// First return false if we went out of bounds (we didn't find an occupied seat)
		if (row < 0 || row >= seats.size() || col < 0 || col >= seats[row].size())
			return false;

		// Check if the seat is occupied and return true if so
		if (seats[row][col] == '#')
			return true;
		// Check if we hit an unoccupied seat and return false if so
		if (seats[row][col] == 'L')
			return false;

		// Recursively check the next seat in the given direction
		switch (dir){
			case N:  return checkDirection(row-1, col, N);
			case S:  return checkDirection(row+1, col, S);
			case E:  return checkDirection(row, col+1, E);
			case W:  return checkDirection(row, col-1, W);
			case NE: return checkDirection(row-1, col+1, NE);
			case NW: return checkDirection(row-1, col-1, NW);
			case SE: return checkDirection(row+1, col+1, SE);
			case SW: return checkDirection(row+1, col-1, SW);
		}
	}

	// Counts number of seats that are seen first in all 8 directions
	int countSeatsDirection(int row, int col){
		int count = 0;
		// Check all directions for an occupied seat and update count
		if (checkDirection(row-1, col, N))
			count++;
		if (checkDirection(row+1, col, S))
			count++;
		if (checkDirection(row, col+1, E))
			count++;
		if (checkDirection(row, col-1, W))
			count++;
		if (checkDirection(row-1, col+1, NE))
			count++;
		if (checkDirection(row-1, col-1, NW))
			count++;
		if (checkDirection(row+1, col+1, SE))
			count++;
		if (checkDirection(row+1, col-1, SW))
			count++;
		
		// Return total count
		return count;
	}

	// Updates seats based on revised predictable set of seating rules
	// Returns true if there was changes made
	bool updateSeatsRevised(){
		// Create a new vector to store the new seating layout
		vector<string> newSeats = seats;
		// Variable to track if we made any changes
		bool changed = false;
		// Go through each seat and update according to the rules
		for (int row = 0; row < seats.size(); row++){
			for (int col = 0; col < seats[row].size(); col++){
				if (seats[row][col] == 'L' && countSeatsDirection(row, col) == 0){
					newSeats[row][col] = '#';
					changed = true;
				}
				if (seats[row][col] == '#' && countSeatsDirection(row, col) >= 5){
					newSeats[row][col] = 'L';
					changed = true;
				}
			}
		}
		// Set the seats to the newSeats layout
		seats = newSeats;
		// Return whether or not we made any changes
		return changed;
	}

	// Returns the number of revised occupied seats after the seating area has stablized
	int finalOccupiedSeatsRevised(){
		int occupied = 0;
		// Update seats until they no longer change
		while (updateSeatsRevised());

		// Get the count of occupied seats
		for (int row = 0; row < seats.size(); row++)
			for (int col = 0; col < seats[row].size(); col++)
				if (seats[row][col] == '#')
					occupied++;

		return occupied;
	}
};

int main(){
	// Create the ferrySeating object and load the seat layout
	ferrySeating seats;
	seats.loadSeats("input11.txt");

	// Output part 1 result
	cout << "Part 1: " << seats.finalOccupiedSeats() << endl;

	// Reload the original seats
	seats.loadSeats("input11.txt");

	// Output part 2 result
	cout << "Part 2: " << seats.finalOccupiedSeatsRevised() << endl;
	return 0;
}
