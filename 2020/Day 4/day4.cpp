using namespace std;

#include <iostream>
#include <vector>
#include <fstream>

// Abstract datatype to store passport information with various helper methods
class passport{
	// Fields
	string byr;
	string iyr;
	string eyr;
	string hgt;
	string hcl;
	string ecl;
	string pid;
	string cid;

	public:
	// Resets the current passports fields
	void reset(){
		byr.clear();
		iyr.clear();
		eyr.clear();
		hgt.clear();
		hcl.clear();
		ecl.clear();
		pid.clear();
		cid.clear();
	}

	// Sets specified field
	void setField(string field, string val){
		if (field == "byr")
			byr = val;
		if (field == "iyr")
			iyr = val;
		if (field == "eyr")
			eyr = val;
		if (field == "hgt")
			hgt = val;
		if (field == "hcl")
			hcl = val;
		if (field == "ecl")
			ecl = val;
		if (field == "pid")
			pid = val;
		if (field == "cid")
			cid = val;
	}

	// Check if the passport is valid for part 1 (has all fields with cid optional)
	bool isValid(){
		return !(byr.empty() || iyr.empty() || eyr.empty() || hgt.empty() || hcl.empty() || ecl.empty() || pid.empty());
	}
	
	//Check if the passport is valid for part 1 (has all fields within requirments with cid optional)
	bool isValidStrict(){
		// Return false immeditially if the passport doesn't fit the basic requirments
		if (!isValid())
			return false;

		// Next we check more strict requirments

		/* Check byr */
		if (byr.empty() || stoi(byr) < 1920 || stoi(byr) > 2002)
			return false;

		/* Check iyr */
		if (iyr.empty() || stoi(iyr) < 2010 || stoi(iyr) > 2020)
			return false;

		/* check eyr */
		if (eyr.empty() || stoi(eyr) < 2020 || stoi(eyr) > 2030)
			return false;

		/* check hgt */
		// First get cm/in (last two chars)
		string measurment = hgt.substr(hgt.size()-2);
		// Then get the height (stoi stops when it hits a non digit)
		int heightVal = stoi(hgt);
		// Not check if the measurments are valid and return false if not
		if (measurment == "cm" && (heightVal < 150 || heightVal > 193))
			return false;
		if (measurment == "in" && (heightVal < 59 || heightVal > 76))
			return false;
		if (measurment != "cm" && measurment != "in")
			return false;

		/* check hcl */
		// First make sure we have a # and have 6 character following (7 total)
		if (hcl[0] != '#' || hcl.size() != 7)
			return false;
		// Next we make sure the characters a valid hex (we use ascii values and some logic to quickly check)
		for (int i = 1; i < hcl.size(); i++){
			// Looks complex but just says if not between either 48(0) and 57(9) or 97(a) and 102(f) return false
			if (!((hcl[i] >= 48 && hcl[i] <= 57) || (hcl[i] >= 97 && hcl[i] <= 102)))
				return false;
		}

		/* check ecl */
		if (ecl != "amb" && ecl != "blu" && ecl != "brn" && ecl != "gry" && ecl != "grn" && ecl != "hzl" && ecl != "oth")
			return false;

		/* check pid */
		// Count the number of digits and at the same time return false if any is not a digit
		int digits = 0;
		for (int i = 0; i < pid.size(); i++){
			if (pid[i] < 48 ^ pid[i] > 57)
				return false;
			digits++;
		}
		// Finally return false if we don't have 9 digits
		if (digits != 9)
			return false;

		// Return true if we didn't fail any checks
		return true;
	}
};

// Reads input file and return a vector of passport structs
vector<passport> readInput(string file){
	// Vector to store the result in
	vector<passport> passports;
	// Instantinate the input file object and open the file
	ifstream inFile;
	inFile.open(file);
	// Current passport object (to be pushed back to the vector)
	passport currPassport;
	// Read the input file line by line
	string line;
	while (getline(inFile, line)){
		// Track where we are in the current line
		int index = 0;

		// If the current line is empty we are done processing the current passport
		// So push it back to the result vector and clear it for the next passport
		if (line == ""){
			passports.push_back(currPassport);
			currPassport.reset();
		}

		// Loop through the current line
		while (index < line.size()){
			// Get the field name (all 3 chars)
			string fieldName = line.substr(index, 3);
			index += 4;
			// Loop until we hit a space to get the value
			string fieldVal = "";
			while (line[index] != ' ' && index < line.size()){
				fieldVal += line[index];
				index++;
			}
			// Jump past the space
			index++;
			// Set the value using passport's setField method
			currPassport.setField(fieldName, fieldVal);
		}
	}

	// Don't forget to pushBack the last passport!
	passports.push_back(currPassport);

	// Close the file
	inFile.close();
	// Return the result vector
	return passports;
}

int countValidPassports(vector<passport> passports){
	// Track number of valid passports
	int validPassports = 0;

	// Check every passport and increment validPassports respectively
	for (int i = 0; i < passports.size(); i++)
		if (passports[i].isValid())
			validPassports++;
		
	// Return the number of valid passports
	return validPassports;
}

int countValidPassportsStrict(vector<passport> passports){
	// Track number of valid passports
	int validPassports = 0;

	// Check every passport and increment validPassports respectively
	for (int i = 0; i < passports.size(); i++)
		if (passports[i].isValidStrict())
			validPassports++;
		
	// Return the number of valid passports
	return validPassports;
}

int main(){
	// Read the input into a vector of ints
	vector<passport> passports = readInput("input4.txt");

	// Output the result
	cout << "Part 1: " << countValidPassports(passports) << endl;
	cout << "Part 2: " << countValidPassportsStrict(passports) << endl;
	return 0;
}
