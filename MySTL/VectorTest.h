#pragma once

//#ifndef _VECTOR_TEST_H_
//#define _VECTOR_TEST_H_

#include <vector>

#include "Vector.h"
#include "TestUtil.h"


#include <array>
#include <cassert>

#include<iostream>
#include <iterator>
#include <string>


namespace MySTL {
	namespace VectorTest {
		template<class T>
		using stdVec = std::vector < T >;

		template<class T>
		using tsVec = MySTL::vector < T >;

		void testCase1() {
			stdVec<std::string> v1(10, "zxh");
			tsVec<std::string> v2(10, "zxh");
			assert(MySTL::Test::container_equal(v1, v2));
			stdVec<std::string> v3(10);
			tsVec<std::string> v4(10);
			assert(MySTL::Test::container_equal(v3, v4));
			std::array<std::string, 3> arr = { "abc", "def", "ghi" };
			stdVec<std::string> v5(std::begin(arr), std::end(arr));
			tsVec<std::string> v6(std::begin(arr), std::end(arr));
			assert(MySTL::Test::container_equal(v5, v6));
		}

		void testCase2() {
			stdVec<int> temp1(10, 0);
			tsVec<int> temp2(10, 0);

			auto v1(temp1);
			auto v2(temp2);
			assert(MySTL::Test::container_equal(v1, v2));

			auto v3(std::move(temp1));
			auto v4(std::move(temp2));
			assert(MySTL::Test::container_equal(v3, v4));

			auto v5 = v1;
			auto v6 = v2;
			assert(MySTL::Test::container_equal(v5, v6));

			auto v7 = std::move(v3);
			auto v8 = std::move(v4);
			assert(MySTL::Test::container_equal(v7, v8));
		}

		void testCase3() {
			tsVec<double> v1, v2;
			for (int i = 0; i != 100; ++i) {//malloc ß∞‹
				v1.push_back(i);
				v2.push_back(i);	
			}
			assert(v1 == v2);
			assert(!(v1 != v2));
		}

		void testCase4() {
			tsVec<int> myvector;
			for (int i = 1; i <= 5; i++) myvector.push_back(i);

			auto i = 1;
			for (tsVec<int>::iterator it = myvector.begin(); it != myvector.end(); ++it, ++i) {
				assert(*it == i);
			}

			i = 1;
			for (tsVec<int>::const_iterator it = myvector.cbegin(); it != myvector.cend(); ++it, ++i) {
				assert(*it == i);
			}
		}
		void testCase5() {
			tsVec<int> myvector(5);  // 5 default-constructed ints
			int i = 0;
			tsVec<int>::reverse rit = myvector.rbegin();
			for (; rit != myvector.rend(); ++rit)
				*rit = ++i;

			i = 5;
			for (tsVec<int>::iterator it = myvector.begin(); it != myvector.end(); ++it, --i) {
				assert(*it == i);
			}

			i = 1;
			for (tsVec<int>::reverse it = myvector.rbegin(); it != myvector.rend(); ++it, ++i) {
				assert(*it == i);
			}
		}//ok
		void testCase6() {
			tsVec<int> v(11, 0);
			assert(v.size() == 11);

			v.resize(5);
			assert(v.size() == 5);

			v.resize(20);
			assert(v.size() == 20);
		}//ok
		void testCase7() {
			tsVec<int> v;
			v.reserve(20);
			assert(v.capacity() == 20);
		}
		void testCase8() {
			stdVec<int> v1(10);
			tsVec<int> v2(10);
			for (unsigned i = 0; i < 10; i++) {
				v1[i] = i;
				v2[i] = i;
			}
			assert(MySTL::Test::container_equal(v1, v2));

			v1.front() = 99;
			v2.front() = 99;
			v1.back() = 100;
			v2.back() = 100;

			assert(MySTL::Test::container_equal(v1, v2));
		}//ok
		void testCase9() {
			stdVec<int> v1(5);
			tsVec<int> v2(5);

			auto p1 = v1.data();
			auto p2 = v2.data();
			*p1 = 10; ++p1; *p1 = 20; p1[2] = 100;
			*p2 = 10; ++p2; *p2 = 20; p2[2] = 100;

			assert(MySTL::Test::container_equal(v1, v2));
		}//ok
		void testCase10() {
			tsVec<int> foo(3, 100);   // three ints with a value of 100
			tsVec<int> bar(2, 200);   // five ints with a value of 200
			//assert(true);
			std::vector<int> asv1{ 100,100,100 };
			std::vector<int> asv2{ 200,200 };

			//bool as1 = MySTL::Test::container_equal
			//(foo, asv1);
			assert(MySTL::Test::container_equal(foo, asv1));
			assert(MySTL::Test::container_equal(bar, asv2));

			foo.swap(bar);
			assert(MySTL::Test::container_equal(bar, asv1));
			assert(MySTL::Test::container_equal(foo, asv2));
		}
		void testCase11() {
			stdVec<std::string> v1;
			tsVec<std::string> v2;

			v1.push_back("hello "); v1.push_back("world");
			v2.push_back("hello "); v2.push_back("world");
			assert(MySTL::Test::container_equal(v1, v2));
			
			v1.pop_back();
			v2.pop_back();
			//std::cout << "OK\n";
			assert(MySTL::Test::container_equal(v1, v2));
		}
		void testCase12() {
			stdVec<int> v1;
			tsVec<int> v2;

			v1.insert(v1.begin(), 0);
			v2.insert(v2.begin(), 0);
			assert(MySTL::Test::container_equal(v1, v2));

			v1.insert(v1.end(), 1);
			v2.insert(v2.end(), 1);
			assert(MySTL::Test::container_equal(v1, v2));

			v1.insert(v1.begin() + v1.size() / 2, 10, 0);
			v2.insert(v2.begin() + v2.size() / 2, 10, 0);
			assert(MySTL::Test::container_equal(v1, v2));

			int arr[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
			v1.insert(v1.end(), std::begin(arr), std::end(arr));
			v2.insert(v2.end(), std::begin(arr), std::end(arr));
			assert(MySTL::Test::container_equal(v1, v2));
		}
		void testCase13() {
			stdVec<int> v1;
			tsVec<int> v2;
			for (int i = 1; i <= 10; i++) {
				v1.push_back(i);
				v2.push_back(i);
			}
			v1.erase(v1.begin() + 5);
			v2.erase(v2.begin() + 5);
			assert(MySTL::Test::container_equal(v1, v2));

			v1.erase(v1.begin(), v1.begin() + 3);
			v2.erase(v2.begin(), v2.begin() + 3);
			assert(MySTL::Test::container_equal(v1, v2));
		}
		void testCase14() {
			tsVec<int> foo(3, 100);
			tsVec<int> bar(2, 200);

			assert(!(foo == bar));
			assert(foo != bar);
		}

		class TestItem{
		public:
			TestItem(){
				//std::cout << "testItem\n";
				++count;
			}
			TestItem(const TestItem& other){
				//std::cout << "testItem\n";
				++count;
			}

			virtual ~TestItem(){
				//std::cout << "destor TestItem\n";
				--count;
			}

			static int getCount(){
				return count;
			}
		private:
			static int count;
		};
		int TestItem::count = 0;

		void testCase15(){
			//std::cout << "test\n";
			assert(TestItem::getCount() == 0);
			{
				
				typedef MySTL::vector<TestItem> TVector;
				TVector t(10);
				//std::cout <<t.capacity()<<" "<<t.size()<<" " <<TestItem::getCount() << std::endl;//10
				//std::cout << "push\n";
				t.push_back(TestItem());
				//std::cout << "end push\n";
				//std::cout << "push\n";
				t.push_back(TestItem());
				//std::cout << "end push\n";
				//std::cout << "push\n";
				t.push_back(TestItem());
				//std::cout << "end push\n";
				//std::cout << t.capacity() << " " << t.size() << " " << TestItem::getCount() << std::endl;//10
				t.insert(t.begin(), t.begin(), t.begin() + 1);
				//std::cout << t.capacity() << " " << t.size() << " " << TestItem::getCount() << std::endl;//10
			}
			assert(TestItem::getCount() == 0);
		}

		void testAllCases() {
			int a[15];
			for (int i = 0; i < 15; i++) a[i] = i + 1;
			int index = 0;
			
			std::cout << a[index++] << std::endl; testCase1();
			std::cout << a[index++] << std::endl; testCase2();
			std::cout << a[index++] << std::endl; testCase3();
			std::cout << a[index++] << std::endl; testCase4();
			std::cout << a[index++] << std::endl; testCase5();
			std::cout << a[index++] << std::endl; testCase6();
			std::cout << a[index++] << std::endl; testCase7();
			std::cout << a[index++] << std::endl; testCase8();
			std::cout << a[index++] << std::endl; testCase9();
			std::cout << a[index++] << std::endl; testCase10();
			std::cout << a[index++] << std::endl; testCase11();
			std::cout << a[index++] << std::endl; testCase12();
			std::cout << a[index++] << std::endl; testCase13();
			std::cout << a[index++] << std::endl; testCase14();
			std::cout << a[index++] << std::endl; testCase15();
		}
	}
}

//#endif