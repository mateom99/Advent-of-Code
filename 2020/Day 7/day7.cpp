using namespace std;

#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <sstream>

// Structure to contains bag and numbers of said bag
struct bagType{
	string name;
	int count;
};

// Class that stores organizes all bag info and contains methods that return details
class bags{
	// Maps a bag to a vector of bags it holds
	unordered_map<string, vector<bagType>> bagMap;

	public:
	// Adds a bag to the bagMap
	void addBag(string newBag, vector<bagType> bagList){
		bagMap[newBag] = bagList;
	}

	// Recursively checks if a bag eventually contains a shiny gold bag
	bool containsGold(string bagName){
		// Get the list of bags the current bag contains
		vector<bagType> bagList;
		bagList = bagMap.find(bagName)->second;
		// If this bag contatins no other bags then it can't contain a shiny gold bag
		if (bagList.size() == 0)
			return false;
		for (int i = 0; i < bagList.size(); i++){
			// Check if it contains a shiny gold bag and return return true if so
			if (bagList[i].name == "shiny gold")
				return true;
			// Otherwise return true if any bags within the bag containg shiny gold bag
			if (containsGold(bagList[i].name) == true)
				return true;
		}
		// Return false if we never found a shiny gold bag
		return false;
	}

	// Returns the number of bags that eventually contain a shiny gold bag
	int countGoldPossibilites(){
		int count = 0;
		unordered_map<string, vector<bagType>>::iterator itr;
		// Increment count for every bag that contains a shiny gold bag
		for (itr = bagMap.begin(); itr != bagMap.end(); itr++){
			if (containsGold(itr->first))
				count++;
		}
		return count;
	}

	// Recursively counts all bags within a bag
	int countBagsInside(string bagName){
		// Get the list of bags the current bag contains
		vector<bagType> bagList;
		bagList = bagMap.find(bagName)->second;

		int total = 1;
		// Get the total by multiplying the count with the number of bags inside the next bag for every bag in the bagList
		for (int i = 0; i < bagList.size(); i++){
			total += (bagList[i].count * countBagsInside(bagList[i].name));
		}
		return total;
	}

	// Returns the number of bags inside a shiny gold bag
	int countBagsInsideGold(){
		return countBagsInside("shiny gold") - 1;
	}
};

// Reads input file and return a bags object from the input
bags readInput(string file){
	// Bags object to store input in to
	bags allBags;
	// Instantinate the input file object and open the file
	ifstream inFile;
	inFile.open(file);
	// Read line by line into an string
	string line;
	while (getline(inFile, line)){
		// Create a stringstream for the current line
		stringstream ss;
		ss << line;
		// Current bag name
		string currBag;
		// Read the current word from the string stream
		string word;
		ss >> word;
		while (word != "bags"){
			currBag += word;
			currBag += " ";
			ss >> word;
		}
		// Remove the space at the end
		currBag.pop_back();
		// Skip over "bags contain"
		ss >> word >> word;
		
		// Vector to store bags the current bag contains
		vector<bagType> bagList;

		// Loop until we hit the end of the line
		while(!ss.eof()){
			// If there are no other bags, push the result back and break from the loop
			if (word == "no"){
				allBags.addBag(currBag, bagList);
				break;
			}
			
			// Loop and get all cotnianed bags
			while(word[word.length()-1] != ',' && word[word.length()-1] != '.' && !ss.eof()){
				// First get the count
				string count = word;
				ss >> word;
				string containedBagName;
				bagType containedBag;
				// Get the bag name
				while (word != "bags," && word != "bags." && word != "bag," && word != "bag."){
					containedBagName += word;
					containedBagName += " ";
					ss >> word;
				}
				// Remove the space at the end of the bag name
				containedBagName.pop_back();
				// Update the containedBag object
				containedBag.count = stoi(count);
				containedBag.name = containedBagName;
				// Push back the containedBag to the bad list
				bagList.push_back(containedBag);
			}
			// Add the bag to the main class
			allBags.addBag(currBag, bagList);
			ss >> word;
		}
	}
	// Close the file
	inFile.close();
	// Return the object
	return allBags;
}

int main(){
	// Read the input into a vector of ints
	bags bagList = readInput("input7.txt");
	// Output the result
	cout << "Part 1: " << bagList.countGoldPossibilites() << endl;
	cout << "Part 2: " << bagList.countBagsInsideGold() << endl;
	return 0;
}