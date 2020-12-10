using namespace std;

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

class adapters{
	vector<int> adapterList;

	public:
	// Loads adapters from a text file into the adapterList vector
	void loadAdapters(string file){
		// First pushback the starting zero adapter
		adapterList.push_back(0);
		// Instantinate the input file object and open the file
		ifstream inFile;
		inFile.open(file);
		// Read line by line into an int and then push back into the adapterList vector
		int number;
		while (inFile >> number){
			adapterList.push_back(number);
		}
		// Sort the list after we are done adding them
		sort(adapterList.begin(), adapterList.end());
		// Add the built-in adapters to the list (3 higher)
		adapterList.push_back(adapterList[adapterList.size()-1]+3);
		// Close the file
		inFile.close();
	}

	// Returns the number of 1-jolt differnces multipled by the number 3-jolt differences
	// Note: Our adapterList is sorted
	int countDifferences(){
		int differencesOne = 0;
		int differencesThree = 0;
		int prevAdapter = 0;
		for (int i = 1; i < adapterList.size(); i++){
			// Increment 1 jolt differences if the previous adapter is 1-jolt away
			if (adapterList[i] - prevAdapter == 1)
				differencesOne++;
			// Increment 3 jolt differences if the previous adapter is 3-jolt away
			if (adapterList[i] - prevAdapter == 3)
				differencesThree++;
			// Set the new previous adapter
			prevAdapter = adapterList[i];
		}
		return differencesOne*differencesThree;
	}
	
	// Returns the number of adapters that can plug into the adapter at index n
	int possibilties(int n){
		int count = 0;
		// Check the previous 3 adapters and increment counts for every adapter that is 3 or less away
		if (n-1 >= 0 && adapterList[n]-adapterList[n-1] <= 3)
			count++;
		if (n-2 >= 0 && adapterList[n]-adapterList[n-2] <= 3)
			count++;
		if (n-3 >= 0 && adapterList[n]-adapterList[n-3] <= 3)
			count++;
		// Return the count
		return count;
	}

	// Returns the number of possible combinations connecting to the the outlet to our device using dynamic programming
	// Note: Our adapterList is sorted
	long countCombinations(){
		// Create a vector used to store dynamic programming result that is the same size as the adapterList vector
		// This vector will store the number of combinations of the adapter at that index
		vector<long> DP(adapterList.size());
		// The first adapter (0) only has 1 combination
		DP[0] = 1;
		// To get the remaining number of combinations we simply add the number of possiblities of adapters
		// before it that could connect to the current one
		for (int i = 1; i < adapterList.size(); i++){
			// Get the number of adapters that can connect to this one using possiblites();
			int poss = possibilties(i);
			// Add the number of combinations from the previous "poss" adapters
			if (poss == 1)
				DP[i] = DP[i-1];
			else if (poss == 2)
				DP[i] = DP[i-1] + DP[i-2];
			else if (poss == 3)
				DP[i] = DP[i-1] + DP[i-2] + DP[i-3];
		}
		// Return the number combinations to the device
		return DP[adapterList.size()-1];
	}
};

int main(){
	// Create the adapters object
	adapters myAdapters;
	// Load the adapters from the input file
	myAdapters.loadAdapters("input10.txt");

	// Output the results
	cout << "Part 1: " << myAdapters.countDifferences() << endl;
	cout << "Part 2: " << myAdapters.countCombinations() << endl;
	return 0;
}
