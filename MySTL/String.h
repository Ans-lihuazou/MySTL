#ifndef _STRING_H_2023_1_6_
#define _STRING_H_2023_1_6_

#include <stddef.h>

#include "Allocator.h"
#include "Utlity.h"

namespace MySTRING {

	class string {
	public:
		
		typedef char		value_type;

		typedef char*		pointer;
		typedef char*		iterator;
		typedef char&		reference;
		typedef const char* const_pointer;
		typedef const char* const_iterator;
		typedef const char& const_reference;

		typedef size_t		size_type;
		typedef ptrdiff_t	difference_type;

		typedef MySTL::allocator<char> dataAllocator;
		
		//construct
		string();
		string(const string& str);
		string(const string& str, size_t pos, size_t len);
		string(const char* s);
		string(const char* s, size_t n);
		string(size_t n, char c);
		template <class InputIterator>  
		string(InputIterator first, InputIterator last);

		virtual ~string();

		//Iterators
		iterator begin();
		const_iterator cbegin() const;

		iterator end();
		const_iterator cend() const;

		//Capacity
		size_type size() const;
		size_type length() const;
		size_type capacity()const;
		void resize(size_type sz, char c = 0);
		void reserver(size_type sz);//改变容量
		void clear();
		bool empty();
		void shrink_to_fit();//去掉预留空间

		//Element access:
		reference operator[](size_type pos);
		const_reference operator[](size_type pos) const;

		reference at(size_type pos);
		const_reference at(size_type pos) const;

		reference back();
		const_reference back()const;

		reference front();
		const_reference front()const;

		//Modifiers:
		string& operator+(const string& str);
		string& operator+(const char* c);
		string& operator+(char c);

		string& operator+=(const string& str);
		string& operator+=(const char* c);
		string& operator+=(char c);

	private:
		iterator _start;
		iterator _finsh;
		iterator _end_of_storage;

		void deallocate();
		void allocate(size_type sz, value_type c = 0);
		

	};
}

#endif // !_STRING_H_2023_1_6_

