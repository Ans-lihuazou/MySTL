#pragma once


#include "TypeTraits.h"
#include "Iterator.h"
#include <cstdlib>

namespace MySTL {
	namespace _Construct_ {
		template<class T>
		inline void construct(T* p, const T& v) {
			new(p)T(v);
		}

		template<class T>
		inline void destory(T* p) {
			p->~T();
		}

		template<class ForwardIterator>
		inline void _destory(ForwardIterator first, ForwardIterator last, _true_type) {}

		template<class ForwardIterator>
		inline void _destory(ForwardIterator first, ForwardIterator last, _false_type) {
			for (; first != last; first++) destory(&*first);
		}

		//template<class ForwardIterator>
		//inline typename _type_tarits<ForwardIterator>::is_POD_type is_Pod(ForwardIterator iter) {
		//	typename _type_tarits<ForwardIterator>::is_POD_type POD_type;
		//	return POD_type();
		//}

		template<class ForwardIterator>
		inline void destory(ForwardIterator first, ForwardIterator last) {
			typedef typename
			_type_traits<typename IteratorTraits<ForwardIterator>::value_type>::
				is_POD_type POD_type;
			_destory(first, last, POD_type());
		}
	}
}
