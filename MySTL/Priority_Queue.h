#pragma once
#ifndef _PRIORITY_QUEUE_H_
#define _PRIORITY_QUEUE_H_

#include "Vector.h"
#include "Allocator.h"

namespace MySTL {
	template<class T,class Sequence = MySTL::vector<T>,class Compare=MySTL::less<T>>
	class priority_queue {
	public:
		typedef T value_type;
		typedef T& refernece;
		typedef const T& const_reference;
		typedef size_t size_type;


		explicit priority_queue(const Sequence& t = Sequence(), const Compare c = Compare()) :
			s(t), cmp(c) {};
		template<class InputIterator>
		priority_queue(InputIterator first, InputIterator last,
			const Sequence& t = Sequence(), const Compare c = Compare()):s(t),cmp(c) {
			s.insert(s.end(), first, last);
			/*std::cout << std::endl;
			for (auto& i : s) std::cout << i << " ";
			std::cout << std::endl;*/
			Heap_Alogrithm::make_heap(s.begin(), s.end(), cmp);
		}

		void push(const value_type& value) {
			s.push_back(value);
			Heap_Alogrithm::push_heap(s.begin(), s.end(), cmp);
		};
		//refernece top() {};
		const_reference top()const { return s[0]; };
		void pop() {
			Heap_Alogrithm::pop_heap(s.begin(), s.end(), cmp);
			s.pop_back();
		};

		size_type size() { return s.size(); }
		bool empty() { return s.empty(); }

		void swap(priority_queue& pq) {
			MySTL::swap(s, pq.s);
			MySTL::swap(cmp, pq.cmp);
		}

		template<class T,class Sequence,class Compare>
		friend void swap(priority_queue<T, Sequence, Compare>&, priority_queue<T, Sequence, Compare>&);

	private:
		Sequence s;
		//MySTL::vector<value_type> s;
		Compare cmp;
		
	};

	template<class T, class Sequence, class Compare>
	void swap(priority_queue<T, Sequence, Compare>& lhs, priority_queue<T, Sequence, Compare>& rhs) {
		lhs.swap(rhs);
	}

}

#endif // !_PRIORITY_QUEUE_H_
