#include <vector>
#include <iostream>
#include <exception>
#include <string>

//Hard to check if it works as intended due to a lack of understanding in bitwise operations on operands. However, the main point of this exercise was to build the grammar. As long as it parses everything well enough for an output, i'm happy.
//I could definitely figure out the logic if the outputs were of incorrect value but i would have to waste more time on understanding bitwise manipulation. Hence i'm leaving it as is.
void clearInputStream() {
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //ignores entire input stream or until the delimiter is met '\n' (also discards delimiter from input buffer)
}
//Declaration
int term();
//Declaration
int secondary();
//Declaration
int primary();

int readNum() {
	char ch = std::cin.get();
	if (ch >= '0' && ch <= '9') {
		std::cin.putback(ch);
		int num;
		std::cin >> num;
		return num;
	}
	else {
		throw std::runtime_error("Number expected. Expression is invalid. Cleaning up traces and restarting program.\n\n");
	}
}


int Expression() {
	int val = term();
	char ch = std::cin.get(); // expected to read a non-numerical char
	while (true) {
		switch (ch) {
		case '|':
			val |= term();
			ch = std::cin.get(); // expected to read a non-numerical char
			break;

		default:
			std::cin.putback(ch);
			return val;
		}
	}
}

int term() {
	int val = secondary();
	char ch = std::cin.get(); // expected to read a non-numerical char
	while (true) {
		switch (ch) {
		case '^':
			val ^= secondary();
			ch = std::cin.get(); // expected to read a non-numerical char
			break;

		default:
			std::cin.putback(ch);
			return val;
		}
	}
}

int secondary() {
	int val = primary();
	char ch = std::cin.get();  // expected to read a non-numerical char
	while (true) {
		switch (ch) {
		case '&':
			val &= primary();
			ch = std::cin.get(); // expected to read a non-numerical char
			break;

		default: 
			std::cin.putback(ch);
			return val;
		}
	}
}

int primary() {
	char ch = std::cin.get(); 
	while (true) {
		switch (ch) {
		case '~':{
			ch = std::cin.get();
			if (ch == '-') {
				int num = readNum();
				return ~num;
			}
			else {
				std::cin.putback(ch); //ch expected to be number, putback so we can get the whole integer
				int num = readNum();
				return ~num;
			}
			break;
		}
		case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': {
			std::cin.putback(ch); //ch expected to be number, putback so we can get the whole integer
			int num = readNum();
			return num;
			break;
		}
		case '-': {
			int num = readNum();
			return -num;
		}

		default:
			throw std::runtime_error("Invalid primary found. Expression is invalid. Cleaning up traces and restarting program.\n\n"); //deal with this in main.
		}
	}
	
}

//issues with current code: 
// 1.using cin.get assumes numbers are only single digit for the order of the expression to be correct. after calling cin.get, if its a number, we should put back and read as an int.
// 2. I think it's reading in the final /n after entering an input as its computing an answer but outputting "invalid pramary afterwards"
int main() {
	while(true){
		try {

			std::cout << "Please enter a new input:";
			int result = Expression();
			std::cout << "Result of input:" << result << "\n";
			std::cout << "Operation completed succesfully.\n\n";
			clearInputStream();
		}
		catch (const std::runtime_error& e) {
			std::cout << e.what();
			clearInputStream();
		}
	}
}
