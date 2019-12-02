#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int doOpCode(int code, int arg0, int arg1) {
	switch (code) {
	case 1:
		return arg0 + arg1;
	case 2:
		return arg0 * arg1;
	}
}

std::vector<int> parseOpCode(std::vector<int> in, int noun, int verb) {
	in[1] = noun;
	in[2] = verb;

	bool exit = false;
	int pos = 0;
	while (!exit) {
		int opCode = in[pos];
		if (opCode == 99)
			break;
		int newVal = doOpCode(opCode, in[in[pos + 1]], in[in[pos + 2]]);
		in[in[pos + 3]] = newVal;
		pos += 4;
	}
	return in;
}

int main() {

	std::ifstream input{ "in.txt" };
	std::vector<std::string> lines{};
	for (std::string s; std::getline(input, s, ','); lines.push_back(s));
	
	std::vector<int> vals{};
	vals.reserve(lines.size());

	for (auto v : lines) {
		vals.push_back(std::stoi(v));
	}

	int target = 19690720;

	for (int i = 0; i != 100; ++i) {
		for (int j = 0; j != 99; ++j) {
			if (parseOpCode(vals, i, j)[0] == target) {
				std::cout << i * 100 + j << '\n';
				return 0;
			}
		}
	}



	return 0;
}