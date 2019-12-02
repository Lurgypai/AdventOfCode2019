#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int calculateFuel(int m) {
	m = m / 3 - 2;
	return m <= 0 ? 0 : m + calculateFuel(m);
}

int main() {

	std::ifstream input{"in.txt"};
	std::vector<std::string> lines{};
	for (std::string s; std::getline(input, s); lines.push_back(s));

	int total{};
	for (auto& line : lines) {
		int f = std::stoi(line);
		total += calculateFuel(f);
	}

	std::cout << total << '\n';

	return 0;
}