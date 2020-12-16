using namespace std;

#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_set>

// Stores the ranges for a field on the ticket
struct field{
	int start1;
	int start2;
	int end1;
	int end2;
};

// Stores info on all the tickets and checks which are valid
class tickets{
	vector<field> fields;
	vector<int> myTicket;
	vector<vector<int>> tickets;
	vector<unordered_set<int>> possibleFields;

	public:
	// Reads input file
	void loadTicketInfo(string file){
		// Instantinate the input file object and open the file
		ifstream inFile;
		inFile.open(file);
		string line;
		getline(inFile, line);

		// Read each field line by line
		while (line != ""){

			// Create a new field object
			field newField;

			// Get to the first number
			size_t pos = line.find(":");
			pos+= 2;

			// Get the first start number
			string num;
			while (line[pos] != '-'){
				num += line[pos];
				pos++;
			}
			// Store the first start value to the field
			newField.start1 = stoi(num);
			num.clear();
			pos++;

			// Get the first end number
			while (line[pos] != ' '){
				num += line[pos];
				pos++;
			}
			// Store the first end value to the field
			newField.end1 = stoi(num);
			num.clear();
			pos+=4;

			// Get the second start number
			while (line[pos] != '-'){
				num += line[pos];
				pos++;
			}
			// Store the first start value to the field
			newField.start2 = stoi(num);
			num.clear();
			pos++;

			// Get the second end number
			num = line.substr(pos);
			// Store the first end value to the field
			newField.end2 = stoi(num);

			// Add the field to the vector of all fields
			fields.push_back(newField);
			getline(inFile, line);
		}

		// Get to our ticket line
		getline(inFile, line);
		getline(inFile, line);

		int index = 0;
		// Store our ticket values
		while (index < line.size()){
			string currVal;
			// Add to the current number until we hit a comma or hit the end of the line
			while (index < line.size() && line[index] != ','){
				currVal += line[index];
				index++;
			}
			index++;
			// Add the current value to our ticket
			myTicket.push_back(stoi(currVal));
		}

		// Get to the first nearby tickets line
		getline(inFile, line);
		getline(inFile, line);
		// Go through every line and store the values to the tickets vector
		while(getline(inFile, line)){
			vector<int> currTicket;
			int index = 0;
			while (index < line.size()){
				string currVal;
				// Add to the current number until we hit a comma or hit the end of the line
				while (index < line.size() && line[index] != ','){
					currVal += line[index];
					index++;
				}
				index++;
				// Add the current value to our ticket
				currTicket.push_back(stoi(currVal));
			}
			// Add the current ticket to the tickets vector
			tickets.push_back(currTicket);
		}

		// Close the file
		inFile.close();
	}

	// Checks if a ticket is possibly valid and if not returns the value
	// that caused it to be invalid, if the ticket was valid, returns -1
	int checkTicket(vector<int> ticket){
		for (int i = 0; i < ticket.size(); i++){
			// Start off assuming the ticket was invalid
			bool valid = false;
			// Check if the ticket is valid for a given field and break if so
			for (int j = 0; j < fields.size(); j++){
				if ( (ticket[i] >= fields[j].start1 && ticket[i] <= fields[j].end1) || (ticket[i] >= fields[j].start2 && ticket[i] <= fields[j].end2)){
					valid = true;
					break;
				}
			}
			// Return which field was invalid if any
			if (!valid)
				return ticket[i];
		}
		// Return -1 if the ticket was valid
		return -1;
	}

	// Counts all valid nearby tickets and removes ones that are invalid from the ticket list
	int countValidNearbyTickets(){
		int validCount = 0;
		for (int i = 0; i < tickets.size(); i++){
			int val = checkTicket(tickets[i]);
			if (val >= 0){
				validCount += val;
				tickets.erase(tickets.begin()+i);
				i--;
			}
		}
		
		return validCount;
	}

	// Checks if a field is possible for a given colomn of all tickets
	bool isFieldPossible(int ticketCol, int field){
		for (int i = 0; i < tickets.size(); i++){
			if ( (tickets[i][ticketCol] < fields[field].start1) || ( (tickets[i][ticketCol] > fields[field].end1) && (tickets[i][ticketCol] < fields[field].start2) ) || (tickets[i][ticketCol] > fields[field].end2) )
				return false;
		}
		return true;
	}

	// Maps every column of ticket values to fields they could possibly be
	void mapPossibleFields(){
		possibleFields.resize(fields.size());
		for (int ticketCol = 0; ticketCol < fields.size(); ticketCol++){
			for (int field = 0; field < fields.size(); field++){
				if (isFieldPossible(ticketCol,field)){
					possibleFields[ticketCol].insert(field);
				}
			}
		}
	}

	// Removes a field from all sets except the passed exception
	void removeFieldFromSets(int field, int exception){
		for (int i = 0; i < fields.size(); i++){
			if (i != exception){
				possibleFields[i].erase(field);
			}
		}
	}

	long findMyTicketValue(){
		vector<int> processed(fields.size());
		// First map all the possible fields
		mapPossibleFields();
		// Then narrow down each possibleField to one field
		for (int i = 0; i < fields.size(); i++){
			// Find the set with size 1 that hasn't been processed
			for (int j = 0; j < possibleFields.size(); j++){
				if (possibleFields[j].size() == 1 && !processed[j]){
					// Remove this field from every other possibleFields set and set the current possibleField as processed
					removeFieldFromSets(*possibleFields[j].begin(), j);
					processed[j] = true;
					break;
				}
			}
		}

		// Get all the departure fields
		vector<int> departureFields;
		for (int i = 0; i < possibleFields.size(); i++)
			if (*possibleFields[i].begin() < 6)
				departureFields.push_back(i);
		
		// Finally, multiply all the departure fields together to get our ticket value
		long ticketVal = 1;
		for (int i = 0; i < departureFields.size(); i++){
			ticketVal *= myTicket[departureFields[i]];
		}

		return ticketVal;
	}
};



int main(){
	// Create the tickets object
	tickets allTickets;
	allTickets.loadTicketInfo("input16.txt");

	// Output the results
	cout << "Part 1: " << allTickets.countValidNearbyTickets() << endl;
	cout << "Part 2: " << allTickets.findMyTicketValue() << endl;
	return 0;
}
