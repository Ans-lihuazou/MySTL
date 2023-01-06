 
#ifndef _LIST_H_
#define _LIST_H_

#include "Iterator.h"
#include "Allocator.h"
#include "ReverseIterator.h"
#include "Algorithm.h"
#include "Utlity.h"
#include <cstddef>
#include <cassert>
#include <type_traits>

namespace MySTL{

	template<class T>
	class list;

	namespace MyList {
		template <class T>
		struct ListNode {
			typedef ListNode<T> list_node;

			list_node* next;
			list_node* prev;
			T data;

			ListNode
			(T d, list_node* n = nullptr, list_node* p = nullptr) :
				data(d), next(n), prev(p) {};

			bool operator==(const list_node& ln) {
				return(data == ln.data && next == ln.next && prev == ln.prev);
			}

		};//end of ListNode

		template<class T>
		class iterator_list : public Iterator<bidirectional_iterator_tag, T> {
		public:
			typedef iterator_list<T>	iterator_type;
			typedef size_t				size_type;
			typedef ListNode<T>			list_node;
			typedef ListNode<T>*		link_type;

			//构造
			iterator_list():node(0) {};
			iterator_list(link_type n) :node(n) {};
			iterator_list(const iterator_list& iter) :node(iter.node) {};

			iterator_type& operator++() {

				node = node->next;
				return *this;
			}

			iterator_type operator++(int) {

				iterator_type temp = *this;
				++(*this);
				return temp;
			}

			iterator_type& operator--() {

				node = node->prev;
				return *this;
			}

			iterator_type operator--(int) {

				iterator_type temp = *this;
				--(*this);
				return temp;
			}

			T& operator*() {

				return node->data;
			}

			T* operator->() {

				return &(this->operator*());
			}

			bool operator==( const iterator_type& rhs) {

				return node == rhs.node;
			}

			bool operator!=(const iterator_type& rhs) {

				return !(this->operator==(rhs));
			}
			template<class T>
			friend bool operator ==(const iterator_list<T>& lhs, const iterator_list<T>& rhs);
			template<class T>
			friend bool operator !=(const iterator_list<T>& lhs, const iterator_list<T>& rhs);
			//迭代器指向的数据
			link_type node;//public
		};//end of iterator_list

		template<class T>
		bool operator ==(const iterator_list<T>& lhs, const iterator_list<T>& rhs) {
			return lhs.node == rhs.node;
		};
		template<class T>
		bool operator !=(const const iterator_list<T>& lhs, const iterator_list<T>& rhs) {
			return !(lhs.node == rhs.node);
		};

	}//end of MyList

	template<class T>
	class list {
	private:
		typedef allocator< MyList::ListNode<T> > dataAllocator;
	public:
		//typedef  typename ListNode<T>		list_node;
		//typedef  typename list_node*		link_type;

		typedef	T				value_type;
		typedef T*				pointer;
		typedef const T*		const_pointer;
		typedef T&				reference;
		typedef const T&		const_reference;
		typedef size_t			size_type;
		typedef ptrdiff_t		difference_type;

		typedef MyList::ListNode<T>				link_node;
		typedef MyList::ListNode<T>*			link_type;
		typedef MyList::iterator_list<T>		iterator;
		typedef MyList::iterator_list<const T>	const_iterator;

		typedef reverse_iterator<iterator> reverse_iter;
		typedef reverse_iterator<const iterator> const_reverse_iter;

		/*****************构造，析构，赋值*****************/
		list();
		explicit list(size_type, const value_type& /*node->data*/);
		template<class InputIterator>
		list(InputIterator, InputIterator);
		list(const list&);
		list(list&&);
		
		~list();

		list& operator=(const list&);
		list& operator=(list&&);

		/*****************迭代器*****************/
		iterator begin();
		const_iterator begin()const;
		const_iterator cbegin()const;

		iterator end();
		const_iterator end()const;
		const_iterator cend()const;

		reverse_iter rbegin();
		//const_reverse_iter rbegin()const;
		//const_reverse_iter crbegin()const;

		reverse_iter rend();
		//const_reverse_iter rend()const;
		//const_reverse_iter crend()const;

		/*****************容量*****************/
		bool empty();
		size_type size();

		/*****************访问*****************/
		reference front();
		reference back();

		/*****************Modifier*****************/
		void push_front(const value_type&);
		void pop_front();

		void push_back(const value_type&);
		void pop_back();

		// 
		iterator insert(iterator, const value_type&);
		iterator insert(iterator, size_type, const value_type&);
		template<class InputIterator>
		iterator insert(iterator, InputIterator, InputIterator);

		iterator erase(iterator);
		iterator erase(iterator, iterator);

		void swap(list&);

		void resize(size_type);
		void resize(size_type,const value_type&);

		void clear();

		/*****************Operations*****************/
		void splice(iterator position, list&);//在position之前插入
		void splice(iterator position, list&, iterator index);
		void splice(iterator position, list&, iterator first, iterator last);

		void sort();//默认排序
		template<class Compare>
		void sort(Compare);

		void merge(list&);//合并有序序列
		template<class Compare>//比较大小的函数
		void merge(list&, Compare);

		void remove(const value_type&);
		template<class isMove>//判断是否删除
		void remove_if(isMove);

		void unique();
		template<class Compare>//判断是否相等的函数
		void unique(Compare);

		void reverse();//反转

		template<class T>
		friend void swap(list<T>&, list<T>&);
		template <class T>
		friend bool operator== (const list<T>& lhs, const list<T>& rhs);
		template <class T>
		friend bool operator!= (const list<T>& lhs, const list<T>& rhs);

	private:
		//功能函数
		void _list_aux(size_type, const value_type&,std::true_type);

		template<class InputIterator>
		void _list_aux(InputIterator, InputIterator, std::false_type);

		iterator _insert_aux(iterator,size_type, const value_type&, std::true_type);

		template<class InputIterator>
		iterator _insert_aux(iterator,InputIterator, InputIterator, std::false_type);

		link_type get_node();//申请一个节点空间
		
		void put_node(link_type p);//释放一个节点
		
		link_type create_node(const value_type& value);//申请并初始化一个节点
		void destroy_node(link_type p);//析构并释放节点

		void transfer(iterator position,iterator first,iterator last);//将[first,last)移动到position 之前

		const_iterator changeIteratorToConstIterator(iterator&)const;
		
		//
		iterator tail;
		iterator head;


	};//end of list

	

}//end of MySTL

#include "List.impl.h"

#endif // !_LIST_H
