#include <iostream>

class after_and_befor {
public:
	after_and_befor() { std::cout << "**********start test**********\n"; }
	~after_and_befor() { std::cout << "**********no error**********\n"; }
};

after_and_befor aab;

//#include "VectorTest.h"	//test is ok
//#include "ListTest.h"	//test is ok
//#include "DequeTest.h"//��ʵ�ֹ��ܿ���ȷ���У����ᷢ���ظ���������δ�����ֻ�ܽ�DequeTest.h����
//�ƶ���MAIN������

signed main() {
	//MySTL::DequeTest::testAllCases();
}