#pragma once

namespace MySTL {
	//私有功能函数
	template<class T>
	typename list<T>::link_type list<T>::get_node() {
		return dataAllocator::allocate();
	}

	template<class T>
	void list<T>::put_node(link_type p) {
		dataAllocator::deallocate(p);
	}

	template<class T>
	typename list<T>::link_type list<T>::
		create_node(const value_type& value) {
		link_type result = dataAllocator::allocate();
		dataAllocator::construct(result, link_node(value));
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
		
	}

	template<class T>
	void list<T>::_list_aux(size_type sz, const value_type& value, std::true_type) {
		for (int i = 0; i < sz; i++) {
			insert(end(), value);
		}
	}

	template<class T>
	template<class InputIterator>
	void list<T>::_list_aux(InputIterator first, InputIterator last, std::false_type) {
		for (; first != last; first++) {
			insert(end(), *first);
		}
	}

	template<class T>
	typename list<T>::iterator list<T>::_insert_aux(iterator position,size_type n, const value_type& value, std::true_type) {
		while (n--) {
			position = insert(position, value);
		}
		return position;
	}

	template<class T>
	template<class InputIterator>
	typename list<T>::iterator list<T>::_insert_aux(iterator position,InputIterator first, InputIterator last, std::false_type) {
		if (first == last) return position;
		for (last--; last != first; last--) {
			position = insert(position, *last);
		}
		return insert(position, *last);
	}

	//********************about construct********************
	template<class T>
	list<T>::list() {
		tail.node = get_node();
		//tail.node->prev = tail.node->next = tail.node;
		head.node = tail.node;
	};

	

	template<class T>
	list<T>::list(size_type sz,const value_type& value) {
		tail.node = get_node();
		//tail.node->prev = tail.node->next = tail.node;
		head.node = tail.node;
		_list_aux(sz, value,typename std::is_integral<size_type>::type());
	}

	template<class T>
	list<T>::list(const list& lst) {
		/*list();*/
		/*iterator first = lst.begin();
		iterator last = lst.end();*/
		tail.node = get_node();
		//tail.node->prev = tail.node->next = tail.node;
		head.node = tail.node;
		iterator first = lst.head;
		iterator last = lst.tail;
		for (; first != last;first=first.node->next) {
			insert(end(), *first);
		}
	}

	template<class T>
	list<T>::list(list&& lst) {
		tail.node = get_node();
		//tail.node->prev = tail.node->next = tail.node;
		head.node = tail.node;
		iterator first = lst.begin();
		iterator last = lst.end();
		for (; first != last; first++) {
			insert(end(),first.node->data);
		}
	}

	template<class T>
	template<class InputIterator>
	list<T>::list(InputIterator first, InputIterator last) {
		tail.node = get_node();
		//tail.node->prev = tail.node->next = tail.node;
		head.node = tail.node;
		_list_aux(first, last, typename std::is_integral<InputIterator>::type());
	}

	template<class T>
	list<T>::~list() {
		iterator first = begin();
		iterator last = end();
		for (; first != last;) {
			iterator temp = first++;
			destroy_node(temp.node);
		}
		put_node(first.node);
	}

	template<class T>
	list<T>& list<T>::operator=(const list& lst) {
		tail = lst.tail;
		head = lst.head;
	}
	
	template<class T>
	list<T>& list<T>::operator=(list&& lst) {
		tail = lst.tail;
		head = lst.head;
		return *this;
	}

	//********************about iterator********************
	template<class T>
	typename list<T>::iterator list<T>::begin() {
		return head;
	}

	template<class T>
	typename list<T>::const_iterator list<T>::begin()const{
		/*MyList::ListNode<const T> temp(head.node->data, (MyList::ListNode<const T>*)(head.node->next), (MyList::ListNode<const T>)(head.node->prev));
		return const_iterator(&temp);*/
		auto temp = (list* const)this;
		return changeIteratorToConstIterator(temp->head);
	}

	template<class T>
	typename list<T>::const_iterator list<T>::changeIteratorToConstIterator(iterator& it)const {
		using nodeP = MyList::ListNode<const T>*;
		//auto temp = (list<const T>*const)this;
		auto ptr = it.node;
		MyList::ListNode<const T> node(ptr->data, (nodeP)(ptr->prev), (nodeP)(ptr->next));
		return const_iterator(&node);
	}

	/*template<class T>
	typename list<T>::const_iterator list<T>::cbegin()const {
		return begin();
	}*/

	template<class T>
	typename list<T>::iterator list<T>::end() {
		return tail;
	}

	template<class T>
	typename list<T>::const_iterator list<T>::end()const {
	/*	MyList::ListNode<const T> temp(tail.node->data, (MyList::ListNode<const T>*)(tail.node->next), (MyList::ListNode<const T>)(tail.node->prev));
		return const_iterator(&temp);*/
		auto temp = (list* const)this;
		return changeIteratorToConstIterator(temp->tail);
	}

	/*template<class T>
	typename list<T>::const_iterator list<T>::cend()const {
		return end();
	}*/

	template<class T>
	typename list<T>::reverse_iter list<T>::rbegin() {
		return reverse_iter(end());
	}

	/*template<class T>
	typename list<T>::const_reverse_iter list<T>::rbegin()const {
		return const_reverse_iter(begin());
	}*/

	/*template<class T>
	typename list<T>::const_reverse_iter list<T>::crbegin()const {
		return rbegin();
	}*/

	template<class T>
	typename list<T>::reverse_iter list<T>::rend() {
		return reverse_iter(begin());
	}

	/*template<class T>
	typename list<T>::const_reverse_iter list<T>::rend()const {
		return rend();
	}

	template<class T>
	typename list<T>::const_reverse_iter list<T>::crend()const {
		return const_reverse_iter(end());
	}*/

	//********************about capacity********************
	template<class T>
	bool list<T>::empty() {
		return (tail == head);
	}

	template<class T>
	typename list<T>::size_type list<T>::size() {
		return MySTL::distance(begin(), end());
	}
	
	//********************about Element access********************
	template<class T>
	typename list<T>::reference list<T>::front() {
		assert(!empty());
		return *begin();
	}

	template<class T>
	typename list<T>::reference list<T>::back() {
		assert(!empty());
		return end().node->prev->data;
	}

	//********************about Modifier********************
	template<class T>
	void list<T>::push_front(const value_type& value) {
		insert(begin(), value);
	}

	template<class T>
	void list<T>::pop_front() {
		assert(!empty());
		erase(begin());
	}

	template<class T>
	void list<T>::push_back(const value_type& value) {
		insert(end(),value);
	}

	template<class T>
	void list<T>::pop_back() {
		assert(!empty());
		erase(end().node->prev);
	}

	//insert
	template<class T>
	typename list<T>::iterator list<T>::insert(iterator position,const value_type& value) {
		if (position == head) {
			link_type link = create_node(value);
			link->next = head.node;
			head.node->prev = link;
			head.node = link;
			return head;
		}
		/*else if (position == tail) {
			link_type link = create_node();
			tail.node->prev->next = link;
			link.node.prev = tail.node->prev;
			tail.node->prev = link;
			link->next = tail;
			return 
		}*/
		link_type link = create_node(value);
		link_type _befor_position=position.node->prev;
		_befor_position->next = link;
		link->prev = _befor_position;
		position.node->prev = link;
		link->next = position.node;
		return position.node->prev;
	}

	template<class T>
	typename list<T>::iterator list<T>::insert(iterator position, size_type n, const value_type& value) {
		return _insert_aux(position, n, value, typename std::is_integral<size_type>::type());
	}

	template<class T>
	template<class InputIterator>
	typename list<T>::iterator list<T>::insert(iterator position, InputIterator first, InputIterator last) {
		return _insert_aux(position, first, last,typename std::is_integral<InputIterator>::type());
	}

	template<class T>
	typename list<T>::iterator list<T>::erase(iterator position) {
		if (position == head) {
			iterator temp = head++;
			head.node->prev = nullptr;
			destroy_node(temp.node);
			return head;
		}
		else if (position == tail) {
			iterator temp = tail--;
			tail.node->next = nullptr;
			destroy_node(temp.node);
			return tail;
		}
		else {
			position.node->prev->next = position.node->next;
			position.node->next->prev = position.node->prev;
			iterator result = position.node->next;
			destroy_node(position.node);
			return result;
		}
	}

	template<class T>
	typename list<T>::iterator list<T>::erase(iterator first, iterator last) {
		if (first == last) return first;
		// tali->next =nullpter,head->prev = nullpter
		//first.node->prev->next = last.node;
		//last.node->prev = first.node->prev;
		for (; first != last;) {
			iterator temp = first++;
			erase(temp);
		}
		return last;
	}

	template<class T>
	void list<T>::clear() {
		erase(begin(), end());
	}

	template<class T>
	void list<T>::resize(size_type n,const value_type& value) {
		size_type now_size = size();
		if (now_size == n) return;
		else if (now_size > n) {
			while (n--) {
				link_type temp = tail.node->prev;
				tail.node->prev = temp->prev;
				destroy_node(temp.node);
			}
		}
		else {
			insert(end(), n - now_size, value);
		}
	}

	template<class T>
	void list<T>::resize(size_type n) {
		resize(n, value_type());
	}

	/*****************Operations*****************/
	template<class T>
	void list<T>::splice(iterator position, list& lst) {
		splice(position, lst,lst.begin(), lst.end());
		lst.head = lst.tail;
	}

	template<class T>
	void list<T>::splice(iterator position, list& lst, iterator index) {
		//index的位置可能是begin() or end();
		//insert(position, *index);
		iterator temp = index++;
		splice(position, lst, temp, index);
	}

	template<class T>
	void list<T>::splice(iterator position, list& lst, iterator first, iterator last) {
		if (lst.empty()||first==last) return;
		//last.node->prev = first.node->prev;
		/*if (first.node != lst.begin()) first.node->prev->next = last.node;
		else head = tail;*/
		//剪切后lst
		link_type remNode = last.node->prev;//if last==lst.end
		if (first == lst.head) {
			lst.head = last;
			lst.head.node->prev = nullptr;
		}
		else {
			first.node->prev->next = last.node;
			last.node->prev = first.node->prev;
		}

		//粘贴
		if (position == head) {
			position.node->prev = remNode;
			remNode->next = position.node;
			head.node = first.node;
			head.node->prev = nullptr;

		}
		else {
			position.node->prev->next = first.node;
			first.node->prev = position.node->prev;
			position.node->prev = remNode;
			remNode->next = position.node;
		}
			/*last.node->next = position.node;
			position.node->prev = last.node;*/
		
		
		//insert(position, first, last);
	}

	template<class T>
	void list<T>::swap(list& lst) {
		/*std::swap(begin(), lst.begin());
		std::swap(end(), lst.end());*/
		MySTL::swap(head.node, lst.head.node);
		MySTL::swap(tail.node, lst.tail.node);
	}

	template<class T>
	void swap(list<T>& lhs,list<T>& rhs) {
		lhs.swap(rhs);
	}

	template<class T>
	void list<T>::sort() {
		sort(MySTL::less<T>());
	}

	template<class T>
	template<class Compare>
	void list<T>::sort(Compare cmp) {//分治
		if (empty() || head.node->next == tail.node) return;//size==0||size==1
		list rem[64];//1+2+4+8+...2^63 = (2^64)-1
		list cur;
		int diff = 0;
		while (!empty()) {
			cur.splice(cur.begin(), *this, begin());
			int i = 0;
			while (i < diff && !rem[i].empty()) {
				rem[i].merge(cur, cmp);//size(rem[i])>=size(cur)
				cur.swap( rem[i++]);
			}
			rem[i].swap( cur);
			if (i == diff)diff++;
		}
		for (int i = 1; i < diff; i++) {
			rem[i].merge(rem[i - 1], cmp);
		}
		swap(rem[diff - 1]);
		//swap(*this, rem[diff-1]);
	}

	template<class T>
	void list<T>::merge(list& lst) {
		/*iterator first = lst.begin();
		iterator last = lst.end();*/
		merge(lst, MySTL::less<T>());
	}

	template<class T>
	template<class Compare>
	void list<T>::merge(list& lst, Compare cmp) {//if cmp is less
		iterator iter1 = begin();
		iterator iter2 = lst.begin();
		iterator sign1 = end();
		iterator sign2 = lst.end();
		while (iter1 != sign1 && iter2 != sign2) {
			if (cmp(*iter1, *iter2)) {
				iter1++;
			}
			else {
				iterator temp = iter2++;
				splice(iter1, lst, temp);
			}
		
		}
		if (iter2 != lst.end()) splice(iter1, lst, iter2, lst.end());
	}

	template<class T>
	void list<T>::remove(const value_type& value) {
		iterator first = begin();
		iterator last = end();
		for (; first != last; ) {
			if (*first == value) {
				first = erase(first);
			}
			else {
				first++;
			}
		}
	}

	template<class T>
	template<class isMove>
	void list<T>::remove_if(isMove ismove) {
		iterator first = begin();
		iterator last = end();
		for (; first != last; ) {
			if (ismove(*first)) {
				first = erase(first);
			}
			else {
				first++;
			}
		}
	}
	
	template<class T>
	void list<T>::unique() {//相邻元素相等则去除tail.node->next->next == tail.node
		if (empty() || head.node->next == tail.node) return;//size is 0 or 1
		iterator last = begin();
		iterator now = begin().node->next;
		iterator sign = end();
		for (; now != sign;now++) {
			if (*last == *now) {
				erase(last);
			}
			last = now;
		}
	}

	template<class T>
	template<class Compare>
	void list<T>::unique(Compare cmp) {//相邻元素相等则去除
		if (empty() || head.node->next == tail.node) return;//size is 0 or 1
		iterator last = begin();
		iterator now = begin().node->next;
		iterator sign = end();
		for (; now != sign; now++) {
			if (cmp(*now,*last)) {
				erase(last);
			}
			last = now;
		}
	}

	template<class T>
	void list<T>::reverse() {
		//if (head == tail) return;
		//head.node->prev = tail.node;
		//link_type new_head = tail.node->prev;
		

		iterator new_end = begin();
		iterator new_begin = end();
		for (; new_begin != new_end; ) {
			iterator temp = new_begin--;
			MySTL::swap(temp.node->next, temp.node->prev);
		}
		MySTL::swap(new_begin.node->next, new_begin.node->prev);
		link_type temp = head.node;
		head.node = tail.node->next;
		head.node->prev = nullptr;
		tail.node->prev = temp;
		tail.node->next = nullptr;
		temp->next = tail.node;
	}

	template<class T>
	bool operator==(const MySTL::list<T>& lhs, const MySTL::list<T>& rhs) {
		using iterator = MyList::iterator_list<T>;
		iterator first1 = lhs.head;
		iterator first2 = rhs.head;
		iterator last1 = lhs.tail;
		iterator last2 = rhs.tail;
		for (; first1 != last1 && first2 != last2;first1++,first2++) {
			if (*first1 != *first2) return false;
		}
		if (first1 != last1 || first2 != last2) return false;
		return true;
	}

	template<class T>
	bool operator!=(const MySTL::list<T>& lhs, const MySTL::list<T>& rhs) {
		return !(lhs==rhs);
	}

}//end of namespace
