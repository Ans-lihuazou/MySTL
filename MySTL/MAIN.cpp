#include <iostream>
#include <cstdio>
#include <list>

class after_and_befor {
public:
	after_and_befor() { std::cout << "start\n"; }
	~after_and_befor() { std::cout << "no error\n"; }
};

after_and_befor aab;

#include <list>
signed main() {
	std::list<int> l(5, 1);
	std::list<int>::iterator iter = l.begin();
	for (; iter != l.end();) {
		iter = l.erase(iter);
	}
	std::cout << l.size() << std::endl;
	
}