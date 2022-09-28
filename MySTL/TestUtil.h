#pragma once


#include <iterator>
#include <iostream>
#include <string>

namespace MySTL {
	namespace Test {

		template<class Container>
		void print_container(Container& container, const std::string& name = "") {//����ÿһ����������const_iterator
			std::cout << "Container " << name << " :";
			for (auto val : container) {
				std::cout << val << " ";
			}
			std::cout << std::endl;
		}

		template<class Container1, class Container2>
		bool container_equal(Container1& con1, Container2& con2) {//����ÿһ����������const_iterator
			//std::cout << "begin equal\n";
			auto first1 = std::begin(con1), last1 = std::end(con1);
			auto first2 = std::begin(con2), last2 = std::end(con2);
			for (; first1 != last1 && first2 != last2; ++first1, ++first2) {
				//std::cout << *first1 << " " << *first2 << std::endl;
				if (*first1 != *first2)
					return false;
			}
			//std::cout << "end equal\n";
			return (first1 == last1 && first2 == last2);
		}
	}
}