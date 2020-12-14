using namespace std;

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include <unordered_map>

// Stores a memory instructions address, value, and mask to use
struct operation{
	int address;
	long val;
	string mask;
};

// Class that emulates a decoder for the sea port's computer system
class computerSystem{
	unordered_map<long, long> mem;
	vector<operation> instructions;

	public:

	// Loads the program from the passed input file
	void loadProgram(string file){
		// Instantinate the input file object and open the file
		ifstream inFile;
		inFile.open(file);
		// Various needed variables
		string line;
		string currMask;
		operation *newOp = new operation;
		// Read line by line and add results to the instructions vector
		while (getline(inFile, line)){
			stringstream ss;
			// If the line is the mask line
			if (line.find("mask") != string::npos){
				// Set the current mask
				ss << line;
				ss >> currMask >> currMask >> currMask;
			} 
			// If the line is a memory operation line
			else {
				// Get the address
				int index = 0;
				string address;
				while (line[index] != ']'){
					if (line[index] == 'm' || line[index] == 'e' || line[index] == '['){
						index++;
					} else {
						address += line[index];
						index++;
					}
				}
				// Store the address
				newOp->address = stoi(address);

				// Get the value
				string val;
				ss << line;
				ss >> val >> val >> val;
				// Store the value
				newOp->val = stol(val);

				// set the mask
				newOp->mask = currMask;
				// Push the instruction back
				instructions.push_back(*newOp);
				newOp = new operation;
			}
		}
		// Close the file
		inFile.close();
	}

	// Converts a 36-bit binary number to a decimal number
	long bin2Dec(string num){
		long dec = 0;
		for (int i = 35; i >= 0; i--)
			if (num[i] == '1')
				dec += pow(2, 35-i);
		return dec;
	}

	// Converts a 36-bit decimal number to a binary string
	string dec2Bin(long num){
		string bin = "";
		for (int i = 35; i >= 0; i--){
			if (num-pow(2,i) >= 0){
				num -= pow(2,i);
				bin += '1';
			} else {
				bin += '0';
			}
		}
		return bin;
	}

	// Applies a mask to the passed by reference num according to part 1 specifications
	void applyMask(string &num, string mask){
		for (int i = 0; i < 36; i++){
			if (mask[i] == 'X')
				continue;
			num[i] = mask[i];
		}
	}

	// Applies a mask to the passed by reference num according to part 2 specifications
	void applyMaskV2(string &num, string mask){
		for (int i = 0; i < 36; i++){
			if (mask[i] == '0')
				continue;
			num[i] = mask[i];
		}
	}

	// Runs the docking initialization program and returns the sum of all values left in memory with part 1 specifications
	long runInitialization(){
		// Run through every memory instruction
		for (int i = 0; i < instructions.size(); i++){
			// First convert the instruction to binary
			string binVal = dec2Bin(instructions[i].val);
			// Then apply the bitmask (instr value passed by reference)
			applyMask(binVal, instructions[i].mask);
			// Lastly convert back to decimal and store into the memory location
			mem[instructions[i].address] = bin2Dec(binVal);
		}

		// Finally sum up the memory address values and return the sum
		long memSum = 0;
		unordered_map<long, long>::iterator itr;
		for (itr = mem.begin(); itr != mem.end(); itr++)
			memSum += itr->second;
		return memSum;
	}

	// Recursively write every possible floating address with the passed val
	void writeFloating(string binAdr, int val){
		// Get the index of any floating bits, if any
		size_t floatingIndex = binAdr.find("X");
		// If there are no more then this memory address is complete
		if (floatingIndex == string::npos){
			// Convert the address to decimal and write the memory, then return
			mem[bin2Dec(binAdr)] = val;
			return;
		}
		// Set the address to 0 then recursively call writeFloating
		binAdr[floatingIndex] = '0';
		writeFloating(binAdr, val);
		// Set the address to 1 then recursively call writeFloating
		binAdr[floatingIndex] = '1';
		writeFloating(binAdr, val);
	}

	// Runs the docking initialization program and returns the sum of all values left in memory with part 2 specifications
	long runInitializationV2(){
		// First clear out any memory part 1 modified
		mem.clear();
		// Run through every memory instruction
		for (int i = 0; i < instructions.size(); i++){
			// First convert the address to binary
			string binAdr = dec2Bin(instructions[i].address);
			// Then apply the bitmask (addr value passed by reference)
			applyMaskV2(binAdr, instructions[i].mask);
			// Lastly write to all possible address values using writeFloating()
			writeFloating(binAdr, instructions[i].val);
		}

		// Finally, sum up the memory address values and return the sum
		long memSum = 0;
		unordered_map<long, long>::iterator itr;
		for (itr = mem.begin(); itr != mem.end(); itr++)
			memSum += itr->second;
		return memSum;
	}
};

int main(){
	// Create the computerSystem object and load the initialization program from the text file
	computerSystem shipComp;
	shipComp.loadProgram("input14.txt");

	// Output the results
	cout << "Part 1: " << shipComp.runInitialization() << endl;
	cout << "Part 2: " << shipComp.runInitializationV2() << endl;
	return 0;
}