
#pragma once
#ifndef _DEQUE_IMPL_H_
#define _DEQUE_IMPL_H_

#include "Deque.h"
namespace MySTL {
	
	namespace MyDeque {
		template<class T>
		iterator_deque<T> operator + (const iterator_deque<T>& it, typename iterator_deque<T>::difference_type n) {//assume n >= 0
			iterator_deque<T> res(it);
			auto m = res._get_tail(res._map_index) - res.cur_;
			if (n <= m) {//前进n步仍在同一个桶中
				res._cur += n;
			}
			else {
				n = n - m;
				res._map_index += (n / it._get_buffer_size() + 1);
				auto p = res._get_buffer_size(res._map_index);
				auto x = n % it._get_buffer_size() - 1;
				res._cur = p + x;
			}
			return res;
		}
		template<class T>
		iterator_deque<T> operator + (typename iterator_deque<T>::difference_type n, const iterator_deque<T>& it) {
			return (it + n);
		}
		template<class T>
		iterator_deque<T> operator - (const iterator_deque<T>& it, typename iterator_deque<T>::difference_type n) {//assume n >= 0
			iterator_deque<T> res(it);
			auto m = res._cur - res._get_buffer_size(res._map_index);
			if (n <= m)//后退n步还在同一个桶中
				res._cur -= n;
			else {
				n = n - m;
				res._map_index -= (n / res._get_buffer_size() + 1);
				res.cur_ = res._get_buffer_size(res._map_index) - (n % res._get_buffer_size() - 1);
			}
			return res;
		}
		template<class T>
		iterator_deque<T> operator - (typename iterator_deque<T>::difference_type n, const iterator_deque<T>& it) {
			return (it - n);
		}
		template<class T>
		typename iterator_deque<T>::difference_type operator - (const iterator_deque<T>& it1, const iterator_deque<T>& it2) {
			if (it1._container == it2._container && it1._container == 0)
				return 0;
			return typename iterator_deque<T>::difference_type(it1._get_buffer_size()) * (it1._map_index - it2._map_index - 1)
				+ (it1._cur - it1._get_buffer_size(it1._map_index)) + (it2._get_buffer_size(it2._map_index) - it2._cur) + 1;
		}
		
	}//end of namepspace mydeque

	////功能函数
	//template<class T, class Alloc, size_t BufSize>
	//typename deque<T, Alloc, BufSize>::map_pointer _get_new_map(size_type n) {
	//	size_type _num_nodes = n / MyDeque::iterator_deque::buffer_size() + 1;
	//	map_size = std::max(8, _num_nodes + 2);
	//	map = mapAllocator::allocate(map_size);
	//	map_pointer _new_start = map + (map_size - _num_nodes) / 2;
	//	map_pointer _new_finsh = _new_start + _num_nodes - 1;
	//	map_pointer cur = _new_start;
	//	for (; cur <= _new_finsh; cur++) {
	//		*cur = dataAllocator::allocate(BufSize);
	//	}
	//	_statr = new_start;
	//	_finsh = new_finsh;
	//	_start.cur = start.first;
	//	_finsh.cur = _finsh.last;
	//}


	template<class T,class Alloc>
	deque<T, Alloc>::deque():map(0),map_size(0) {};

	template<class T, class Alloc>
	deque<T, Alloc>::deque(size_type n,const value_type& value) {
		_deque_aux(n, value, std::is_integral<size_type>::type());
	}

	template<class T, class Alloc>
	template<class InputIterator>
	deque<T, Alloc>::deque(InputIterator first, InputIterator last) {
		_deque_aux(first, last, std::is_integral<InputIterator>::type());
	}

	template<class T, class Alloc>
	deque<T, Alloc>::deque(const deque& q) {
		
	}
	

}

#endif // !_DEQUE_IMPL_H_
