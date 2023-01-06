#include <iostream>

class after_and_befor {
public:
	after_and_befor() { std::cout << "**********start test**********\n"; }
	~after_and_befor() { std::cout << "\n**********no error**********\n"; }
};

after_and_befor aab;

//#include "VectorTest.h"	//test is ok
//#include "ListTest.h"		//test is ok
//#include "DequeTest.h"	//test is ok
//#include "StackTest.h"	//test is ok
//#include "QueueTest.h"	//test is ok


int main() {
	//MySTL::DequeTest::testAllCases();
	return 0;
}