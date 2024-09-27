#include "../../std_lib_facilities.h"
#include <string>

//known issue: doing std::cin.get() twice works for everything aside from the nmoun func since we expect the first char to be a character and not whitespace, unlike the rest of the input.

constexpr int valid_nouns_count = 3;
constexpr int valid_verbs_count = 3;
constexpr int valid_conjuncs_count= 3;

std::string arr_noun[valid_nouns_count] = { "birds", "fish", "C++" };
std::string arr_verb[valid_verbs_count] = { "rules", "fly", "swim" };
std::string arr_conjuncs[valid_conjuncs_count] = { "and", "or", "but" };

void resetCinn() {
	std::cin.clear(); //reset cin if in error state so it can be used in the future
}

void clearInputStream() {
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //ignores entire input stream or until the delimiter is met '\n' (also discards delimiter from input buffer)
}

bool isNoun(std::string word) {
	for (int i = 0; i < valid_nouns_count; i++) {
		if (word == arr_noun[i]) {
			return true;
		}
	}
	return false;
}


bool isVerb(std::string word) {

	for (int i = 0; i < valid_verbs_count; i++) {
		if (word == arr_verb[i]) {
			return true;
		}
	}
	return false;
}

bool isConjunc(std::string word) {

	for (int i = 0; i < valid_conjuncs_count; i++) {
		if (word == arr_conjuncs[i]) {
			return true;
		}
	}
	return false;
}



bool fullstop() {
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
	std::cin.get(); //consume whitespace after reading in word

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
	//should this next part be nested? Not sure yet.
	if (!isNoun(potential_noun)) {
		return false;
	}
	std::cin.get(); //consume whitespace after reading in word
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
	std::cin.get();//consume whitespace after reading in word
	if (fullstop()) {
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
		clearInputStream();
	}
}
