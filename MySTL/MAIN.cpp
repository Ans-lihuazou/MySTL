#include <iostream>

class after_and_befor {
public:
	after_and_befor() { std::cout << "**********start test**********\n"; }
	~after_and_befor() { std::cout << "\n**********no error**********\n"; }
};

after_and_befor aab;

//#include "VectorTest.h"	//test is ok
//#include "ListTest.h"	//test is ok
//#include "DequeTest.h"//��ʵ�ֹ��ܿ���ȷ���У����ᷢ���ظ���������δ�����ֻ�ܽ�DequeTest.h����
//�ƶ���MAIN������
//#include "StackTest.h" //test is ok
//#include "QueueTest.h" //test is ok
//#include "Priority_QueueTest.h" //test is ok

//  /FORCE:MULTIPLE:�����Ƿ��ظ�����


signed main() {
	//MySTL::Priority_QueueTest::testAllCases();
}