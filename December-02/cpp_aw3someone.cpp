#include <iostream>
#include <string>

bool validate_credit_card(std::string cc) {
	int s1 = 0;
	int s2 = 0;
	auto it = cc.rbegin();
	const auto end = cc.rend();
	while (1) {
		s1 += *it - '0';
		if (++it == end) break;
		int d = 2 * (*it - '0');
		s2 += d > 9 ? d / 10 + d % 10 : d;
		if (++it == end) break;
	}
	return !((s1 + s2) % 10);
}

int main() {
	std::cout << validate_credit_card("49927398716") << std::endl;
}
