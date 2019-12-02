#include <algorithm>
#include <iostream>
#include <vector>

// gross recursive function that finds the sums of powers of 7 choose k where k >= 2
std::vector<int> distribute_n(int n, std::vector<int>& v, std::vector<int>::iterator it) {
	if (it == v.end()) return {};
	std::vector<int> sums;
	for (; it != v.end(); ++it) {
		int sum = n + *it;
		sums.push_back(sum);
		auto rec = distribute_n(sum, v, it + 1);
		sums.insert(sums.end(), rec.begin(), rec.end());
	}
	return sums;
}

std::vector<int> calculate_sums(std::vector<int>& v) {
	std::vector<int> sums;
	for (auto it = v.begin(); it != v.end(); ++it) {
		auto temp = distribute_n(*it, v, it + 1);
		sums.insert(sums.end(), temp.begin(), temp.end());
	}
	return sums;
}

int sevenish_number(int n) {
	std::vector<int> powers_of_seven;
	// calculate all powers of 7 that won't put us in danger of overflowing
	// could use unsigned longs but w/e
	for (size_t i = 0; i <= 10; i++) {
		powers_of_seven.push_back(pow(7, i));
	}

	std::vector<int> sums_of_powers_of_seven = calculate_sums(powers_of_seven);
	std::vector<int> sevenish_numbers;
	sevenish_numbers.reserve(powers_of_seven.size() + sums_of_powers_of_seven.size());
	sevenish_numbers.insert(sevenish_numbers.end(), powers_of_seven.begin(), powers_of_seven.end());
	sevenish_numbers.insert(sevenish_numbers.end(), sums_of_powers_of_seven.begin(), sums_of_powers_of_seven.end());
	std::sort(sevenish_numbers.begin(), sevenish_numbers.end());

	return sevenish_numbers[n - 1];
}

int main() {
	int tests[] = { 1, 5, 10, 25 };
	for (auto t : tests) {
		std::cout << sevenish_number(t) << std::endl;
	}
}
