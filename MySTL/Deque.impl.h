
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

	//deque
	//功能函数
	template<class	T,class Alloc>
	void deque<T, Alloc>::_init() {
		map_size = 2;
		map = mapAllocator::allocate(map_size);
		_start._container = _finsh._container = this;
		_start._map_index = _finsh._map_index = 1;
		_start._cur = _finsh._cur = map[1];
	}

	template<class	T, class Alloc>
	typename deque<T, Alloc>::size_type
		deque<T, Alloc>::_get_buffer_size() { return BUFFERSIZE; }

	template<class	T, class Alloc>
	typename deque<T, Alloc>::pointer
		deque<T, Alloc>::_allocate_block() {
		return dataAllocator::allocate(BUFFERSIZE);
	}

	template<class	T, class Alloc>
	typename deque<T, Alloc>::map_pointer 
	deque<T, Alloc>::_allocate_map(size_type n) {
		map_pointer temp = mapAllocator::allocate(n);
		for (int i = 0; i < n; i++)
			temp[i] = _allocate_block();
		return temp;
	}

	template<class	T, class Alloc>
	typename deque<T, Alloc>::map_pointer
		deque<T, Alloc>::_reallocate_and_copy(size_type n) {
		size_type _new_mapsize = n;
		map_pointer temp = _allocate_map(_new_mapsize);
		size_type _start_index = _new_mapsize / 4;//当前容量为4倍
		for (int i = _start._map_index; i < map_size && i <= _finsh._map_index; i++) {
			for (int j = 0; j < BUFFERSIZE; j++) {
				temp[_start_index][j] = map[i][j];
			}
			_start_index++;
		}
		_start_index = _new_mapsize / 4;
		size_type _first_to_cur = _start._cur - map[_start._map_index];
		size_type _last_size = this->size();
		clear();
		map_size = _new_mapsize;
		_start = iterator(_start_index / 4, temp[_start_index] + _first_to_cur, this);
		_finsh = _start + _last_size;
	}

	template<class	T, class Alloc>
	typename deque<T, Alloc>::size_type
		deque<T, Alloc>::_get_new_size(size_type n) {
		return ((n == 0) ? 2 : n * 2);
	}

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
		map_size = q.map_size;
		map = _allocate_map(map_size);
		_start._map_index = q._start._map_index;
		_finsh._map_index = q._finsh._map_index;
		_start._cur = map[_start._map_index] + (q._start._cur - q.map[q._start._map_index]);
		_finsh._cur = map[_finsh._map_index] + (q._finsh._cur - q.map[q._finsh._map_index]);
		for (iterator i = _start,j = q._start; i < _finsh; i++) {
			*(i._cur) = *(j._cur);
		}
	}
	
	template<class T, class Alloc>
	deque<T, Alloc>::deque(deque&& q) {
		map_size = q.map_size;
		map = _allocate_map(map_size);
		_start._map_index = q._start._map_index;
		_finsh._map_index = q._finsh._map_index;
		_start._cur = map[_start._map_index] + (q._start._cur - q.map[q._start._map_index]);
		_finsh._cur = map[_finsh._map_index] + (q._finsh._cur - q.map[q._finsh._map_index]);
		for (iterator i = _start, j = q._start; i < _finsh; i++) {
			*(i._cur) = *(j._cur);
		}
	}

	//template<class T,class Alloc>
	//deque<T, Alloc>::~deque() {
	//	for(int i=0;)
	//}
}

#endif // !_DEQUE_IMPL_H_
