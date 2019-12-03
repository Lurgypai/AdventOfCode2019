#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <sstream>
#include <algorithm>
#include <cstdint>

struct point {
	int x;
	int y;
};

void printPoint(point p) {
	//std::cout << p.x << ", " << p.y << '\n';
}

std::vector<std::vector<uint32_t>> getPoints(const std::vector<std::string> & lines) {
	int size = 21800;
	std::vector<std::vector<uint32_t>> points = std::vector<std::vector<uint32_t>>(size, std::vector<uint32_t>(size, 0));

	std::cout << "map constructed\n";

	int offset = points.size() / 2;

	point pos = { 0, 0 };
	int steps = 0;
	for (auto& line : lines) {
		char dir = line[0];
		int dist = stoi(line.substr(1, line.size() - 1));

		switch (dir) {
		case 'U':
			for (int i = 1; i != dist + 1; ++i) {
				++steps;
				points[pos.x + offset][pos.y + i + offset] = steps;
			}
			pos.y += dist;
			break;
		case 'D':
			for (int i = 1; i != dist + 1; ++i) {
				++steps;
				points[pos.x + offset][pos.y - i + offset] = steps;
			}
			pos.y -= dist;
			break;
		case 'L':
			for (int i = 1; i != dist + 1; ++i) {
				++steps;
				points[pos.x - i + offset][pos.y + offset] = steps;
			}
			pos.x -= dist;
			break;
		case 'R':
			for (int i = 1; i != dist + 1; ++i) {
				++steps;
				points[pos.x + i + offset][pos.y + offset] = steps;
			}
			pos.x += dist;
			break;
		}
	}

	return points;
}

int findDistance(std::vector<std::vector<uint32_t>>& points, const std::vector<std::string> lines) {

	std::vector<int> overlaps{};
	std::vector<int> stepCounts{};

	int offset = points.size() / 2;

	point pos = { 0, 0 };

	int steps = 0;
	for (auto& line : lines) {
		char dir = line[0];
		int dist = stoi(line.substr(1, line.size() - 1));

		switch (dir) {
		case 'U':
			for (int i = 1; i != dist + 1; ++i) {
				++steps;
				if (points[pos.x + offset][pos.y + i + offset]) {
					overlaps.push_back(std::abs(pos.x) + std::abs(pos.y + i));
					stepCounts.push_back(steps + points[pos.x + offset][pos.y + i + offset]);
				}
			}
			pos.y += dist;
			break;
		case 'D':
			for (int i = 1; i != dist + 1; ++i) {
				++steps;
				if (points[pos.x + offset][pos.y - i + offset]) {
					overlaps.push_back(std::abs(pos.x) + std::abs(pos.y - i));
					stepCounts.push_back(steps + points[pos.x + offset][pos.y - i + offset]);
				}
			}
			pos.y -= dist;
			break;
		case 'L':
			for (int i = 1; i != dist + 1; ++i) {
				++steps;
				if (points[pos.x - i + offset][pos.y + offset]) {
					overlaps.push_back(std::abs(pos.x - i) + std::abs(pos.y));
					stepCounts.push_back(steps + points[pos.x - i + offset][pos.y + offset]);
				}
			}
			pos.x -= dist;
			break;
		case 'R':
			for (int i = 1; i != dist + 1; ++i) {
				++steps;
				if (points[pos.x + i + offset][pos.y + offset]) {
					overlaps.push_back(std::abs(pos.x + i) + std::abs(pos.y));
					stepCounts.push_back(steps + points[pos.x + i + offset][pos.y + offset]);
				}
			}
			pos.x += dist;
			break;
		}
	}

	std::sort(overlaps.begin(), overlaps.end());
	std::cout << "sorted overlaps\n";


	std::sort(stepCounts.begin(), stepCounts.end());
	std::cout << "sorted steps\n";
	return stepCounts[0];
}

bool sortedContains(std::vector<point> sorted, point p, int bottom, int top) {

	if (top - bottom <= 1)
		return false;

	int pos = (top - bottom) / 2;

	if (p.x < sorted[pos].x) {
		return sortedContains(sorted, p, bottom, pos);
	}
	else if (p.x > sorted[pos].y) {
		return sortedContains(sorted, p, pos, top);
	}
	else if (p.x == sorted[pos].x) {
		if (p.y < sorted[pos].y) {
			return sortedContains(sorted, p, bottom, pos);
		}
		else if (p.y > sorted[pos].y) {
			return sortedContains(sorted, p, pos, top);
		}
		else if (p.x == p.y) {
			return true;
		}
	}
}

int main() {

	std::ifstream input{ "in.txt" };
	std::string first{};
	std::string second{};
	input >> first;
	input >> second;

	std::stringstream s1{first};
	std::stringstream s2{ second };

	std::vector<std::string> lines1{};
	for (std::string s; std::getline(s1, s, ','); lines1.push_back(s));

	std::vector<std::string> lines2{};
	for (std::string s; std::getline(s2, s, ','); lines2.push_back(s));

	std::vector<std::vector<uint32_t>> firstCrossed = getPoints(lines1);

	std::cout << "map filled...\n";

	int minDistance = findDistance(firstCrossed, lines2);

	std::cout << minDistance << '\n';

	return 0;
}