#pragma once

#ifndef _UTLITY_H_
#define _UTLITY_H_



#include "TypeTraits.h"
#include "Iterator.h"
#include "Algorithm.h"
#include <cstring>
#include <string.h>

namespace MySTL {
	//swap
	template<class T>
	void swap(T& a, T& b) {
		T temp = a;
		a = b;
		b = temp;
	}

	//uninitialized_fill_n
	template<class ForwardIterator, class Size, class T>
	ForwardIterator _uninitialized_fill_n_aux
	(ForwardIterator first, Size sz, const T& v, _true_type) {
		//std::cout << "_true_type_\n";
		return MySTL::fill_n(first, sz, v);
	}

	template<class ForwardIterator, class Size, class T>
	ForwardIterator _uninitialized_fill_n_aux
	(ForwardIterator first, Size sz, const T& v, _false_type) {
		//std::cout << "_fasle_type_\n";
		ForwardIterator cur = first;
		for (; sz; sz--, cur++)_Construct_::construct(&*cur, v);
		return cur;
	}


	//template<class ForwardIterator, class Size, class T, class ValueType>
	//ForwardIterator _uninitialized_fill_n
	//(ForwardIterator first, Size sz, const T& value, ValueType) {
	//	return _uninitialized_fill_n_aux(first, sz, value, is_Pod(first));
	//}

	template<class ForwardIterator, class Size, class T>
	ForwardIterator
		uninitialized_fill_n(ForwardIterator first, Size sz, const T& value) {
		typedef typename _type_traits<T>::is_POD_type POD_type;
		return _uninitialized_fill_n_aux(first, sz, value, POD_type());
	}

	//uninitialized_copy
	template<class InputIterator, class ForwardIterator>
	ForwardIterator _uninitialized_copy_aux(InputIterator first, InputIterator last, ForwardIterator result, _true_type) {
		/*ptrdiff_t dis = last - first;
		memcpy(result, first,dis * sizeof(*first));
		return result + dis;*/
		return std::copy(first, last, result);
	}

	template<class InputIterator, class ForwardIterator>
	ForwardIterator _uninitialized_copy_aux(InputIterator first, InputIterator last, ForwardIterator result, _false_type) {
		ForwardIterator cur = result;
		for (; first != last; first++, cur++) {
			_Construct_::construct(&*cur, *first);
		}
		return cur;
	}

	//template<class InputIterator, class ForwardIterator£¬class ValueType>
	//ForwardIterator _uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result,value_type) {
	//	return _uninitialized_copy_aux(first, last, result, is_Pod(result));
	//}

	template<class InputIterator, class ForwardIterator>
	ForwardIterator uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result) {
		typedef typename _type_traits< typename IteratorTraits<InputIterator>::value_type 
		>::is_POD_type POD_type;
		return _uninitialized_copy_aux(first, last, result, POD_type());
	}

	//uninitialized_fill
	template<class ForwardIterator, class T>
	void _uninitialized_fill_aux
	(ForwardIterator first, ForwardIterator last, const T& v, _true_type) {
		fill(first, last, v);
	}

	template<class ForwardIterator, class T>
	void _uninitialized_fill_aux
	(ForwardIterator first, ForwardIterator last, const T& v, _false_type) {
		for (; first < last; first++) _Construct_::construct(&*first, v);
	}

	template<class ForwardIterator, class T>
	void uninitialized_fill
	(ForwardIterator first, ForwardIterator last, const T& v) {
		typedef typename _type_traits<T>::is_POD_type POD_type;
		_uninitialized_fill_aux(first, last, v, POD_type());
	}
}

#endif // !_UTLITY_H_