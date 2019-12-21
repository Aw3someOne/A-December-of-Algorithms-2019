#include <algorithm>
#include <iostream>
#include <vector>

int brute_force(int n) {
	std::vector<bool> v;
	v.resize(n, false);
	for (size_t i = 1; i <= v.size(); i++) {
		for (size_t j = i - 1; j < v.size(); j += i)
			v[j] = !v[j];
	}
	return std::count(v.begin(), v.end(), true);
}

int constant_time(int n) {
	return floor(sqrt(n));
}

std::vector<int> optional(int n) {
	std::vector<int> v;
	int c = constant_time(n);
	for (size_t i = 1; i <= c; i++)
		v.push_back(i * i);
	return v;
}

int main() {
	int n;
	std::cout << "Enter no of switches: ";
	if (!(std::cin >> n)) return 1;
	std::cout << "No of switches in the 'on' state at the end: " << brute_force(n) << std::endl;
	std::cout << "No of switches in the 'on' state at the end: " << constant_time(n) << std::endl;
	std::cout << "The switches that are on the on position are: " << std::endl;
	for (auto x : optional(n))
		std::cout << x << std::endl;
}
