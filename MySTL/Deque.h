#pragma once

#ifndef _DEQUE_H_
#define _DEQUE_H_

#include "Iterator.h"
#include "Algorithm.h"
#include "Allocator.h"
#include "ReverseIterator.h"
#include "Utlity.h"

#include <cstddef>

namespace MySTL {
	
	template<class T, class Alloc = allocator<T>>
	class deque;
	namespace MyDeque {
		template<class T>
		class iterator_deque :public Iterator<bidirectional_iterator_tag, T> {
		public:
			typedef size_t size_type;
			typedef iterator_deque<T> iterator;
			typedef Iterator::pointer pointer;
			//construct
			iterator_deque() :_map_index(-1), _cur(0), _container(0) {};
			iterator_deque(size_type index, pointer value, containerPtr container) :
				_map_index(index), _cur(value), _container(container) {};
			iterator_deque(const iterator_deque& iter) :
				_map_index(iter._map_index), _cur(iter._cur), _container(iter._container) {};
			iterator& operator=(const iterator_deque& iter) {
				if (&iter == this) return *this;
				_map_index = iter._map_index;
				_cur = iter._cur;
				_container = iter._container;
			};

			reference operator*() { return *cur; }
			const reference operator*() const { return *cur; }
			pointer operator->() { return &(this->operator*()); }
			const pointer operator->()const { return &(this->operator*()); }


			static size_type buffer_size() {
				return __deque_buffer_size(BufSize, sizeof(T));
			}

			iterator operator++() {
				if (_cur != _get_tail(_map_index)) {
					_cur++;
				}
				else{//进入下一空间块
					_map_index++;
					_cur = _get_head(_map_index);
				}
				return *this;
			}
			iterator operator++(int) {
				iterator result = *this;
				++(*this);
				return temp;
			}

			iterator operator--() {
				if (_cur != _get_head()) {
					_cur--;
				}
				else {
					_map_index--;
					_cur = _get_head(_map_index);
				}
				return *this;
			}
			iterator operator--(int) {
				iterator temp = *this;
				--(*this);
				return temp;
			}


			template<class T>
			friend iterator operator + (const iterator_deque<T>& it, typename iterator_deque<T>::difference_type n);
			template<class T>
			friend iterator operator + (typename iterator_deque<T>::difference_type n, const iterator_deque<T>& it);
			template<class T>
			friend iterator operator - (const iterator_deque<T>& it, typename iterator_deque<T>::difference_type n);
			template<class T>
			friend iterator operator - (typename iterator_deque<T>::difference_type n, const iterator_deque<T>& it);
			template<class T>
			friend typename iterator::difference_type operator - (const iterator_deque<T>& it1, const iterator_deque<T>& it2);

		private:
			//typedef typename pointer* map_pointer;
			template<class T,class Alloc>
			friend class MySTL::deque;
			typedef const MySTL::deque<T>* containerPtr;
			size_type _map_index;//所属的连续块状空间编号
			pointer _cur;//指向的数据
			containerPtr _container;//所属的deque

			pointer _get_head(size_type n) {
				return _container->map[n];
			};
			pointer _get_tail(size_type n) {
				return _container->map[n]+_get_buffer_size();
			};
			size_type _get_buffer_size() { return 0; };

		};//end of class iterator
	}//end of namespace mydeque


	template<class T,class Alloc >
	class deque {
	public:
		template<class T>
		friend class ::MySTL::MyDeque::iterator_deque;
		
		typedef T			value_type;
		typedef T*			pointer;
		typedef const T*	const_pointer;
		typedef T&			reference;
		typedef const T&	const_reference;
		typedef size_t		size_type;
		typedef ptrdiff_t	difference_type;

		typedef MyDeque::iterator_deque<T, BufSize>			iterator;
		typedef MyDeque::iterator_deque<const T, BufSize>	const_iterator;
		typedef reverse_iterator<iterator> reverse;
		typedef reverse_iterator<const_iterator> const_reverse;

		//construct
		deque();
		explicit deque(size_type, const value_type& value = value_type());
		template<class InputIterator>
		deque(InputIterator fisrt, InputIterator last);
		deque(const deque&);
		deque(deque&&);

		~deque();

		deque& operator=(const deque&);
		deque& operator=(deque&&);

		//iterator
		iterator begin();
		const_iterator begin()const;
		const_iterator cbegin()const;

		iterator end();
		const_iterator end()const;
		const_iterator cend()const;

		reverse rbegin();
		reverse rend();

		//capacity
		size_type size();
		bool empty();
		void resize(size_type,const value_type&);
		void shrink_to_fit();

		//Element access
		reference front();
		reference back();
		reference operator[](size_type);
		reference at(size_type);

		//Modifiers:
		void assign(size_type, const value_type&);
		template<class InputIterator>
		void assign(InputIterator first, InputIterator last);

		void push_back(const value_type&);
		void push_front(const value_type&);
		void pop_back();
		void pop_front();

		iterator insert(iterator, const value_type&);
		iterator insert(iterator, size_type, const value_type&);
		template<class InputIterator>
		iterator insert(iterator, InputIterator, InputIterator);

		iterator erase(iterator);
		iterator erase(iterator, iterator);

		void swap(deque&);

		void clear();


	private:
		typedef pointer* map_pointer;
		typedef Alloc<T> dataAllocator;
		typedef Alloc<pointer> mapAllocator;
		
		enum {BUFFERSIZE=64};//一个空间快可以容纳的数据个数

		iterator _start;
		iterator _finsh;

		map_pointer map;
		size_type map_size;

		//构造
		void _deque_aux(size_type, const value_type&, std::true_type);
		template<class InputIterator>
		void _deque_aux(InputIterator first, InputIterator last, std::false_type);
		
		//获取空间
		void _init();//初始化
		void _reallocate_and_copy(size_type);

	};

	template<class T>
	class deque {



	};

}

#include "Deque.impl.h"

#endif // !_DEQUE_H_
