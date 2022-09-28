#pragma once
#ifndef _LIST_H_
#define _LIST_H_

#include "Iterator.h"
#include "Allocator.h"
#include "ReverseIterator.h"
#include "Algorithm.h"
#include <cstddef>
#include <cassert>

namespace MySTL{

	template<class T>
	class list;

	namespace MyList {
		template <class T>
		struct ListNode {
			typedef ListNode<T> list_node;

			list_node* next;
			list_node* prev;
			list<T>* belong;
			T data;

			ListNode
			(T d, list_node* n = nullptr, list_node* p = nullptr, list<T>* b = nullptr) :
				data(d), next(n), prev(p), belong(b) {};

			bool operator==(const list_node& ln) {
				return(data == ln.data && next == ln.next && prev == ln.prev, belong == ln.belong);
			}

		};//end of ListNode

		template<class T>
		class iterator_list : public Iterator<bidirectional_iterator_tag, T> {
		public:
			typedef iterator_list<T>	iterator_type;

			typedef size_t				size_type;

			typedef  typename ListNode<T>		list_node;
			typedef  typename list_node*		link_type;



			//����
			iterator_list() {}
			iterator_list(link_type n) :node(n) {};
			iterator_list(const iterator_list& iter) :node(iter.node) {};

			iterator_type operator++() {
				node = node->next;
				return *this;
			}

			iterator_type operator++(int) {
				iterator_type temp = *this;
				++(*this);
				return temp;
			}

			iterator_type operator--() {
				node = node->pre;
				return *this;
			}

			iterator_type operator--(int) {
				iterator_type temp = *this;
				--(*this);
				return temp;
			}

			list_node operator*() {
				return node->data;
			}

			list_node operator->() {
				return &(this->operator*());
			}
		private:
			//������ָ�������
			link_type node;
		};//end of iterator_list
	}//end of MyList

	template<class T>
	class list {
	private:
		typedef allocator<node> dataAllocator;
	public:
		//typedef  typename ListNode<T>		list_node;
		//typedef  typename list_node*		link_type;

		typedef	T				value_type;
		typedef T*				pointer;
		typedef const T*		const_pointer;
		typedef T&				reference;
		typedef const T&		const_referenece;
		typedef size_t			size_type;
		typedef ptrdiff_t		difference_type;

		typedef MyList::ListNode<T>				node;
		typedef node*							link_type;
		typedef MyList::iterator_list<T>		iterator;
		typedef MyList::iterator_list<const T>	const_iterator;

		typedef reverse_iterator<iterator> reverse_iter;
		typedef reverse_iterator<const iterator> const_reverse_iter;

		/*****************���죬��������ֵ*****************/
		list();
		list(size_type, const value_type& /*node->data*/);
		template<class InputIterator>
		list(InputIterator, InputIterator);
		list(const list&);
		list(list&&);
		
		~list();

		list& operator=(const list&);
		list& operator=(list&&);

		/*****************������*****************/
		iterator begin();
		const_iterator begin()const;
		const_iterator cbegin()const;

		iterator end();
		const_iterator end()const;
		const_iterator cend()const;

		reverse_iter rbegin();
		const_reverse_iter rbegin()const;
		const_reverse_iter crbegin()const;

		reverse_iter rend();
		const_reverse_iter rend()const;
		const_reverse_iter crend()const;

		/*****************����*****************/
		bool empty();
		size_type size();

		/*****************����*****************/
		reference front();
		reference back();

		/*****************Modifier*****************/
		void push_front(const value_type&);
		void pop_front();

		void push_back(const value_type&);
		void pop_back();

		// 
		iterator insert(iterator, const value_type&);
		iterator insert(iterator, size_t, const value_type&);
		template<class InputIterator>
		iterator insert(iterator, InputIterator, InputIterator);

		iterator erase(iterator);
		iterator erase(iterator, iterator);

		void swap(list&);

		void resize(size_t);

		void clear();

		/*****************Operations*****************/
		void splice(iterator position, list&);//��position֮ǰ����
		void splice(iterator position, list&, iterator index);
		void splice(iterator position, list&, iterator first, iterator last);

		void sort();//Ĭ������
		template<class Compare>
		void sort(Compare);

		void merge(list&);//�ϲ���������
		template<class Compare>//�Ƚϴ�С�ĺ���
		template void marge(list&, Compare);

		void remove(const value_type&);
		template<class isMove>//�ж��Ƿ�ɾ��
		void remove_if(isMove);

		void unique();
		template<class Compare>//�ж��Ƿ���ȵĺ���
		void unique(Compare);

		void reverse();//��ת

	private:
		//���ܺ���
		

		link_type get_node();//����һ���ڵ�ռ�
		
		void put_node(link_type p);//�ͷ�һ���ڵ�
		
		link_type create_node(const value_type& value);//���벢��ʼ��һ���ڵ�
		void destroy_node(link_type p);//�������ͷŽڵ�

		void transfer(iterator position,iterator first,iterator last);//��[first,last)�ƶ���position ֮ǰ
		
		//
		link_type node;


	};//end of list

	

}//end of MySTL

#include "List.impl.h"

#endif // !_LIST_H
