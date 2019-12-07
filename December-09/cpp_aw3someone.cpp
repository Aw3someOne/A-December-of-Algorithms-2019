#include <iostream>
#include <set>
#include <sstream>
#include <vector>

void readset(std::vector<float>& v, std::istringstream& iss) {
	float t;
	if (iss.peek() == '{')
		iss.ignore();
	while (iss >> t >> std::ws) {
		v.push_back(t);
		if (iss.peek() == ',')
			iss.ignore();
	}
}

float fx(float x, char op, float k) {
	switch (op) {
	case '+': return x + k;
	case '-': return x - k;
	case '*': return x * k;
	case '/': return x / k;
	case '^': return pow(x, k);
	default: return x;
	}
}

int main() {
	std::vector<float> set1;
	std::vector<float> set2;
	std::string line;
	std::cout << "Set 1: ";
	getline(std::cin, line);
	std::istringstream iss(line);
	readset(set1, iss);
	std::cout << "Set 2: ";
	getline(std::cin, line);
	iss = std::istringstream(line);
	readset(set2, iss);
	std::cout << "Function: ";

	char x, op;
	float n;
	std::set<float> outputs;
	if (set2.size() > set1.size())
		goto notonetoone;

	if (!(std::cin >> x >> std::ws >> op >> n))
		return 1;

	for (auto x : set1) {
		float y = fx(x, op, n);
		if (outputs.find(y) != outputs.end())
			goto notonetoone;
		outputs.insert(y);
	}

	std::cout << "Result: It is one to one" << std::endl;
	return 0;

notonetoone:
	std::cout << "Result: It is not one to one" << std::endl;
}
