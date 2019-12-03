#include <deque>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct Patient {
	int token;
	std::string id;
	Patient(int token, std::string id) : token(token), id(id) {}
};

std::ostream& operator<<(std::ostream& os, const Patient* p) {
	os << '(' << p->token << ", " << p->id << ')';
	return os;
}

class Queue {
	std::deque<Patient*> _d;
public:
	bool promote(std::string id) {
		for (auto it = _d.begin(); it != _d.end(); ++it) {
			if ((*it)->id == id) {
				Patient* tmp = *it;
				_d.erase(it, it + 1);
				_d.push_front(tmp);
				return true;
			}
		}
		return false;
	}
	void enqueue(Patient* p) {
		_d.push_back(p);
	}
	size_t size() const {
		return _d.size();
	}
	friend std::ostream& operator<<(std::ostream& os, const Queue& q);
};

std::ostream& operator<<(std::ostream& os, const Queue& q) {
	for (const auto p : q._d)
		os << p << std::endl;
	return os;
}

int main() {
	int N = 0;
	for (std::string line; std::cout << "Enter N: " && getline(std::cin, line);) {
		std::istringstream iss(line);
		if (iss >> N && N > 0) break;
	}
	std::cout << "Enter (token no, id):" << std::endl;
	Queue queue;
	for (std::string line; queue.size() < N && getline(std::cin, line);) {
		std::istringstream iss(line);
		char _;
		int token;
		std::string id;
		if (!(iss >> _ >> token >> _ >> id)) continue;
		if ((*id.rbegin()) != ')') continue;
		id.pop_back();
		queue.enqueue(new Patient(token, id));
	}
	std::cout << "Enter k: ";
	std::string k;
	std::cin >> k;
	queue.promote(k);

	std::cout << "The order is:" << std::endl;
	std::cout << queue << std::endl;
}
