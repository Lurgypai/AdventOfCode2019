#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main() {

	std::ifstream input{ "in.txt" };
	std::vector<std::string> lines{};
	for (std::string s; std::getline(input, s); lines.push_back(s));

	int min = 183564;
	int max = 657474;

	std::vector<std::string> doubleDigits = { "00", "11", "22", "33", "44", "55", "66", "77", "88", "99" };
	std::vector<std::string> tripleDigits = { "000", "111", "222", "333", "444", "555", "666", "777", "888", "999" };

	std::vector<std::string> possibles;
	possibles.reserve(max - min + 1);

	for (int i = min; i != max + 1; ++i) {
		possibles.push_back(std::to_string(i));
	}

	std::cout << "all possibles found\n";

	possibles.erase(std::remove_if(possibles.begin(), possibles.end(), [&](const std::string & possible) {
		for (int i = 0; i != doubleDigits.size(); ++i) {
			auto& doubleDigit = doubleDigits[i];
			auto& tripleDigit = tripleDigits[i];
			if (possible.find(doubleDigit) != std::string::npos && possible.find(tripleDigit) == std::string::npos)
				return !std::is_sorted(possible.begin(), possible.end(), [](const char a, const char b) {return a < b; });
		}
		return true;
		}), possibles.end());

	return 0;
}