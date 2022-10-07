#pragma once

#ifndef _STACK_H_
#define _STACK_H_


#include "Vector.h"

namespace MySTL {
	
	template<class T,class Sequence = MySTL::vector<T>>
	class stack {
	public:
		typedef typename Sequence::value_type value_type;
		typedef typename Sequence::reference reference;
		typedef typename Sequence::const_reference const_reference;
		typedef typename Sequence::size_type size_type;
		typedef typename Sequence sequence_type;

		explicit stack(const sequence_type& t=sequence_type()):s(t) {};


		void push(const value_type& value) { s.push_back(value); }
		void pop() { s.pop_back(); }
		reference top() { return s.back(); }
		const_reference top()const { return s.back(); }

		size_type size() { return s.size(); };
		bool empty() { return s.empty(); };

		void swap(stack& sta) { s.swap(sta.s); };

		bool operator==(const stack& sta) { return s == sta.s; }
		bool operator!=(const stack& sta) { return s != sta.s; }

		template<class T,class Sequence>
		friend bool operator==(const stack<T, Sequence>&, const stack<T, Sequence>&);

		template<class T, class Sequence>
		friend bool operator!=(const stack<T, Sequence>&, const stack<T, Sequence>&);

		template <class T, class Sequence>
		friend void swap(stack<T, Sequence>&, stack<T, Sequence>&);

	private:
		sequence_type s;//µ×²ãÈÝÆ÷,¿ÉÒÔÑ¡Ôñlist,deque,vector

	};//end class stack

	template <class T, class Sequence>
	bool operator== (const stack<T, Sequence>& lhs, const stack<T, Sequence>& rhs) {
		return lhs.s == rhs.s;
	}
	template <class T, class Sequence>
	bool operator!= (const stack<T, Sequence>& lhs, const stack<T, Sequence>& rhs) {
		return lhs.s != rhs.s;
	}
	template <class T, class Sequence>
	void swap(stack<T, Sequence>& x, stack<T, Sequence>& y) {
		x.swap(y);
	}

}//end namespace

#endif // !_STACK_H_
