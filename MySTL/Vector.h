 

#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <algorithm>
#include <type_traits>

#include "Iterator.h"
#include "Allocator.h"
#include "ReverseIterator.h"
#include "Utlity.h"


namespace MySTL {
	template<class T, class Alloc = allocator<T>>
	class vector {
	public:
		typedef T							value_type;
		typedef T*							pointer;
		typedef T*							iterator;
		typedef const T*					const_iterator;
		typedef T&							reference;
		typedef const T&					const_reference;
		typedef size_t						size_type;
		typedef ptrdiff_t					difference_type;
		typedef reverse_iterator<T*>		reverse;
		typedef reverse_iterator<const T*>	const_reverse;
		typedef Alloc						dataAllocator;

		//ctor,copy ctor,dtor,assignment
		vector();
		explicit vector(size_type);
		vector(size_type, const value_type&);
		template<class InputIterator>
		vector(InputIterator, InputIterator);
		vector(const vector&);
		vector(vector&&);

		vector& operator=(const vector&);
		vector& operator=(vector&&);

		~vector();

		//迭代器相关
		iterator begin() { return _start; }
		const_iterator begin()const { return _start; }
		const_iterator cbegin()const { return _start; }
		iterator end() { return _finsh; }
		iterator end() const { return _finsh; }
		const_iterator cend() const { return _finsh; }
		reverse rbegin() { return reverse(_finsh); }
		const_reverse crbegin()const { return const_reverse(_finsh); }
		reverse rend() { return reverse(_start); }
		const_reverse crend() const { return const_reverse(_start); }

		//Capacity
		difference_type size()const { return _finsh - _start; }
		difference_type capacity()const { return _end_of_storage - _start; }
		bool empty() { return _start == _finsh; }
		void shrink_to_fit();//去掉预留空间
		void reserve(size_type);
		void resize(size_type n, value_type v = value_type());

		//Element access(取值)
		reference operator[](const size_type n) { assert(n < size());  return *(_start + n); }
		const_reference operator[](const size_type n)const { assert(n > size()); return *(cbegin() + n); }
		reference front() { return *_start; }
		reference back() { return *(_finsh - 1); }
		pointer data() { return _start; }
		reference at(size_type n) { return operator[](n); }
		const_reference at(size_type n)const { return operator[](n); }

		//Modifiers:

		void push_back(const value_type&);
		void pop_back();
		iterator insert(iterator, const value_type&);
		iterator insert(iterator, size_type, const value_type&);
		template<class InputIterator>
		iterator insert(iterator, InputIterator, InputIterator);
		iterator erase(iterator);
		iterator erase(iterator, iterator);
		void clear();
		void swap(vector&);

		//Allocator:
		Alloc get_allocator() { return dataAllocator; }

		//operator
		template<class T, class Alloc>
		friend bool operator ==<T, Alloc>(const vector<T, Alloc>& v1, const vector<T, Alloc>& v2);
		template<class T, class Alloc>
		friend bool operator !=<T, Alloc>(const vector<T, Alloc>& v1, const vector<T, Alloc>& v2);

		bool operator ==(const vector<T, Alloc>& v);
		bool operator !=(const vector<T, Alloc>& v);


	private:

		iterator _start;
		iterator _finsh;
		iterator _end_of_storage;

		void _destory_and_deallocate();//析构并释放空间
		void _allocate_and_construct(size_t, const value_type&);//申请空间并构造

		template<class InputIterator>//vector(iter1,iter2);
		void _vector_aux(InputIterator first, InputIterator last, std::true_type);
		template<class InputIterator>
		void _vector_aux(InputIterator first, InputIterator last, std::false_type);

		iterator _insert_aux(iterator, size_t, const value_type&, std::true_type);
		template<class InputIterator>
		iterator _insert_aux(iterator, InputIterator first, InputIterator last, std::false_type);

		template<class InputIterator>
		void _allocate_and_copy(InputIterator first, InputIterator last);

		template<class InputIterator>
		iterator _reallocate_and_copy(iterator, InputIterator, InputIterator);
		iterator _reallocate_and_copy(iterator, size_t, const value_type&);


	};
	
};//end of namespace

#include "Vector.imp.h"
#endif // !_VECTOR_


