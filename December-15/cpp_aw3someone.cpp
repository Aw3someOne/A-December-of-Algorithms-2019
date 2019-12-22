#include <algorithm>
#include <iostream>
#include <vector>

void dfs(std::vector<char> permutation, size_t target_quantity, std::vector<std::vector<char>> &valid_permutations) {
	size_t a = count(permutation.begin(), permutation.end(), 'A');
	size_t b = count(permutation.begin(), permutation.end(), 'B');
	if (a == b && a == target_quantity) {
		valid_permutations.push_back(permutation);
		return;
	}
	if (a > target_quantity || b > a) return;
	auto add_a = permutation;
	auto add_b = permutation;
	add_a.push_back('A');
	add_b.push_back('B');
	dfs(add_a, target_quantity, valid_permutations);
	dfs(add_b, target_quantity, valid_permutations);
}

int main() {
	std::cout << "Quantity of A (in grams): ";
	size_t a;
	if (!(std::cin >> a)) return 1;

	std::vector<std::vector<char>> permutations;
	dfs({}, a, permutations);
	std::cout << "Permutations: ";
	for (auto v : permutations) {
		std::cout << '[';
		for (auto x : v)
			std::cout << x;
		std::cout << "],";
	}
	std::cout << std::endl;
}
