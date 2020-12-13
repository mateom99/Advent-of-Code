using namespace std;

#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

// For part 2 - stores bus ID and offset after t
struct busInfo{
	int id;
	int offset;
};

// Stores info about the bus schedule and finds various timestamps
class busService{
	int myDepartTime;	
	vector<string> busses;
	vector<busInfo> schedule;


	public:
	// Loads the bus times from a text file
	void loadBusTimes(string file){
		// Instantinate the input file object and open the file
		ifstream inFile;
		inFile.open(file);
		// Store the first line as myDepartTime
		inFile >> myDepartTime;
		// Get the next line
		string line;
		inFile >> line;
		int index = 0;
		string busTime;
		while (index < line.size()){
			// Get each bus time
			busTime = "";
			while(line[index] != ',' && index < line.size()){
				busTime += line[index];
				index++;
			}
			index++;
			// Add the bus time to the vector
			busses.push_back(busTime);
		}
		// Close the file
		inFile.close();
	}
	// Finds the earliest timestamp we could depart
	int findEarliestBus(){
		// Assumme the first bus is the earlist time:
		// We simply divide our earliest depart time by the current bus time, round up
		// and multiply by the current bus time to see the earliest time we can take that bus
		int earliestTime = ceil((double)myDepartTime/stoi(busses[0])) * stoi(busses[0]);
		int earliestID = stoi(busses[0]);
		// Check the remaining busses
		for (int i = 1; i < busses.size(); i++){
			if (busses[i] == "x")
				continue;
			int currTime = ceil((double)myDepartTime/stoi(busses[i])) * stoi(busses[i]);
			if (currTime < earliestTime){
				earliestTime = currTime;
				earliestID = stoi(busses[i]);
			}
		}
		return (earliestTime-myDepartTime)*earliestID;
	}

	// Stores the bus schedule according to part 2
	void storeSchedule(){
		for (int i = 0; i < busses.size(); i++){
			if (busses[i] == "x")
				continue;
			busInfo currBus;
			currBus.id = stoi(busses[i]);
			currBus.offset = i;
			schedule.push_back(currBus);
		}
	}

	// Find the timestamp when all the busses line up
	long long completeChallenge(){
		// First store the schedule with 't' offsets
		storeSchedule();
		// Bruteforce approach - slightly faster
		// We notice that the in our input since bus 0's time is 17 and 17 minutes after that bus 2 should arrive
		// Thus, we know that we only need to check positions at bus[0]*bus[2]-bus[0] and can increment by
		// bus[2]*bus[0] every time which is 15,419 in my input as makes bruteforce slightly more feasible
		// Now we just check when all 8 conditions align and return the timestamp
		for (long long i = schedule[0].id*schedule[2].id; i < 9223372036854775807; i+=schedule[0].id*schedule[2].id){
			long long x = i-schedule[0].id;
			if (((x+schedule[1].offset) % schedule[1].id) == 0)
				if (((x+schedule[2].offset) % schedule[2].id) == 0)
					if (((x+schedule[3].offset) % schedule[3].id) == 0)
						if (((x+schedule[4].offset) % schedule[4].id) == 0)
							if (((x+schedule[5].offset) % schedule[5].id) == 0)
								if (((x+schedule[6].offset) % schedule[6].id) == 0)
									if (((x+schedule[7].offset) % schedule[7].id) == 0)
										if (((x+schedule[8].offset) % schedule[8].id) == 0)
											return x;
		}
		// Return -1 if we didn't find a timestamp (error)
		return -1;
	}
};

int main(){
	// Create the busService object and load the input
	busService busses;
	busses.loadBusTimes("input13.txt");

	// Output the result
	cout << "Part 1: " << busses.findEarliestBus() << endl;
	cout << "Part 2: " << busses.completeChallenge() << endl;
	return 0;
}
