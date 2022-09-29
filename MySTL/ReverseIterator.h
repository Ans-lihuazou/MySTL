#pragma once

#include "Iterator.h"
//反向迭代器
//rbegin,rend
namespace MySTL {

	template<class Iterator>
	class reverse_iterator {
	public:
		typedef typename IteratorTraits<Iterator>::iterator_category	iterator_category;
		typedef typename IteratorTraits<Iterator>::value_type			value_type;
		typedef typename IteratorTraits<Iterator>::pointer				pointer;
		typedef typename IteratorTraits<Iterator>::reference			reference;
		typedef typename IteratorTraits<Iterator>::difference_type		difference_type;
		typedef typename Iterator										iterator_type;
		typedef typename const pointer									const_pointer;
		typedef typename const reference								const_reference;

		reverse_iterator() : _base(0), _cur(0) {}
		explicit reverse_iterator(const Iterator& base) :_base(base) {
			Iterator t = base;
			_cur = --t;
		}
		template<class T>
		reverse_iterator(const reverse_iterator<T>& iter) {
			_base = (Iterator)iter.base();
			Iterator t = base;
			_cur = --t;
		}

		//operator
		Iterator base() { return _base; }
		reference operator*() { return (*_cur); }
		const_reference operator*() const { return(*_cur); }
		pointer operator->() { return &(*this); }
		const_pointer operator->() const { return &(*this); }

		reverse_iterator operator++() { _cur--, _base--; return *this; }//反向，所以++实际为--
		reverse_iterator operator++(int) { reverse_iterator temp = *this; ++(*this); return temp; }

		reverse_iterator operator--() { _cur++, _base++; return *this; }//反向，所以++实际为--
		reverse_iterator operator--(int) { reverse_iterator temp = *this; --(*this); return temp; }

		reference operator[](difference_type index) { return  base()[-index - 1]; }//base is end


		reverse_iterator operator+=(difference_type n) {
			_base = advanceNStep(_base, n, false, iterator_category());
			_cur = advanceNStep(_cur, n, false, iterator_category());
			return *this;
		};

		reverse_iterator operator-=(difference_type n) {
			_base = advanceNStep(_base, n, true, iterator_category());
			_cur = advanceNStep(_cur, n, true, iterator_category());
			return *this;
		};

		reverse_iterator operator+(difference_type n)const {
			reverse_iterator result = *this;
			result += n;
			return result;
		};
		reverse_iterator operator-(difference_type n)const {
			reverse_iterator result = *this;
			result -= n;
			return result;
		};

		bool operator == (const reverse_iterator<Iterator>& lhs) {
			return lhs._cur == _cur;
		}

		bool operator != (const reverse_iterator<Iterator>& lhs) {
			return lhs._cur != _cur;
		}
		

		template <class Iterator>
		friend bool operator == (const reverse_iterator<Iterator>& lhs,
			const reverse_iterator<Iterator>& rhs);

		template <class Iterator>
		friend bool operator != (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs);

		template <class Iterator>friend bool operator <
			(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs);

		template <class Iterator>
		friend bool operator <= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs);

		template <class Iterator>
		friend bool operator > (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs);

		template <class Iterator>
		friend bool operator >= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs);

		template <class Iterator>
		friend reverse_iterator<Iterator> operator + (typename reverse_iterator<Iterator>::difference_type n,
			const reverse_iterator<Iterator>& rev_it);

		template <class Iterator>
		friend typename reverse_iterator<Iterator>::difference_type operator-
			(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs);

	private:
		Iterator _base;
		Iterator _cur;

		Iterator advanceNStep(Iterator iter, difference_type n, bool flag, random_access_iterator_tag) {//可以直接跳
			n = (n < 0) ? -n : n;
			if (flag) return iter + n;
			else return iter - n;
		}

		Iterator advanceNStep(Iterator iter, difference_type n, bool flag, bidirectional_iterator_tag) {//一步一步
			n = (n < 0) ? -n : n;
			if (flag) while (n--) iter++;
			else while (n--) iter--;
			return iter;
		}
	};

	template <class Iterator>
	bool operator == (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return lhs._cur == rhs._cur;
	};

	template <class Iterator>
	bool operator != (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return lhs._cur != rhs._cur;
	};

	template <class Iterator>
	bool operator <(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return lhs._cur < rhs._cur;
	};

	template <class Iterator>
	bool operator <= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return !(lhs._cur > rhs._cur);
	};

	template <class Iterator>
	bool operator > (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return lhs._cur > rhs._cur;
	};

	template <class Iterator>
	bool operator >= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return !(lhs._cur < rhs._cur);
	};

	template <class Iterator>
	reverse_iterator<Iterator> operator + (typename reverse_iterator<Iterator>::difference_type n,
		const reverse_iterator<Iterator>& rev_it) {
		return rev_it + n;
	};

	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator>& lhs,
		const reverse_iterator<Iterator>& rhs) {
		lhs._cur - rhs._cur;
	};

}



