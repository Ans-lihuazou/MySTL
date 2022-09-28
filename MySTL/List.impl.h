#pragma once

namespace MySTL {
	//私有功能函数
	template<class T>
	typename list<T>::link_type list<T>::get_node() {
		return dataAllocator::allocater();
	}

	template<class T>
	void list<T>::put_node(link_type p) {
		dataAllocator::deallocate(p);
	}

	template<class T>
	typename list<T>::link_type list<T>::
		create_node(const value_type& value) {
		link_type result = dataAllocator::allocater();
		_Construct_(result->data, value);
		return result;
	}

	template<class T>
	void list<T>::destroy_node(link_type p) {
		dataAllocator::destroy(p);
		dataAllocator::deallocate(p);
	}

	template<class T>
	void list<T>::transfer(iterator position, iterator first, iterator last) {
		//first and postion->pre
		position.node->prev->next = first;
		iterator _first_befor = first.node->prev;
		first.node->prev = position.node->prev;
		//last-1  and postion
		iterator _move_end = last.node->prev;
		_move_end.node->next = position;
		position.node->prev = _move_end;
		//_first_befor ans postion
		_first_befor.node->next = last;
		last.node->prev = _first_befor;
	}

	//********************about construct********************
	template<class T>
	list<T>::list() {
		node = get_node();
		node->next = node;
		node->prev = node;
	};

	template<class T>
	list<T>::list(size_type sz,const value_type& value) {
		list();
		for (int i = 0; i < sz; i++) {
			insert(end(), create_node(value));
		}
	}

	template<class T>
	list<T>::list(const list& lst) {
		list();
		iterator first = lst.begin();
		iterator last = lst.end();
		for (; first != last;first=first.node->next) {
			insert(end(), create_node(first.node->data));
		}
	}

	template<class T>
	list<T>::list(list&& lst) {
		list();
		iterator first = lst.begin();
		iterator last = lst.end();
		for (; first != last; first = first.node->next) {
			insert(end(), create_node(first.node->data));
		}
	}

	template<class T>
	template<class InputIterator>
	list<T>::list(InputIterator first, InputIterator last) {
		list();
		for (; first != last; first = first.node->next) {
			insert(end(), create_node(first.node->data));
		}
	}

	template<class T>
	list<T>::~list() {
		iterator first = begin();
		iterator last = end();
		for (; first != last; first = first.node->next) {
			destroy_node(first);
		}
		put_node(last);
	}

	template<class T>
	list<T>& list<T>::operator=(const list& lst) {
		node = lst.node;
	}
	
	template<class T>
	list<T>& list<T>::operator=(list&& lst) {
		node = lst.node;
	}

	//********************about iterator********************
	template<class T>
	typename list<T>::iterator list<T>::begin() {
		return (*node).next;
	}

	template<class T>
	typename list<T>::const_iterator list<T>::begin()const{
		return begin();
	}

	template<class T>
	typename list<T>::const_iterator list<T>::cbegin()const {
		return begin();
	}

	template<class T>
	typename list<T>::iterator list<T>::end() {
		return node;
	}

	template<class T>
	typename list<T>::const_iterator list<T>::end()const {
		return end();
	}

	template<class T>
	typename list<T>::const_iterator list<T>::cend()const {
		return end();
	}

	template<class T>
	typename list<T>::reverse_iter list<T>::rbegin() {
		return reverse_iter(begin());
	}

	template<class T>
	typename list<T>::const_reverse_iter list<T>::rbegin()const {
		return rbegin();
	}

	template<class T>
	typename list<T>::const_reverse_iter list<T>::crbegin()const {
		return rbegin();
	}

	template<class T>
	typename list<T>::reverse_iter list<T>::rend() {
		return reverse_iter(end());
	}

	template<class T>
	typename list<T>::const_reverse_iter list<T>::rend()const {
		return rend();
	}

	template<class T>
	typename list<T>::const_reverse_iter list<T>::rend()const {
		return rend();
	}

	//********************about capacity********************
	template<class T>
	bool list<T>::empty() {
		return (node == (*node).next);
	}

	template<class T>
	typename list<T>::size_type list<T>::size() {
		return distance(begin(), end());
	}
	
	//********************about Element access********************
	template<class T>
	typename list<T>::reference list<T>::front() {
		assert(!empty());
		return begin().node->data;
	}

	template<class T>
	typename list<T>::reference list<T>::back() {
		assert(!empty());
		return end().node->prev->data;
	}

	//********************about Modifier********************
	template<class T>
	void list<T>::push_front(const value_type& value) {
		insert(begin(), create_node(value));
	}

	template<class T>
	void list<T>::pop_front() {
		assert(!empty());
		erase(begin());
	}

	template<class T>
	void list<T>::push_back(const value_type& value) {
		insert(end(), create_node(value));
	}

	template<class T>
	void list<T>::pop_back() {
		assert(!empty());
		erase(end().node->prev);
	}

	//insert
	template<class T>
	typename list<T>::iterator list<T>::insert(iterator position,const value_type& value) {
		link_type link = create_node(value);
		iterator _befor_position=position.node->prev;
		_befor_position.node->next = link;
		link->prev = _befor_position.node;
		position.node->prev = link;
		link->next = position.node;
		return link;
	}

	template<class T>
	typename list<T>::iterator list<T>::insert(iterator position, size_t n, const value_type& value) {
		if (0 == n) return position;
		while (n--) {
			position = insert(position, value);
		}
		return position;
	}

	template<class T>
	template<class InputIterator>
	typename list<T>::iterator list<T>::insert(iterator position, InputIterator first, InputIterator last) {
		if (first == last) return position;
		for (last--; last != first; last--) {
			position = insert(position, *last);
		}
		return position;
	}

	template<class T>
	typename list<T>::iterator list<T>::erase(iterator position) {
		iterator result = position.node->next;
		position.node->prev->next = result;
		result.node->prev = position.node->prev->next;
		destroy_node(position);
		return result;
	}

	template<class T>
	typename list<T>::iterator list<T>::erase(iterator first, iterator last) {
		if (first == last) return first;
		first.node->prev->next = last;
		last.node->prev = first.node->prev;
		for (; first != last;) {
			iterator temp = first;
			first++;
			destroy_node(temp);
		}
		return last;
	}

	template<class T>
	void list<T>::clear() {
		erase(begin(), end());
	}



}//end of namespace
