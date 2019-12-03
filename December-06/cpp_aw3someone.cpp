#include <iostream>
#include <vector>

std::vector<int> fibonacci_prime(int n) {
	std::vector<int> fibsequence = { 0, 1 };
	std::vector<bool> primes = { false, false };
	std::vector<int> fib_primes;
	size_t f = 1, p = 1;
	while (1) {
		int fib = fibsequence[f];
		// check to see if we know if it's prime or not
		if (fib > p) {
			// we need to determine if fib is prime
			primes.resize(fib + 1, true);
			for (size_t i = 2; i <= fib; i++) {
				if (primes[i])
					for (size_t j = 2;; j++) {
						int composite = j * i;
						if (composite > fib) break;
						primes[composite] = false;
					}
				p = i;
			}
		}
		if (primes[fib]) fib_primes.push_back(fib);
		if (fib_primes.size() >= n) return fib_primes;
		if (++f >= fibsequence.size()) fibsequence.push_back(fibsequence[f - 1] + fibsequence[f - 2]);
	}
}

int main() {
	auto v = fibonacci_prime(5);
	for (auto x : v)
		std::cout << x << std::endl;
}
