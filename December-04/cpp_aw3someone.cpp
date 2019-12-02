#include <iostream>
#include <vector>

int h_index(const std::vector<int>& v) {
	for (size_t n = v.size(); n-- > 0; ) {
		int c = 0;
		for (auto x : v) {
			if (x >= n) c++;
			if (c == n) return n;
		}
	}
	return 0;
}

int main() {
	std::vector<std::vector<int>> vv = {
		{ 4, 3, 0, 1, 5 },
		{ 4, 5, 2, 0, 6, 4 },
	};
	for (const auto& v : vv)
		std::cout << h_index(v) << std::endl;
}
