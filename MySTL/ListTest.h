#pragma once

#ifndef _LISTTEST_H_
#define _LISTTEST_H_

#include "TestUtil.h"
#include <list>
#include "List.h"



#include <cassert>
#include <functional>
#include <string>
#include <random>

namespace MySTL {
	namespace ListTest {
		template<class T>
		using stdL = std::list < T >;
		template<class T>
		using tsL = MySTL::list < T >;

		void testCase1();
		void testCase2();
		void testCase3();
		void testCase4();
		void testCase5();
		void testCase6();
		void testCase7();
		void testCase8();
		void testCase9();
		void testCase10();
		void testCase11();
		void testCase12();
		void testCase13();
		void testCase14();
		void testCase15();

		void testAllCases();

		void testCase1() {
			stdL<int> l1(10, 0);
			tsL<int> l2(10, 0);
			assert(MySTL::Test::container_equal(l1, l2));

			int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
			stdL<int> l3(std::begin(arr), std::end(arr));
			tsL<int> l4(std::begin(arr), std::end(arr));
			assert(MySTL::Test::container_equal(l3, l4));

			auto l5(l1);
			auto l6(l2);
			assert(MySTL::Test::container_equal(l5, l6));

			auto l7 = l1;
			auto l8 = l2;
			assert(MySTL::Test::container_equal(l7, l8));
		}
		void testCase2() {
			tsL<std::string> l1;
			assert(l1.empty());
			assert(l1.size() == 0);

			std::string arr[] = { "1", "2", "3" };
			tsL<std::string> l2(std::begin(arr), std::end(arr));
			assert(!l2.empty());
			assert(l2.size() == 3);
		}
		void testCase3() {
			std::string arr[] = { "1", "2", "3" };
			tsL<std::string> l(std::begin(arr), std::end(arr));
			assert(l.back() == arr[2]);
			assert(l.front() == arr[0]);

			l.front() = "front";
			l.back() = "back";
			assert(l.back() == "back");
			assert(l.front() == "front");
		}
		void testCase4() {
			stdL<int> l1;
			tsL<int> l2;
			for (auto i = 0; i != 10; ++i) {
				l1.push_front(i);
				l2.push_front(i);
			}
			assert(MySTL::Test::container_equal(l1, l2));
			for (auto i = 0; i != 10; ++i) {
				l1.push_back(i);
				l2.push_back(i);
			}
			assert(MySTL::Test::container_equal(l1, l2));
			for (auto i = 0; i != 5; ++i) {
				l1.pop_back();
				l2.pop_back();
			}
			assert(MySTL::Test::container_equal(l1, l2));
			for (auto i = 0; i != 5; ++i) {
				l1.pop_front();
				l2.pop_front();
			}
			assert(MySTL::Test::container_equal(l1, l2));
		}
		void testCase5() {
			stdL<int> l1;
			tsL<int> l2;

			for (auto i = 0; i != 10; ++i) {
				l1.push_back(i);
				l2.push_back(i);
			}
			auto rit1 = l1.rbegin();
			auto rit2 = l2.rbegin();
			auto temp = l2.rend();
			for (; rit1 != l1.rend() && rit2 != l2.rend(); ++rit1, ++rit2) {
				//std::cout << *rit1 << " " << *rit2 << std::endl;
				assert(*rit1 == *rit2);
			}
			//std::cout << *rit2 << std::endl;
			//auto first1 = l1.begin();
			//auto first2 = l2.begin();
			//
			//for (; first1 != l1.end() && first2 != l2.end(); ++first1, ++first2) {
			//	std::cout << *first1 << " " << *first2 << std::endl;
			//}
			//if (rit1 != l1.rend()) std::cout << "error 1\n";//true
			//if (l2.begin() == l2.end()) std::cout << "error 2\n";//fasle
			//if(l2.rbegin()==l2.rend()) std::cout << "error 3\n";//false
			//if (rit2 != l2.rend()) std::cout << "error 4\n";//false
			assert(rit1 == l1.rend() && rit2 == l2.rend());
		}
		void testCase6() {
			stdL<int> l1;
			tsL<int> l2;

			l1.insert(l1.end(), 10, -1);
			l2.insert(l2.end(), 10, -1);
			assert(MySTL::Test::container_equal(l1, l2));

			auto it1 = l1.begin();
			auto it2 = l2.begin();
			for (auto i = l1.size() / 2 + 1; i != 0; --i) {
				++it1;
				++it2;
			}
			l1.insert(it1, 1);
			l2.insert(it2, 1);
			assert(MySTL::Test::container_equal(l1, l2));

			int arr[] = { 1, 2, 3, 4, 5 };
			it1 = l1.end();
			it2 = l2.end();
			l1.insert(it1, std::begin(arr), std::end(arr));
			l2.insert(it2, std::begin(arr), std::end(arr));
			assert(MySTL::Test::container_equal(l1, l2));
		}
		void testCase7() {
			stdL<int> l1;
			tsL<int> l2;
			for (auto i = 0; i != 100; ++i) {
				l1.push_back(i);
				l2.push_back(i);
			}

			l1.erase(l1.begin()); l1.erase(--l1.end());
			l2.erase(l2.begin()); l2.erase(--l2.end());
			//std::cout << "assert1: " << l1.size() << " " << l2.size() << std::endl;
			assert(MySTL::Test::container_equal(l1, l2));
			
			l1.erase(l1.begin(), l1.end());
			l2.erase(l2.begin(), l2.end());
			//std::cout << "assert2: " << l1.size() << " " << l2.size() << std::endl;
			assert(MySTL::Test::container_equal(l1, l2));
		}
		void testCase8() {
			tsL<int> l1, l2;
			l1.push_back(1); l1.push_back(1); l1.push_back(1);
			l2.push_back(2); l2.push_back(2);

			l1.swap(l2);
			assert(l1.size() == 2 && l2.size() == 3);
			//std::cout << "assert1 is ok\n";
			MySTL::swap(l1, l2);
			assert(l1.size() == 3 && l2.size() == 2);
			//std::cout << "assert2 is ok\n";
		}
		void testCase9() {
			std::random_device rd;
			stdL<int> l1;
			tsL<int> l2;
			for (auto i = 0; i != 100; ++i) {
				auto ret = rd() % 65536;
				l1.push_back(ret);
				l2.push_back(ret);
			}
			l1.sort();
			l2.sort();
			assert(MySTL::Test::container_equal(l1, l2));
			//std::cout << "assert1 is ok\n";
			l1.sort(std::greater<int>());
			l2.sort(std::greater<int>());
			assert(MySTL::Test::container_equal(l1, l2));
			//std::cout << " assert2 is ok\n";
		}
		void testCase10() {
			int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
			stdL<int> l1(std::begin(arr), std::end(arr));
			tsL<int> l2(std::begin(arr), std::end(arr));
			l1.reverse();
			l2.reverse();
			assert(MySTL::Test::container_equal(l1, l2));
		}
		void testCase11() {
			int arr1[] = { 0, 1, 3, 5, 9 }, arr2[] = { 2, 4, 6, 7, 8 };
			stdL<double> first1(std::begin(arr1), std::end(arr1)), second1(std::begin(arr2), std::end(arr2));
			tsL<double> first2(std::begin(arr1), std::end(arr1)), second2(std::begin(arr2), std::end(arr2));

			first1.merge(second1);
			first2.merge(second2);
			assert(MySTL::Test::container_equal(first1, first2));
		}
		void testCase12() {
			int arr[] = { 0, 0, 1, 2, 2, 3, 3, 4, 4, 4, 5, 5, 6, 7, 8, 8, 9, 11 };
			stdL<int> l1(std::begin(arr), std::end(arr));
			tsL<int> l2(std::begin(arr), std::end(arr));
			
			l1.unique();
			l2.unique();
			
			assert(MySTL::Test::container_equal(l1, l2));
		}
		void testCase13() {
			int arr[] = { 17, 89, 7, 14, 89, 0, 1, 4 };
			stdL<int> l1(std::begin(arr), std::end(arr));
			tsL<int> l2(std::begin(arr), std::end(arr));

			l1.remove(89);
			l2.remove(89);
			assert(MySTL::Test::container_equal(l1, l2));

			auto func = [](int n) {return n % 2 == 0; };
			l1.remove_if(func);
			l2.remove_if(func);
			assert(MySTL::Test::container_equal(l1, l2));
		}
		/*std::cout << "start error\n befor unique size: " << l1.size() << " " << l2.size() << "\n";
		auto iter1 = l1.begin();
		auto iter2 = l2.begin();
		int cnt = 0;
		for (; iter1 != l1.end() && iter2 != l2.end(); iter1++, iter2++) {
			std::cout << cnt++ << " " << *iter1 << " " << *iter2 << std::endl;
		}*/
		void testCase14() {
			stdL<int> l1(10, 0), l3(10, 1);
			tsL<int> l2(10, 0), l4(10, 1);

			l1.splice(l1.begin(), l3);
			l2.splice(l2.begin(), l4);
			assert(MySTL::Test::container_equal(l1, l2));
			//std::cout << "assert1 is ok\n";

			auto l5 = l1;
			auto l6 = l2;
			l1.splice(l1.end(), l5, l5.begin());
			l2.splice(l2.end(), l6, l6.begin());
			assert(MySTL::Test::container_equal(l1, l2));
			//std::cout << "assert1 is ok\n";

			auto it1 = l1.begin();
			auto it2 = l2.begin();
			for (auto i = 0; i != l1.size() / 2; ++i) {
				++it1;
				++it2;
			}
			l1.splice(it1, l5, l5.begin(), l5.end());
			l2.splice(it2, l6, l6.begin(), l6.end());
			assert(MySTL::Test::container_equal(l1, l2));
			//std::cout << "assert1 is ok\n";
		}
		void testCase15() {
			tsL<int> l1(10, 0), l2(10, 1), l3(10, 0);

			assert(l1 == l3);
			//std::cout << "assert1 is ok\n";
			assert(l1 != l2);
			//std::cout << "assert2 is ok\n";
		}


		void testAllCases() {
			int a[17];
			for (int i = 0; i < 17; i++) a[i] = i;
			int index = 1;
			std::cout << a[index++] << std::endl;
			testCase1();
			std::cout << a[index++] << std::endl;
			testCase2();
			std::cout << a[index++] << std::endl;
			testCase3();
			std::cout << a[index++] << std::endl;
			testCase4();
			std::cout << a[index++] << std::endl;
			testCase5();
			std::cout << a[index++] << std::endl;
			testCase6();
			std::cout << a[index++] << std::endl;
			testCase7();
			std::cout << a[index++] << std::endl;
			testCase8();
			std::cout << a[index++] << std::endl;
			testCase9();
			std::cout << a[index++] << std::endl;
			testCase10();
			std::cout << a[index++] << std::endl;
			testCase11();
			std::cout << a[index++] << std::endl;
			testCase12();
			std::cout << a[index++] << std::endl;
			testCase13();
			std::cout << a[index++] << std::endl;
			testCase14();
			std::cout << a[index++] << std::endl;
			testCase15();
		}
	}
}

#endif // !_LISTTEST_H_