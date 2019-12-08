#include <iostream>

int cookieCount(int n, int p, int c) {
	int eaten = n / p, jars = eaten;
	while (jars >= c) {
		int d = jars / c, m = jars % c;
		eaten += d;
		jars = m + d;
	}
	return eaten;
}

int main() {
	std::cout << cookieCount(15, 3, 2) << std::endl;
	std::cout << cookieCount(10, 2, 5) << std::endl;
	std::cout << cookieCount(12, 4, 4) << std::endl;
}
