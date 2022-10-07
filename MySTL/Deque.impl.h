
#pragma once
#ifndef _DEQUE_IMPL_H_
#define _DEQUE_IMPL_H_

//#include "Deque.h"

namespace MySTL {
	
	namespace MyDeque {
		template<class T>
		iterator_deque<T> operator + (const iterator_deque<T>& it, typename iterator_deque<T>::difference_type n) {//assume n >= 0
			iterator_deque<T> res(it);
			typename iterator_deque<T>::difference_type m = res._get_tail(res._map_index) - res._cur;
			if (n <= m) {//前进n步仍在同一个桶中
				res._cur += n;
			}
			else {
				n = n - m;
				res._map_index += (n / res._get_buffer_size() + 1);
				auto p = res._get_head(res._map_index);
				auto x = n % res._get_buffer_size() - 1;
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
			typename iterator_deque<T>::difference_type m = res._cur - res._get_head(res._map_index);
			if (n <= m)//还在同一个桶中
				res._cur -= n;
			else {
				n = n - m;
				res._map_index -= (n / res._get_buffer_size() + 1);
				res._cur = res._get_tail(res._map_index) - (n % res._get_buffer_size() - 1);
			}
			return res;
		}
		template<class T>
		iterator_deque<T> operator - (typename iterator_deque<T>::difference_type n, const iterator_deque<T>& it) {
			return (it - n);
		}
		//friend typename iterator_deque<T>::difference_type operator - (const iterator_deque<T>& it1, const iterator_deque<T>& it2);
		template<class T>
		typename iterator_deque<T>::difference_type operator - (const iterator_deque<T>& it1, const iterator_deque<T>& it2) {
			if (it1._container == it2._container && it1._container == 0)
				return 0;
			//typename iterator_deque<T>::difference_type result = 0;
			//(it1._cur - it1._get_head(it1._map_index))
			//it1._get_head(it1._map_index);
			typename iterator_deque<T>::difference_type result = (it1._get_buffer_size()) * (it1._map_index - it2._map_index - 1)
				+ (it1._cur - it1._get_head(it1._map_index)) + (it2._get_tail(it2._map_index) - it2._cur) + 1;
			return result;
		}
		
		template<class T>
		void swap(iterator_deque<T>& iter1, iterator_deque<T>& iter2) {
			iter1.swap(iter2);
		}
		
	}//end of namepspace mydeque

	//deque
	//功能函数
	//deque只有在构造时才会调用
	template<class T,class Alloc>
	void deque<T, Alloc>::_deque_aux(size_type n, const value_type& value, std::true_type) {
		int i = 0, sign = n / 2;
		for (; i != sign; ++i)//每次扩容后数据在最中间，同时向双侧扩容可以减少重新申请空间的次数
			(*this).push_front(value);
		for (; i != n; ++i)
			(*this).push_back(value);
	}

	template<class T,class Alloc>
	template<class InputIterator>
	void deque<T, Alloc>::_deque_aux(InputIterator first, InputIterator last, std::false_type) {
		difference_type mid = (last - first) / 2;
		for (InputIterator iter = first + mid; iter != first; iter--) {
			(*this).push_front(*iter);
		}
		(*this).push_front(*first);
		for (InputIterator iter = first + mid + 1; iter != last; iter++) {
			(*this).push_back(*iter);
		}

	}

	template<class	T,class Alloc>
	void deque<T, Alloc>::_init() {
		map_size = 2;
		map = _allocate_map(map_size);
		_start._container = _finsh._container = this;
		_start._map_index = _finsh._map_index = 1;
		_start._cur = _finsh._cur = map[1];
	}

	template<class	T, class Alloc>
	typename deque<T, Alloc>::size_type
		deque<T, Alloc>::_get_buffer_size()const { return BUFFERSIZE; }

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
	void deque<T, Alloc>::_reallocate_and_copy() {
		size_type _new_mapsize = _get_new_size(map_size);
		map_pointer temp = _allocate_map(_new_mapsize);
		size_type _start_index = _new_mapsize / 4;//当前容量为4倍
		int i = _start._map_index;
		
		for ( ;i < map_size; i++) {
			if (i == _finsh._map_index) break;
			for (int j = 0; j < BUFFERSIZE; j++) {
				temp[_start_index][j] = map[i][j];
			}
			_start_index++;
		}
		if (i < map_size) {
			for (int j = 0; map[i]+j != _finsh._cur; j++) {
				temp[_start_index][j] = map[i][j];
			}
		}
		_start_index = _new_mapsize / 4;
		size_type _first_to_cur = _start._cur - map[_start._map_index];
		size_type _last_size = this->size();
		clear();
		for (int i = 0; i < map_size; i++) {
			dataAllocator::deallocate(map[i]);
		}
		mapAllocator::deallocate(map, map_size);
		map_size = _new_mapsize;
		_start = iterator(_start_index, temp[_start_index] + _first_to_cur, this);
		_finsh = _start + _last_size;
		map = temp;
	}

	template<class	T, class Alloc>
	typename deque<T, Alloc>::size_type
		deque<T, Alloc>::_get_new_size(size_type n) {
		return ((n == 0) ? 2 : n * 2);
	}

	//template<class T, class Alloc>
	//inline const_iterator deque<T, Alloc>::changeIteratorToConstIterator(iterator&) const
	//{
	//	return const_iterator();
	//}

	template<class T,class Alloc>
	typename deque<T, Alloc>::const_iterator deque<T, Alloc>::changeIteratorToConstIterator(iterator& iter)const {
		auto temp = (deque<const T>*const)this;
		return const_iterator(iter._map_index,const_cast<const value_type*>(iter._cur)
		,temp);

	}

	template<class T,class Alloc>
	bool deque<T, Alloc>::_back_is_full() {
		return map[map_size] == _finsh._cur;
		//return (_finsh._map_index == map_size);
	}

	template<class T, class Alloc>
	bool deque<T, Alloc>::_head_is_full() {
		return map[0] == _start._cur;
		//return (_start._map_index == 0);
	}

	//********************************************

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
		_start._container = _finsh._container = this;
		_start._cur = map[_start._map_index] + (q._start._cur - q.map[q._start._map_index]);
		_finsh._cur = map[_finsh._map_index] + (q._finsh._cur - q.map[q._finsh._map_index]);
		for (iterator i = _start,j = q._start; i != _finsh; i++,j++) {
			*(i._cur) = *(j._cur);
		}
	}
		
	template<class T, class Alloc>
	deque<T, Alloc>::deque(deque&& q) {
		map_size = q.map_size;
		map = _allocate_map(map_size);
		_start._map_index = q._start._map_index;
		_finsh._map_index = q._finsh._map_index;
		_start._container = _finsh._container = this;
		_start._cur = map[_start._map_index] + (q._start._cur - q.map[q._start._map_index]);
		_finsh._cur = map[_finsh._map_index] + (q._finsh._cur - q.map[q._finsh._map_index]);
		for (iterator i = _start, j = q._start; i != _finsh; i++,j++) {
			*(i._cur) = *(j._cur);
		}
	}
	
	template<class T,class Alloc>
	deque<T, Alloc>::~deque() {
		for (iterator first = _start; first != _finsh; first++) {
			dataAllocator::destroy(first._cur);
		}
		for (int i = 0; i < map_size; i++) {
			dataAllocator::deallocate(map[i]);
		}
		mapAllocator::deallocate(map,map_size);
	}

	template<class T,class Alloc>
	deque<T, Alloc>& deque<T, Alloc>::operator=(const deque<T, Alloc>& q) {
		map_size = q.map_size;
		map = _allocate_map(map_size);
		_start._map_index = q._start._map_index;
		_finsh._map_index = q._finsh._map_index;
		_start._container = _finsh._container = this;
		_start._cur = map[_start._map_index] + (q._start._cur - q.map[q._start._map_index]);
		_finsh._cur = map[_finsh._map_index] + (q._finsh._cur - q.map[q._finsh._map_index]);
		for (iterator i = _start, j = q._start; i != _finsh; i++, j++) {
			*(i._cur) = *(j._cur);
		}
		return *this;
	}

	template<class T, class Alloc>
	deque<T, Alloc>& deque<T, Alloc>::operator=(deque<T, Alloc>&& q) {
		map_size = q.map_size;
		map = _allocate_map(map_size);
		_start._map_index = q._start._map_index;
		_finsh._map_index = q._finsh._map_index;
		_start._container = _finsh._container = this;
		_start._cur = map[_start._map_index] + (q._start._cur - q.map[q._start._map_index]);
		_finsh._cur = map[_finsh._map_index] + (q._finsh._cur - q.map[q._finsh._map_index]);
		for (iterator i = _start, j = q._start; i < _finsh; i++, j++) {
			*(i._cur) = *(j._cur);//赋值值
}
		return *this;
	}

	template<class T,class Alloc>
	typename deque<T, Alloc>::iterator deque<T, Alloc>::begin() {
		return _start;
	}

	//template<class T, class Alloc>
	//typename deque<T, Alloc>::const_iterator deque<T, Alloc>::begin() const{
	//	return changeIteratorToConstIterator(_start);
	//}

	template<class T, class Alloc>
	typename deque<T, Alloc>::iterator deque<T, Alloc>::begin() const {
		return _start;
	}

	template<class T, class Alloc>
	typename deque<T, Alloc>::const_iterator deque<T, Alloc>::cbegin() const {
		return changeIteratorToConstIterator(_start);
	}

	template<class T, class Alloc>
	typename deque<T, Alloc>::iterator deque<T, Alloc>::end() {
		return _finsh;
	}

	template<class T, class Alloc>
	typename deque<T, Alloc>::iterator deque<T, Alloc>::end() const {
		return _finsh;
	}

	template<class T, class Alloc>
	typename deque<T, Alloc>::const_iterator deque<T, Alloc>::cend() const {
		return changeIteratorToConstIterator(_finsh);
	}

	template<class T,class Alloc>
	typename deque<T, Alloc>::reverse deque<T, Alloc>::rbegin() {
		return reverse(_start);
	}

	template<class T, class Alloc>
	typename deque<T, Alloc>::reverse deque<T, Alloc>::rend() {
		return reverse(_finsh);
	}

	template<class T, class Alloc>
	typename deque<T, Alloc>::reference deque<T, Alloc>::front() {
		return *_start;
	}

	template<class T, class Alloc>
	typename deque<T, Alloc>::reference deque<T, Alloc>::back() {
		return *(_finsh - 1);
	}

	template<class T, class Alloc>
	typename deque<T, Alloc>::reference deque<T, Alloc>::operator[](size_type n) {
		return *(_start + n);
	}
	//iterator_deuqe需要特化
	template<class T, class Alloc>
	typename deque<T, Alloc>::const_reference deque<T, Alloc>::front() const{
		return *_start;
	}

	template<class T, class Alloc>
	typename deque<T, Alloc>::const_reference deque<T, Alloc>::back() const {
		return *(_finsh - 1);
	}

	template<class T, class Alloc>
	typename deque<T, Alloc>::const_reference deque<T, Alloc>::operator[](size_type n)const {
		return *(_finsh + n);
	}

	template<class T, class Alloc>
	typename deque<T, Alloc>::reference deque<T, Alloc>::at(size_type n) {
		return *(_finsh + n);
	}

	template<class T, class Alloc>
	void deque<T, Alloc>::push_front(const value_type& value) {
		if (empty()) {
			_init();
		}
		else if (_head_is_full()) {
			_reallocate_and_copy();
		}
		--_start;
		dataAllocator::construct(_start._cur, value);
	}

	template<class T,class Alloc>
	void deque<T, Alloc>::push_back(const value_type& value) {
		if (empty()) {
			_init();
		}
		else if (_back_is_full()) {
			_reallocate_and_copy();
		}
		dataAllocator::construct(_finsh._cur, value);
		_finsh++;
	}

	template<class T, class Alloc>
	void deque<T, Alloc>::pop_front() {
		dataAllocator::destroy(_start._cur);
		++_start;
	}

	template<class T, class Alloc>
	void deque<T, Alloc>::pop_back() {
		--_finsh;
		dataAllocator::destroy(_finsh._cur);
	}

	template<class T,class Alloc>
	void deque<T, Alloc>::swap(deque<T, Alloc>& q) {
		MySTL::swap(map_size, q.map_size);
		MySTL::swap(map, q.map);
		_start.swap(q._start);
		_finsh.swap(q._finsh);
	}

	template<class T,class Alloc>
	void deque<T, Alloc>::clear() {
		for (iterator first = _start; first != _finsh; first++)
			dataAllocator::deallocate(first._cur);
		_start._map_index = _finsh._map_index = map_size / 2;
		_start._cur = _finsh._cur = map[map_size / 2];
	}
	//__int64 MySTL::MyDeque::operator -<T>(const MySTL::MyDeque::iterator_deque<T>&, const MySTL::MyDeque::iterator_deque<T>&)
	//__int64 MySTL::MyDeque::operator -<T>(const MySTL::MyDeque::iterator_deque<T>&, const MySTL::MyDeque::iterator_deque<T>&)
	template<class T, class Alloc >
	typename deque<T, Alloc>::size_type deque<T, Alloc>::size() {
		return _finsh - _start;
	}

	template<class T,class Alloc>
	bool deque<T, Alloc>::empty() {
		return _start == _finsh;
	}

	//friend function
	template<class T, class Alloc>
	void swap(const deque<T, Alloc>& q1, const deque<T, Alloc>& q2) {
		q1.swap(q2);
	}
	/*template<class T, class Alloc>
	friend bool operator==(const deque<T, Alloc>&, const deque<T, Alloc>&);*/
	template<class T, class Alloc>
	bool operator== (const deque<T, Alloc>& q1, const deque<T, Alloc>& q2) {
		//using iterator_dq = typename deque<T, Alloc>::iterator;
		typename deque<T, Alloc>::iterator st1 = q1.begin();
		typename deque<T, Alloc>::iterator st2 = q2.begin();
		for (; st1 != q1.end() && st2 != q2.end(); st1++, st2++) {
			if (*st1 != *st2) return false;
		}
		if (st1 == q1.end() && st2 == q2.end()) return true;
		return false;
	}

	template<class T, class Alloc>
	bool operator!=(const deque<T, Alloc>& q1, const deque<T, Alloc>& q2) {
		return !(q1 == q2);
	}

}

#endif // !_DEQUE_IMPL_H_

