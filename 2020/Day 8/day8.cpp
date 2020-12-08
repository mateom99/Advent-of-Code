using namespace std;

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

// Stuct that store an insturction, its immediate, and if it was executed or not
struct instructions{
	string operation;
	int immediate;
	bool executed;
};

// handheldProcessor class that runs the boot code for a handhelp processor
class handheldProcessor{
	// Track the current instruction we are on (Program Counter)
	int PC = 0;
	int accumulator = 0;
	// Vector of bootCode instructions
	vector<instructions> bootCode;

	public:
	// Adds an instruction to the handheldProcessors ram
	void addInstruction(string operation, int immediate){
		instructions instr;
		instr.operation = operation;
		instr.immediate = immediate;
		instr.executed = false;
		bootCode.push_back(instr);
	}

	// Programs the handheldProcessor from an input file
	void programProcessor(string file){
		// Instantinate the input file object and open the file
		ifstream inFile;
		inFile.open(file);
		// Read line by line and add each instruction to the processor
		string line;
		while (getline(inFile, line)){
			stringstream ss;
			ss << line;
			string operation;
			string immediate;
			// Populate the operator and immediate
			ss >> operation >> immediate;
			// Add the instruction to the processor
			addInstruction(operation, stoi(immediate));
		}
		// Close the file
		inFile.close();
	}

	// Resets accumulator, program counter, and all instructions to not executed (Powercycle the processor)
	void reset(){
		for (int i = 0; i < bootCode.size(); i++)
			bootCode[i].executed = false;;
		accumulator = 0;
		PC = 0;
	}

	// Executes an instruction
	void execute(){
		// Only increment the PC for a no operation instruction
		if (bootCode[PC].operation == "nop"){
			bootCode[PC].executed = true;
			PC++;
			return;
		}
		// Increment the accumulator by the immediate
		if (bootCode[PC].operation == "acc"){
			bootCode[PC].executed = true;
			accumulator += bootCode[PC].immediate;
			PC++;
			return;
		}
		// Jump the program coutner by the immediate
		if (bootCode[PC].operation == "jmp"){
			bootCode[PC].executed = true;
			PC += bootCode[PC].immediate;
			return;
		}
	}

	// Returns the value of the accumulator just before it enters an infinite loop
	int accumulatorBeforeLoop(){
		// Execute until as long as we aren't in a loop
		while(PC < bootCode.size()){
			if(bootCode[PC].executed == false)
				execute();
			else{
				// Reset the processor when we hit a loop and return the accumulator value before the reset
				int result = accumulator;
				reset();
				return result;
			}
		}
	}

	// Checks if the program will eventually cause an infite loop
	bool checkLoop(){
		// Execute until as long as we aren't in a loop
		while(PC < bootCode.size()){
			if(bootCode[PC].executed == false)
				execute();
			else{
				// Reset the processor when we hit a loop and return true;
				reset();
				return true;
			}
		}
		// Reset the processor and return false since we didn't hit an infinite loop
		reset();
		return false;
	}

	// Fixes an instruction that causes an infite loop in the program
	void fixLoop(){
		// Try to change every nop to jmp and jmp to nop one by one and check if we still hit a loop
		for (int i = 0; i < bootCode.size(); i++){
			// Do nothing for accumulator function
			if (bootCode[i].operation == "acc")
				continue;
			// Change nop to jmp and check if we hit a loop
			if (bootCode[i].operation == "nop"){
				bootCode[i].operation = "jmp";
				if (!checkLoop()){
					return;
				} else {
					// Change the instruction back and continue trying
					bootCode[i].operation = "nop";
					continue;
				}
			}
			// Change jmp to nop and check if we hit a loop
			if (bootCode[i].operation == "jmp"){
				bootCode[i].operation = "nop";
				if (!checkLoop()){
					return;
				} else {
					// Change the instruction back and continue trying
					bootCode[i].operation = "jmp";
					continue;
				}
			}
		}
	}
	
	// Runs a complete boot program after fixing the infinite loop
	int run(){
		// First fix the loop
		fixLoop();
		
		// Execute until we are at the end of the program
		while (PC < bootCode.size())
			execute();

		// Reset the processor and return the accumulator value before the reset
		int acc = accumulator;
		reset();
		return acc;
	}
};

int main(){
	// Create a handheldProcessor processor
	handheldProcessor processor;
	// Program the processor from the input file
	processor.programProcessor("input8.txt");
	// Output the result
	cout << "Part 1: " << processor.accumulatorBeforeLoop() << endl;
	cout << "Part 2: " << processor.run() << endl;
	return 0;
}
