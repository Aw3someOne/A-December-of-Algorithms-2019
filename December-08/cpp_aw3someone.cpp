#include <iostream>
#include <sstream>
#include <string>
#include <vector>

constexpr auto FRONT = .3F;
constexpr auto BEHIND = .2F;
constexpr auto SIDE = .2F;
constexpr auto DIAGONAL = .025F;

int main() {
	std::cout << "Enter rows on each line, with columns separated by spaces EOF when done" << std::endl;
	std::vector<std::vector<std::string>> students;
	for (std::string line; getline(std::cin, line);) {
		std::istringstream iss(line);
		std::vector<std::string> row;
		std::string col;
		while (iss >> col)
			row.push_back(col);
		if (students.size() && students[0].size() != row.size())
			std::cout << "entered row doesn't match previous row's length, please try again" << std::endl;
		else
			students.push_back(row);
		if (iss >> std::ws && iss.get() == EOF) break;
	}

	std::vector<std::vector<float>> cheat;
	cheat.resize(students.size(), {});
	for (size_t r = 0; r < students.size(); r++) {
		cheat[r].resize(students[r].size(), 0);
		for (size_t c = 0; c < students[r].size(); c++) {
			std::string s = students[r][c];
			if (r > 0 && students[r - 1][c] == s)
				cheat[r][c] += SIDE;
			if (r < students.size() - 1 && students[r + 1][c] == s)
				cheat[r][c] += SIDE;
			if (c > 0 && students[r][c - 1] == s)
				cheat[r][c] += FRONT;
			if (c < students[r].size() - 1 && students[r][c + 1] == s)
				cheat[r][c] += BEHIND;
			if (r > 0 && c > 0 && students[r - 1][c - 1] == s)
				cheat[r][c] += DIAGONAL;
			if (r < students.size() - 1 && c > 0 && students[r + 1][c - 1] == s)
				cheat[r][c] += DIAGONAL;
			if (r > 0 && c < students[r].size() - 1 && students[r - 1][c + 1] == s)
				cheat[r][c] += DIAGONAL;
			if (r < students.size() - 1 && c < students[r].size() - 1 && students[r + 1][c + 1] == s)
				cheat[r][c] += DIAGONAL;
		}
	}
	for (const auto& row : cheat) {
		for (auto p : row)
			printf("%1.3f ", p);
		std::cout << std::endl;
	}
}
