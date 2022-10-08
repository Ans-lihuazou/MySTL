#include <iostream>

class after_and_befor {
public:
	after_and_befor() { std::cout << "**********start test**********\n"; }
	~after_and_befor() { std::cout << "\n**********no error**********\n"; }
};

after_and_befor aab;

//#include "VectorTest.h"	//test is ok
//#include "ListTest.h"	//test is ok
//#include "DequeTest.h"//已实现功能可正确运行，但会发生重复链接问题未解决，只能将DequeTest.h代码
//移动到MAIN中运行
//#include "StackTest.h" //test is ok
//#include "QueueTest.h" //test is ok
//#include "Priority_QueueTest.h" //test is ok

//  /FORCE:MULTIPLE:不管是否重复定义


signed main() {
	//MySTL::Priority_QueueTest::testAllCases();
}