#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main() {

	std::ifstream input{ "in.txt" };
	std::vector<std::string> lines{};
	for (std::string s; std::getline(input, s); lines.push_back(s));

	return 0;
}