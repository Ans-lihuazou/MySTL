#pragma once

#include <cstddef>
#include "Construct.h"
#include "Alloc.h"

//¹¹Ôì£¬Îö¹¹
namespace MySTL {

	template<class T>
	class allocator {
	public:
		typedef T			value_type;
		typedef T* pointer;
		typedef const T* const_pointer;
		typedef T& reference;
		typedef const T& const_reference;
		typedef size_t		size_type;
		typedef ptrdiff_t	difference_type;

		static T* allocate();
		static T* allocate(size_t byte);
		static void deallocate(T*);
		static void deallocate(T*, size_t);

		static void construct(T*);
		static void construct(T*, const T&);
		static void destroy(T*);
		static void destroy(T*, T*);

	private:

	};

}

#include "Allocator.impl.h"