#include <vector>

bool is_sorted(const std::vector<int>& v) {
	for (size_t i = 1; i < v.size(); i++)
		if (v[i] < v[i - 1])
			return false;
	return true;
}

void snap(std::vector<int>& v) {
	while (!is_sorted(v))
		v.resize(v.size() / 2);
}

int main() {
	std::vector<int> v = { 1, 2, 3, 4, 3 };
	snap(v);
}
