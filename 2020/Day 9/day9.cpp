using namespace std;

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

// Class to break the XMAS encryption
class xmas{
	vector<long long> input;

	public:
	void readInput(string file){
		// Instantinate the input file object and open the file
		ifstream inFile;
		inFile.open(file);
		// Read line by line into an int and then push back into the input vector
		long long number;
		while (inFile >> number)
			input.push_back(number);
		// Close the file
		inFile.close();
	}

	// Simple O(N^2) twoSum that checks between start and end vector values for target
	// and returns true if the target can be summed to
	bool twoSum(int start, int end, long long target){
		for (int i = start; i <= end; i++)
			for (int j = i+1; j <= end; j++)
				if (input[i] + input[j] == target)
					return true;
			
		return false;
	}

	// Finds the first number that is not a sum of the previous preambleLength before it
	long long findWeakness(int preambleLength){
		int start = preambleLength;
		int end = start+preambleLength;

		// Loop until we either find the weakness or hit the end
		while (end-1 < input.size()){
			if (!twoSum(start, end, input[end+1])){
				return input[end+1];
			} else {
				// Increment start and end for the next check
				start++;
				end++;
			}
		}
	}

	// Returns the contiguous sum of the input in the specified range
	long long getSum(int start, int end){
		long long result = 0;
		for (int i = start; i <= end; i++){
			result += input[i];
		}
		return result;
	}

	// Gets the max value of the input within the specified range
	long long getMin(int start, int end){
		long long min = input[end];
		for (int i = start; i < end; i++)
			if (input[i] < min)
				min = input[i];
		
		return min;
	}

	// Gets the min value of the input within the specified range
	long long getMax(int start, int end){
		long long max = input[end];
		for (int i = start; i < end; i++)
			if (input[i] > max)
				max = input[i];
		
		return max;
	}

	// Returns the sum of the smallest and largest number in the contiguous range of the input that sums to the target
	long long breakEncryption(int preambleLength){
		// First get the target from the previous part
		long long target = findWeakness(preambleLength);
		int start;
		int end;

		// Bruteforce the contiguous set that sums to target that is larger than 1
		for (int i = 0; i < input.size(); i++){
			for (int j = i; j < input.size(); j++){
				if (getSum(i,j) == target && i != j){
					start = i;
					end = j;
				}
			}
		}
		
		return getMin(start, end) + getMax(start, end);;
	}
};

int main(){
	// Create the eXchange-Masking Addition System object
	xmas xmasObj;
	// Read the input
	xmasObj.readInput("input9.txt");

	// Output the results
	cout << "Part 1: " << xmasObj.findWeakness(25) << endl;
	cout << "Part 2: " << xmasObj.breakEncryption(25) << endl;
	return 0;
}
