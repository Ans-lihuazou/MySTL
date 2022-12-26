 #ifndef _DEQUE_H_
#define _DEQUE_H_

#include "Iterator.h"
#include "Algorithm.h"
#include "Allocator.h"
#include "ReverseIterator.h"
#include "Utlity.h"


namespace MySTL {
	
	template<class T, class Alloc = allocator<T>>
	class deque;
	namespace MyDeque {
		template<class T>
		class iterator_deque :public Iterator<bidirectional_iterator_tag, T> {
		private:
			template<class T, class Alloc>
			friend class MySTL::deque;
		public:
			typedef const MySTL::deque<T>* containerPtr;
			typedef size_t size_type;
			typedef iterator_deque<T> iterator;
			typedef Iterator<bidirectional_iterator_tag, T>::pointer pointer;
			typedef Iterator<bidirectional_iterator_tag, T>::reference reference;
			typedef Iterator<bidirectional_iterator_tag, T>::difference_type difference_type;
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
				return *this;
			};

			reference operator*() { return *_cur; }
			const reference operator*() const { return *_cur; }
			pointer operator->() { return &(this->operator*()); }
			const pointer operator->()const { return &(this->operator*()); }


			bool operator==(const iterator& iter)const {
				return (_map_index == iter._map_index) && (_cur == iter._cur) && (_container == iter._container);
			}

			bool operator!=(const iterator& iter)const {
				return !(*this == iter);
			}

			iterator operator++() {
				if (_cur != _get_tail(_map_index)) {
					_cur++;
				}
				else if(_map_index+1< _container->map_size) {//进入下一空间块
					_map_index++;
					_cur = _get_head(_map_index);
				}
				else {
					_map_index = _container->map_size;
					_cur = _get_head(_map_index);
				}
				return *this;
			}
			iterator operator++(int) {
				iterator result = *this;
				++(*this);
				return result;
			}

			iterator operator--() {
				if (_cur != _get_head(_map_index)) {
					_cur--;
				}
				else if(_map_index>=1) {
					_map_index--;
					_cur = _get_tail(_map_index);
				}
				else {
					_map_index = 0;
					_cur = _get_head(_map_index);
				}
				return *this;
			}
			iterator operator--(int) {
				iterator temp = *this;
				--(*this);
				return temp;
			}

			void swap(iterator& iter) {
				MySTL::swap(_map_index, iter._map_index);
				MySTL::swap(_cur, iter._cur);
				//_container无法交换，设计有误
			}

			template<class T>
			friend iterator_deque<T> operator+ (const iterator_deque<T>& it, typename iterator_deque<T>::difference_type n);
			template<class T>
			friend iterator_deque<T> operator+ (typename iterator_deque<T>::difference_type n, const iterator_deque<T>& it);
			template<class T>
			friend iterator_deque<T> operator- (const iterator_deque<T>& it, typename iterator_deque<T>::difference_type n);
			template<class T>
			friend iterator_deque<T> operator- (typename iterator_deque<T>::difference_type n, const iterator_deque<T>& it);
			template<class T>
			friend typename iterator_deque<T>::difference_type operator - (const iterator_deque<T>& it1, const iterator_deque<T>& it2);
			template<class T>
			friend void swap(iterator_deque<T>&, iterator_deque<T>&);

		private:
			//typedef typename pointer* map_pointer;
			
			size_type _map_index;//所属的连续块状空间编号
			pointer _cur;//指向的数据
			containerPtr _container;//所属的deque


			pointer _get_head(size_type n) const {
				return _container->map[n];
			};
			pointer _get_tail(size_type n) const {
				return _container->map[n] + _get_buffer_size();
			};
			size_type _get_buffer_size() const { return _container->_get_buffer_size(); };

		};//end of class iterator
	}//end of namespace mydeque


	template<class T,class Alloc>
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

		typedef MyDeque::iterator_deque<T>			iterator;
		typedef MyDeque::iterator_deque<const T>	const_iterator;
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
		/*const_iterator begin()const;*/
		iterator begin()const;//没有特化const T类型的迭代器
		const_iterator cbegin()const;

		iterator end();
		/*const_iterator end()const;*/
		iterator end()const;
		const_iterator cend()const;

		reverse rbegin();
		reverse rend();

		//capacity
		size_type size();
		bool empty();
		//void resize(size_type,const value_type&);
		//void shrink_to_fit();

		//Element access
		reference front();
		reference back();
		reference operator[](size_type);
		const_reference front()const;
		const_reference back()const;
		const_reference operator[](size_type)const;
		reference at(size_type);

		//Modifiers:
		//void assign(size_type, const value_type&);
		//template<class InputIterator>
		//void assign(InputIterator first, InputIterator last);

		void push_back(const value_type&);
		void push_front(const value_type&);
		void pop_back();
		void pop_front();

		//iterator insert(iterator, const value_type&);
		//iterator insert(iterator, size_type, const value_type&);
		//template<class InputIterator>
		//iterator insert(iterator, InputIterator, InputIterator);

		//iterator erase(iterator);
		//iterator erase(iterator, iterator);

		void swap(deque&);

		void clear();


		//friend
		template<class T, class Alloc>
		friend void swap(deque<T, Alloc>&, deque<T, Alloc>&);
		template<class T, class Alloc>
		friend bool operator==(const deque<T, Alloc>&, const deque<T, Alloc>&);
		template<class T, class Alloc>
		friend bool operator!=(const deque<T, Alloc>&, const deque<T, Alloc>&);

	private:
		typedef pointer* map_pointer;
		typedef allocator<value_type> dataAllocator;
		typedef allocator<pointer> mapAllocator;
		
		enum {BUFFERSIZE=64};//一个空间快可以容纳的数据个数

		//有效范围为[1,map_size-1]
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
		map_pointer _allocate_map(size_type);
		pointer _allocate_block();
		void _reallocate_and_copy();

		size_type _get_buffer_size()const;
		size_type _get_new_size(size_type);
		const_iterator changeIteratorToConstIterator(iterator&)const;

		bool _back_is_full();
		bool _head_is_full();
	};



}

#include "Deque.impl.h"

#endif // !_DEQUE_H_
