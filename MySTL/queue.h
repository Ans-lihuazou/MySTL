#pragma once
#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "List.h"

namespace MySTL {
	template<class T,class Sequence = MySTL::list<T>>
	class queue {
	public:
		typedef typename Sequence::value_type value_type;
		typedef typename Sequence::size_type size_type;
		typedef typename Sequence::reference reference;
		typedef typename Sequence::const_reference const_reference;
		typedef Sequence sequence_type;

		explicit queue(const sequence_type& t = sequence_type()) :s(t) {};

		bool empty() { return s.empty(); }
		size_type size() { return s.size(); }

		reference front() { return s.front(); }
		const_reference front()const { return *s.begin(); }

		reference back() { return s.back(); }
		const_reference back() const { return *s.end(); }

		void push(const value_type& value) { s.push_back(value); }
		void pop() { s.pop_front(); }

		void swap(queue& q) { s.swap(q.s); }

		template<class T,class Sequence>
		friend bool operator==(const queue<T, Sequence>&, const queue<T, Sequence>&);
		template<class T, class Sequence>
		friend bool operator!=(const queue<T, Sequence>&, const queue<T, Sequence>&);
		template<class T,class Sequence>
		friend void swap(queue<T, Sequence>&, queue<T, Sequence>&);

	private:
		MySTL::list<T> s;
	};

	template<class T, class Sequence>
	bool operator==(const queue<T, Sequence>& lhs, const queue<T, Sequence>& rhs) {
		return lhs.s == rhs.s;
	};
	template<class T, class Sequence>
	bool operator!=(const queue<T, Sequence>& lhs, const queue<T, Sequence>& rhs) {
		return lhs.s != rhs.s;
	};
	template<class T, class Sequence>
	void swap(queue<T, Sequence>& lhs, queue<T, Sequence>& rhs) {
		lhs.swap(rhs);
	};

}


#endif // !_QUEUE_H_

