#include <iostream>
#include <string>
#include <vector>

//known issue: doing std::cin.get() twice works for everything aside from the nmoun func since we expect the first char to be a character and not whitespace, unlike the rest of the input.

constexpr int valid_nouns_count = 3;
constexpr int valid_verbs_count = 3;
constexpr int valid_conjuncs_count= 3;

std::vector<std::string> vec_noun = { "birds", "fish", "C++" };
std::vector<std::string> vec_verb = { "rules", "fly", "swim" };
std::vector<std::string> vec_conjuncs = { "and", "or", "but" };

void resetCinn() {
	std::cin.clear(); //reset cin if in error state so it can be used in the future
}

void clearInputStream() {
	std::cout << "Clearing input buffer. If in terminal, \"input:\" is not automatically called, enter any value to continue.\n" ;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //ignores entire input stream or until the delimiter is met '\n' (also discards delimiter from input buffer)
}

bool isNoun(std::string word) {
	for (auto it = vec_noun.begin(); it != vec_noun.end(); ++it) {
		if (word == *it) {
			return true;
		}
	}
	return false;
}



bool isVerb(std::string word) {

	for (auto it = vec_verb.begin(); it != vec_verb.end(); ++it) {
		if (word == *it) {
			return true;
		}
	}
	return false;
}

bool isConjunc(std::string word) {

	for (auto it = vec_conjuncs.begin(); it != vec_conjuncs.end(); ++it) {
		if (word == *it) {
			return true;
		}
	}
	return false;
}



bool isFullstop() {
	char ch = std::cin.get();
	if (ch == '.') {
		return true;
	}
	else {
		std::cin.putback(ch);
		return false;
	}
}

bool sentence();

bool conjunction() {
	char ch = std::cin.get();
	if (ch == ' ') {
		return false;
	}
	std::cin.putback(ch);
	std::string potential_conjunc;
	std::cin >> potential_conjunc;
	std::cin.get(); //consume whitespace after reading in string

	if (isConjunc(potential_conjunc)) {
		return sentence();
	}
	else {
		return false;
	}


}

//structure of sentence : noun verb 
//						: sentence conjunction sentence
bool sentence() {
	char ch;
	ch = std::cin.get();
	if (ch == ' ') {
		return false;
	}
	std::cin.putback(ch);
	std::string potential_noun;
	std::cin >> potential_noun; 
	if (!isNoun(potential_noun)) {
		return false;
	}
	std::cin.get(); //consume whitespace after reading in string
	ch = std::cin.get();
	if (ch == ' ') {
		return false;
	}
	std::cin.putback(ch);
	std::string potential_verb;
	std::cin >> potential_verb;
	if (!isVerb(potential_verb)) {
		return false;
	}
	ch = std::cin.get(); //consume whitespace after reading in string or \n depending on input.
	if (ch == '\n') {
		return false;
	}

	if (isFullstop()) {
		return true;
	}
	return conjunction();

}

//validate this works for a plethora of input.
int main() {

	while (true) {
		std::cout << "input:";
		bool result = sentence() << '\n';
		if (result) {
			std::cout << "OK" << '\n' << '\n';
		}
		else {
			std::cout << "Not OK" << '\n' << '\n';
		}
		//if stream is fully clear after sentence() is executed, calling this causes the program to wait for user input as it has nothing to ignore.
		clearInputStream();
	}
}

