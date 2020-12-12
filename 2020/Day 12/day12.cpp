using namespace std;

#include <iostream>
#include <vector>
#include <fstream>

// Stores the navigation instruction and amount
struct navInstr{
	char instr;
	int amount;
};

// Ship class for processing navigation instructions
class ship{
	vector<navInstr> instructions;
	int X = 0;
	int Y = 0;
	int wpX = 10;
	int wpY = 1;
	int heading = 90;

	public:
	// load ship instructions from text file
	void loadinstructions(string file){
		// Instantinate the input file object and open the file
		ifstream inFile;
		inFile.open(file);
		// Read line by line into and store each instruction
		string line;
		while (inFile >> line){
			// Create a new instruction
			navInstr currInstr;
			// Get the instruction and amount
			currInstr.instr = line[0];
			currInstr.amount = stoi(line.substr(1));
			// Add it to the instructions vector
			instructions.push_back(currInstr);
		}
		// Close the file
		inFile.close();
	}

	// Moves the ship based on the direction and amount
	void move(char dir, int amount){
		if (dir == 'N')
			Y+= amount;
		if (dir == 'S')
			Y-= amount;
		if (dir == 'E')
			X+= amount;
		if (dir == 'W')
			X-= amount;
	}

	// Moves the ship forward in the direction it is facing by the given amount
	void forward(int amount){
		switch (heading){
			case 0: move('N', amount);
					break;
			case 90: move('E', amount);
					break;
			case 180: move('S', amount);
					break;
			case 270: move('W', amount);
					break;
		}
	}

	// Turns the ship in the given direction by the given degrees
	void turn(char dir, int degrees){
		if (dir == 'L'){
			// For the negative direction, simply move 360-amount forward
			heading += (360-degrees);
			// Wrap around if we went of 360 degrees
			heading %= 360;
		}
		if (dir == 'R'){
			heading += degrees;
			// Wrap degrees if we went of 360 degrees
			heading %= 360;
		}
	}

	// Processes every instruction using helper functions above and return the manhattan distance of the ship
	int processInstructions(){
		for (int i = 0; i < instructions.size(); i++){
			switch(instructions[i].instr){
				case 'N': move('N', instructions[i].amount);
				          break;
				case 'S': move('S', instructions[i].amount);
						  break;
				case 'E': move('E', instructions[i].amount);
						  break;
				case 'W': move('W', instructions[i].amount);
						  break;
				case 'L': turn('L', instructions[i].amount);
						  break;
				case 'R': turn('R', instructions[i].amount);
						  break;
				case 'F': forward(instructions[i].amount);
						  break;
			}
		}
		return abs(X) + abs(Y);
	}


	// Moves the ship's waypoint based on the direction and amount
	void wpMove(char dir, int amount){
		if (dir == 'N')
			wpY+= amount;
		if (dir == 'S')
			wpY-= amount;
		if (dir == 'E')
			wpX+= amount;
		if (dir == 'W')
			wpX-= amount;
	}

	// Moves the ship towards the waypoint the given number of times
	void forwardToWaypoint(int amount){
		X += (wpX*amount);
		Y += (wpY*amount);
	}

	// Rotates the waypoint around the ship a given amount of degrees
	void wpTurn(char dir, int amount){
		// How many 90 degree turns
		int times = amount/90;
		// For every 90 degree turn
		for (int i = 0; i < times; i++){
			if (dir == 'L'){
				int temp = wpX;
				wpX = -wpY;
				wpY = temp;
			}
			if (dir == 'R'){
				int temp = wpX;
				wpX = wpY;
				wpY = -temp;
			}
		}
	}

	// Processes every instruction using helper functions above for part two and return the manhattan distance of the ship
	int newProcessInstructions(){
		// First reset the cordinates from part 1
		X = 0;
		Y = 0;
		for (int i = 0; i < instructions.size(); i++){
			switch(instructions[i].instr){
				case 'N': wpMove('N', instructions[i].amount);
				          break;
				case 'S': wpMove('S', instructions[i].amount);
						  break;
				case 'E': wpMove('E', instructions[i].amount);
						  break;
				case 'W': wpMove('W', instructions[i].amount);
						  break;
				case 'L': wpTurn('L', instructions[i].amount);
						  break;
				case 'R': wpTurn('R', instructions[i].amount);
						  break;
				case 'F': forwardToWaypoint(instructions[i].amount);
						  break;
			}
		}
		return abs(X) + abs(Y);
	}
};

int main(){
	// Create the ship object
	ship myShip;
	// Load the ship instructions
	myShip.loadinstructions("input12.txt");

	// Output the results
	cout << "Part 1: " << myShip.processInstructions() << endl;
	cout << "Part 2: " << myShip.newProcessInstructions() << endl;
	return 0;
}
