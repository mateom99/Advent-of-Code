using namespace std;

#include <iostream>
#include <vector>
#include <fstream>
#include <deque>

class calculator{
	vector<deque<string>> equations;

	public:
	// Loads all the equations from the input file into a vector of deques
	void loadEquations(string file){
		// Instantinate the input file object and open the file
		ifstream inFile;
		inFile.open(file);
		// Get each line
		string line;
		while (getline(inFile, line)){
			// Create a deque for the current equation
			deque<string> currEquation;
			// Add every character to the deque that isn't a space (this works since all numbers in the input are one digit)
			for (int i = 0; i < line.size(); i++){
				if (line[i] == ' ')
					continue;
				string expr;
				expr += line[i];
				currEquation.push_back(expr);
			}
			// Add the current equation to the vector of equations
			equations.push_back(currEquation);
		}
		// Close the file
		inFile.close();
	}
	// Solves an equation from left to right with parenthesis overriding the order and returns the answer
	long solveEquation(deque<string> equation){
		// Continue until we have solved everything and are left with the answer in the deque
		while (equation.size() > 1){
			long operand1;
			long operand2;
			string op;
			// If a parenthesis isn't in front of the deque, we can directly get our first operand
			if (equation.front() != "("){
				operand1 = stol(equation.front());
				equation.pop_front();
			} else {
				// If we do hit a parenthesis however, store everything in between the parenthesis
				// in a new deque and recursively call solveEquation() to simplify it
				int bracketCount = 0;
				equation.pop_front();
				deque<string> newEquation;
				while(bracketCount > 0 || equation.front() != ")"){
					if (equation.front() == "(")
						bracketCount++;
					if (equation.front() == ")")
						bracketCount--;
					newEquation.push_back(equation.front());
					equation.pop_front();
				}
				equation.pop_front();
				// Operand 1 is now the answer to this solved equation
				operand1 = (solveEquation(newEquation));
			}
			// Next, we get the operator (+/*)
			op = equation.front();
			equation.pop_front();
			// We get the second operand exactly the same as the first
			if (equation.front() != "("){
				operand2 = stol(equation.front());
				equation.pop_front();
			} else {
				int bracketCount = 0;
				equation.pop_front();
				deque<string> newEquation;
				while(bracketCount > 0 || equation.front() != ")"){
					if (equation.front() == "(")
						bracketCount++;
					if (equation.front() == ")")
						bracketCount--;
					newEquation.push_back(equation.front());
					equation.pop_front();
				}
				equation.pop_front();
				operand2 = (solveEquation(newEquation));
			}
			// Now simply push to the front of the deque the result of the operands with respective operator
			if (op == "+")
				equation.push_front(to_string(operand1 + operand2));
			if (op == "*")
				equation.push_front(to_string(operand1 * operand2));
			
		}
		// Return the remaining element of the deque
		return stol(equation.front());
	}

	// Returns the sum of all the answers to all equations
	long sumEquations(){
		long sum = 0;
		for (int i = 0; i < equations.size(); i++)
			sum += solveEquation(equations[i]);
		
		return sum;
	}

	// Solves an equation with addition having higher precedence than
	// multiplication and parenthesis overriding the order and returns the answer
	long solveEquationAdvanced(deque<string> equation){
		deque<string> simplifiedEquation;
		// Continue until we have solved all addiiton and are left a simplified equation consisting of only multiplication
		while (equation.size() > 1){
			long operand1;
			long operand2;
			string op;
			// If a parenthesis isn't in front of the deque, we can directly get our first operand
			if (equation.front() != "("){
				operand1 = stol(equation.front());
				equation.pop_front();
			} else {
				// If we do hit a parenthesis however, store everything in between the parenthesis
				// in a new deque and recursively call solveEquation() to simplify it
				int bracketCount = 0;
				equation.pop_front();
				deque<string> newEquation;
				while(bracketCount > 0 || equation.front() != ")"){
					if (equation.front() == "(")
						bracketCount++;
					if (equation.front() == ")")
						bracketCount--;
					newEquation.push_back(equation.front());
					equation.pop_front();
				}
				equation.pop_front();
				// Operand 1 is now the answer to this solved equation
				operand1 = (solveEquationAdvanced(newEquation));
			}
			// Next, we get the operator (+/*)
			op = equation.front();
			equation.pop_front();
			// We get the second operand exactly the same as the first
			if (equation.front() != "("){
				operand2 = stol(equation.front());
				equation.pop_front();
			} else {
				int bracketCount = 0;
				equation.pop_front();
				deque<string> newEquation;
				while(bracketCount > 0 || equation.front() != ")"){
					if (equation.front() == "(")
						bracketCount++;
					if (equation.front() == ")")
						bracketCount--;
					newEquation.push_back(equation.front());
					equation.pop_front();
				}
				equation.pop_front();
				operand2 = (solveEquationAdvanced(newEquation));
			}
			// If the operation is addition, solve it as normal and push it to the front of the deque
			if (op == "+")
				equation.push_front(to_string(operand1 + operand2));
			// If the operation is multiplcation, add the second operand back to the front of the original deque
			// and add the first operand the the operator to the simplified equation to build up an equation
			// that consists of only multiplication
			if (op == "*"){
				equation.push_front(to_string(operand2));
				simplifiedEquation.push_back(to_string(operand1));
				simplifiedEquation.push_back(op);
			}
			
		}
		// Get the final operand from the equation into simplified equation
		string finalOperand = equation.front();
		simplifiedEquation.push_back(finalOperand);
		equation.pop_front();

		// Finally solve the remaining multiplication using our original solveEquation()
		return solveEquation(simplifiedEquation);
	}

	// Returns the sum of all the answers to all equations using advanced math
	long sumEquationsAdvanced(){
		long sum = 0;
		for (int i = 0; i < equations.size(); i++)
			sum += solveEquationAdvanced(equations[i]);
		
		return sum;
	}
};


int main(){
	// Create the calculator object and load the equations
	calculator calc;
	calc.loadEquations("input18.txt");

	// Output the results
	cout << "Part 1: " << calc.sumEquations() << endl; 
	cout << "Part 2: " << calc.sumEquationsAdvanced() << endl; 
	return 0;
}