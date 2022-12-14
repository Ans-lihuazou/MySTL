#ifndef _VECTOR_IMP_H_2023_1_6_
#define _VECTOR_IMP_H_2023_1_6_

namespace MySTL {

	//功能函数
	template<class T, class Alloc>
	void vector<T, Alloc>::_destory_and_deallocate() {

		if (capacity()) {
			dataAllocator::destroy(_start, _finsh);//析构
			dataAllocator::deallocate(_start, capacity());//释放空间
		}
	}

	template<class T, class Alloc>
	void vector<T, Alloc>::_allocate_and_construct(size_t n, const value_type& v) {

		//std::cout << "_allocate_and_construct\n";
		_start = allocator<T>::allocate(n);
		//_start = allocator<T>::allocate(n);
		//_start = dataAllocator::allocate(n * sizeof(value_type));
		//if (!_start) std::cout << "error allocate\n";
		//std::cout << "mid _allocate_and_construct\n";
		MySTL::uninitialized_fill_n(_start, n, v);
		_finsh = _start + n;
		_end_of_storage = _finsh;
		//std::cout << "end _allocate_and_construct\n";
	}

	template<class T, class Alloc>
	template<class InputIterator>//vector(iter1,iter2);
	void vector<T, Alloc>::_vector_aux(InputIterator first, InputIterator last, std::true_type) {

		_allocate_and_construct(first, last);//first为个数，last为value
	};

	template<class T, class Alloc>
	template<class InputIterator>
	void vector<T, Alloc>::_allocate_and_copy(InputIterator first, InputIterator last) {

		assert((last - first) >= 0);
		_start = dataAllocator::allocate(last - first);
		_finsh = MySTL::uninitialized_copy(first, last, _start);
		_end_of_storage = _finsh;
	}

	template<class T, class Alloc>
	template<class InputIterator>//vector(iter1,iter2);
	void vector<T, Alloc>::_vector_aux(InputIterator first, InputIterator last, std::false_type) {

		//first，last为迭代器，将[first,last)的值拷入
		assert((last - first) >= 0);
		_allocate_and_copy(first, last);
	};

	template<class T, class Alloc>
	typename vector<T, Alloc>::iterator vector<T, Alloc>::_reallocate_and_copy
	(iterator position, size_t n, const value_type& val) {

		size_t index = position - _start;
		difference_type old_cap = capacity();
		difference_type new_cap = (old_cap == 0) ? n : old_cap + ((old_cap > n) ? old_cap : n);
		iterator new_start = dataAllocator::allocate(new_cap);
		//std::cout <<"malloc size: "<< sizeof(new_start) << std::endl;
		iterator new_finsh = MySTL::uninitialized_copy(_start, position, new_start);

		new_finsh = MySTL::uninitialized_fill_n(new_finsh, n, val);
		new_finsh = MySTL::uninitialized_copy(position, _finsh, new_finsh);
		_destory_and_deallocate();
		_start = new_start;
		_finsh = new_finsh;
		_end_of_storage = new_start + new_cap;

		return _start + index;
	}

	template<class T, class Alloc>
	template<class InputIterator>
	typename vector<T, Alloc>::iterator vector<T, Alloc>::_reallocate_and_copy(iterator postion, InputIterator first, InputIterator last) {
		
		size_t index = postion - _start;
		difference_type need_dis = last - first;
		difference_type old_cap = capacity();
		difference_type new_cap = (old_cap == 0) ? need_dis : old_cap + ((old_cap > need_dis) ? old_cap : need_dis);
		
		iterator new_start = dataAllocator::allocate(new_cap);
		iterator new_finsh = MySTL::uninitialized_copy(_start, postion, new_start);
		new_finsh = MySTL::uninitialized_copy(first, last, new_finsh);
		new_finsh = MySTL::uninitialized_copy(postion, _finsh, new_finsh);
		_destory_and_deallocate();
		_start = new_start;
		_finsh = new_finsh;
		_end_of_storage = _start + new_cap;

		return _start + index;
	}

	
	template<class T, class Alloc>
	typename vector<T, Alloc>::iterator vector<T, Alloc>::_insert_aux
	(iterator position, size_t n, const value_type& value, std::true_type) {

		assert(n > 0);
		difference_type dis = _end_of_storage - _finsh;//已申请的空间剩余量

		if (n <= dis) {//够用
			iterator temp = _finsh - 1;
			for (; temp - position >= 0; temp--) {
				//_Construct_::construct(temp + n, *temp);
				allocator<T>::construct(temp + n, *temp);//[postion,finsh) move to [postion+n ,finsh+n)
			}
			MySTL::uninitialized_fill_n(position, n, value);
			_finsh = _finsh + n;
		}
		else {
			return _reallocate_and_copy(position, n, value);
		}

		return position;
	}

	template<class T, class Alloc>
	template<class InputIterator>
	typename vector<T, Alloc>::iterator vector<T, Alloc>::_insert_aux
	(iterator position, InputIterator first, InputIterator last, std::false_type) {

		difference_type dis = _end_of_storage - _finsh;
		difference_type need_dis = last - first;
		assert(need_dis >= 0);

		if (dis >= need_dis) {
			difference_type right_dis = _finsh - position;
			if (right_dis >= need_dis) {//begin,begin,begin+1
				//std::cout << "start copy\n";
				MySTL::uninitialized_copy(_finsh - need_dis, _finsh, _finsh);
				//uninitialized_copy会调用构造函数初始化未调用的空间
				//copy不会，调用析构函数
				//std::copy(_finsh - need_dis, _finsh, _finsh);
				//std::cout << "copy1\n";
				std::copy_backward(position, _finsh - need_dis, _finsh);
				//std::cout << "copy2\n";
				//MySTL::uninitialized_copy(first, last, position);
				std::copy(first, last, position);
				//std::cout << "copy3\n";
			}
			else {
				difference_type out_dis = need_dis - right_dis;
				iterator temp_finsh = MySTL::uninitialized_copy(first + right_dis, last, _finsh);
				MySTL::uninitialized_copy(position, _finsh, temp_finsh);
				std::copy(first, first + right_dis, position);

			}
			_finsh = _finsh + need_dis;
		}
		else {
			return _reallocate_and_copy(position, first, last);
		}

		return position;
	}


	//析构，构造

	template<class T, class Alloc>
	vector< T, Alloc>::vector() :_start(0), _finsh(0), _end_of_storage(0) {};

	template<class T, class Alloc>
	vector < T, Alloc >::vector(size_type sz) {

		_allocate_and_construct(sz, value_type());
	}

	template<class T, class Alloc>
	vector<T, Alloc>::vector(size_type sz, const value_type& value) {

		//std::cout << "begin\n";
		_allocate_and_construct(sz, value);
		//std::cout << "end\n";s
	}

	template<class T, class Alloc>
	template<class InputIterator>
	vector<T, Alloc>::vector(InputIterator first, InputIterator last) {

		_vector_aux(first, last, typename std::is_integral<InputIterator>::type());
	}

	template<class T, class Alloc>
	vector<T, Alloc>::vector(const vector<T, Alloc>& v) {

		_allocate_and_copy(v._start, v._finsh);
	}

	template<class T, class Alloc>
	vector<T, Alloc>::vector(vector<T, Alloc>&& v) {

		_destory_and_deallocate();
		_start = v._start;
		_finsh = v._finsh;
		_end_of_storage = v._end_of_storage;
		v._start = v._end_of_storage = v._finsh = 0;
	}

	template<class T, class Alloc>
	vector<T, Alloc>::~vector() {

		_destory_and_deallocate();
	}

	template<class T, class Alloc>
	vector<T, Alloc>& vector<T, Alloc>::operator=(const vector<T, Alloc>& v) {

		if (this != &v) _allocate_and_copy(v.begin(), v.end());
		
		return *this;
	};

	template<class T, class Alloc>
	vector<T, Alloc>& vector<T, Alloc>::operator=(vector<T, Alloc>&& v) {

		if (this != &v) {
			_destory_and_deallocate();
			_start = v._start;
			_finsh = v._finsh;
			_end_of_storage = v._end_of_storage;
			v._start = v._end_of_storage = v._finsh = 0;
		}

		return *this;
	}

	template<class T, class Alloc>
	void vector<T, Alloc>::push_back(const value_type& value) {

		insert(end(), value);
	}


	template<class T, class Alloc>
	void vector<T, Alloc>::pop_back() {

		assert(capacity() != (difference_type)0);
		_finsh--;
		dataAllocator::destroy(_finsh);
	}

	//iterator insert(iterator, const value_type&);
	template<class T, class Alloc>
	typename vector<T, Alloc>::iterator
		vector<T, Alloc>::insert(iterator position, const value_type& value) {

		difference_type index = position - _start;
		insert(position, 1, value);
		return _start + index;
	}
	//void insert(iterator, size_type, const value_type&);
	template<class T, class Alloc>
	typename vector<T, Alloc>::iterator vector<T, Alloc>::insert(iterator position, size_type n, const value_type& value) {
		
		return _insert_aux(position, n, value, typename std::is_integral<size_type>::type());
	}

	//template<class InputIterator>
	//void insert(iterator, InputIterator, InputIterator);
	template<class T, class Alloc>
	template<class InputIterator>
	typename vector<T, Alloc>::iterator vector<T, Alloc>::insert(iterator position, InputIterator first, InputIterator last) {
		
		return _insert_aux(position, first, last, typename std::is_integral<InputIterator>::type());
	}

	template<class T, class Alloc>
	bool vector<T, Alloc>::operator==(const vector<T, Alloc>& v) {
		
		if (size() != v.size()) return false;

		auto s1 = _start;
		auto s2 = v._start;
		for (; s1 != _finsh && s2 != v._finsh; s1++, s2++) {
			if (*s1 != *s2) return false;
		}

		return true;
	}

	template<class T, class Alloc>
	bool vector<T, Alloc>::operator!=(const vector<T, Alloc>& v) {

		return !(*this == v);
	}

	template<class T, class Alloc>
	bool operator==(const vector<T, Alloc>& v1, const vector<T, Alloc>& v2) {

		return v1.operator==(v2);
	}

	template<class T, class Alloc>
	bool operator!=(const vector<T, Alloc>& v1, const vector<T, Alloc>& v2) {

		return !(v1 == v2);
	}
	//void erase(iterator);
	template<class T, class Alloc>
	typename vector<T, Alloc>::iterator
		vector<T, Alloc>::erase(iterator position) {

		return erase(position, position + 1);
	}

	//void erase(iterator, iterator);
	template<class T, class Alloc>
	typename vector<T, Alloc>::iterator
		vector<T, Alloc>::erase(iterator first, iterator last) {

		difference_type erase_dis = last - first;
		assert(erase_dis >= 0);

		/*MySTL::uninitialized_copy(last, _finsh, first);*/
		std::copy(last, _finsh, first);
		dataAllocator::destroy(_finsh - erase_dis, _finsh);
		_finsh = _finsh - erase_dis;

		return first;
	}

	//void clear();
	template<class T, class Alloc>
	void vector<T, Alloc>::clear() {//将所有元素析构

		dataAllocator::destroy(_start, _finsh);
		_finsh = _start;
	}

	//void swap(vector&);
	template<class T, class Alloc>
	void vector<T, Alloc>::swap(vector<T, Alloc>& v) {

		iterator _temp_start = _start;
		iterator _temp_finsh = _finsh;
		iterator _temp_end_of_storage = _end_of_storage;
		_start = v._start;
		_finsh = v._finsh;
		_end_of_storage = v._end_of_storage;
		v._start = _temp_start;
		v._finsh = _temp_finsh;
		v._end_of_storage = _temp_end_of_storage;
	}

	//void shrink_to_fit();//去掉预留空间
	template<class T, class Alloc>
	void vector<T, Alloc>::shrink_to_fit() {//重新分配空间
		iterator new_start = dataAllocator::allocate(size());
		iterator new_finsh = MySTL::uninitialized_copy(_start, _finsh, new_start);
		_destory_and_deallocate();
		_start = new_start;
		_end_of_storage = _finsh = new_finsh;
	}

	//void reserve(size_type);//改变容量
	template<class T, class Alloc>
	void vector<T, Alloc>::reserve(size_type cap) {

		if (cap <= capacity())return;
		difference_type new_cap = cap;
		iterator new_start = dataAllocator::allocate(new_cap);
		iterator new_finsh = MySTL::uninitialized_copy(_start, _finsh, new_start);
		_destory_and_deallocate();
		_start = new_start;
		_finsh = new_finsh;
		_end_of_storage = new_start + new_cap;
	}

	//void resize(size_type n, value_type v = value_type());
	template<class T, class Alloc>
	void vector<T, Alloc>::resize(size_type n, value_type value) {

		if (n == size()) return;

		if (n < size()) {//n小于当前vector大小,n==size()时不用处理
			dataAllocator::destroy(_start + n, _finsh);
			_finsh = _start + n;
		}
		else if (n <= capacity()) {
			_finsh = MySTL::uninitialized_fill_n(_finsh, n - size(), value);
		}
		else {
			difference_type old_cap = capacity();
			difference_type new_cap = (old_cap == 0) ? n : old_cap + ((old_cap > n) ? old_cap : n);
			iterator new_start = dataAllocator::allocate(new_cap);
			iterator new_finsh = MySTL::uninitialized_copy(_start, _finsh, new_start);
			new_finsh = MySTL::uninitialized_fill_n(new_finsh, n - size(), value);
			_destory_and_deallocate();
			_start = new_start;
			_finsh = new_finsh;
			_end_of_storage = new_start + new_cap;
		}
	}

}//end of namespace MySTL

#endif // !_VECTOR_IMP_H_2023_1_6_
