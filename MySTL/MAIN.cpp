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

//  /FORCE:MULTIPLE:�����Ƿ��ظ�����

#include "Algorithm.h"
#include <algorithm>
signed main() {

	int arr[5] = { 5,4,3,2,1 };
	std::sort(arr, arr + 5, MySTL::less<int>());
	for (int i = 0; i < 5; i++) {
		std::cout << arr[i] << " ";
	}

}