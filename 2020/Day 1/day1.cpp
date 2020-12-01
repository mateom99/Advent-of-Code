using namespace std;

#include <iostream>
#include <vector>
#include <fstream>

// Reads input file and return a vector<int> from the input
vector<int> readInput(string file){
	// Vector to store the result in
	vector<int> result;
	// Instantinate the input file object and open the file
	ifstream inFile;
	inFile.open(file);
	// Read line by line into an int and then push back into the result vector
	int number;
	while (inFile >> number){
		result.push_back(number);
	}
	// Close the file
	inFile.close();
	// Return the result vector
	return result;
}

// Checks which two expenses sum to 2020 and returns their product
int twoSum2020(vector<int> expenses){
    for (int i = 0; i < expenses.size(); i++)
        for (int j = i+1; j < expenses.size(); j++)
                if (expenses[i] + expenses[j] == 2020)
                    return expenses[i] * expenses[j];
}

// Checks which three expenses sum to 2020 and returns their product
int threeSum2020(vector<int> expenses){
    for (int i = 0; i < expenses.size(); i++)
        for (int j = i+1; j < expenses.size(); j++)
            for (int k = j+1; k < expenses.size(); k++)
                if (expenses[i] + expenses[j] + expenses[k] == 2020)
                    return expenses[i] * expenses[j] * expenses[k];
}

int main(){
	// Read the input into a vector of ints
	vector<int> expenseReport = readInput("input1.txt");
	// Output the result
	cout << "Part 1: " << twoSum2020(expenseReport) << endl;
	cout << "Part 2: " << threeSum2020(expenseReport) << endl;
	return 0;
}
