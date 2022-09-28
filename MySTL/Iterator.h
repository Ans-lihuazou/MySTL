#pragma once

#include <cstddef>

namespace MySTL {
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag :public input_iterator_tag {};
	struct bidirectional_iterator_tag :public forward_iterator_tag {};
	struct random_access_iterator_tag :public bidirectional_iterator_tag {};

	template <class T, class Distance>
	struct input_iterator {
		typedef input_iterator_tag	iterator_category;
		typedef T					value_type;
		typedef Distance			difference_type;
		typedef T* pointer;
		typedef T& reference;
	};

	struct output_iterator {
		typedef output_iterator_tag iterator_category;
		typedef void                value_type;
		typedef void                difference_type;
		typedef void                pointer;
		typedef void                reference;
	};

	template <class T, class Distance>
	struct forward_iterator {
		typedef forward_iterator_tag	iterator_category;
		typedef T						value_type;
		typedef Distance				difference_type;
		typedef T* pointer;
		typedef T& reference;
	};

	template <class T, class Distance>
	struct bidirectional_iterator {
		typedef bidirectional_iterator_tag	iterator_category;
		typedef T							value_type;
		typedef Distance					difference_type;
		typedef T* pointer;
		typedef T& reference;
	};

	template <class T, class Distance>
	struct random_access_iterator {
		typedef random_access_iterator_tag	iterator_category;
		typedef T							value_type;
		typedef Distance					difference_type;
		typedef T* pointer;
		typedef T& reference;
	};

	template<class Category, class T, class Pointer = T*, class Reference = T&, class Difference_type = ptrdiff_t>
	struct Iterator {
		typedef Category		iterator_category;
		typedef T				value_type;
		typedef Pointer			pointer;
		typedef Reference		reference;
		typedef Difference_type difference_type;
	};


	template<class iter>
	struct IteratorTraits {
		typedef typename iter::iterator_category	iterator_category;
		typedef typename iter::value_type			value_type;
		typedef typename iter::pointer				pointer;
		typedef typename iter::reference			reference;
		typedef typename iter::difference_type		difference_type;
	};

	template<class T>
	struct IteratorTraits<T*> {
		typedef random_access_iterator_tag	iterator_category;
		typedef T							value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef ptrdiff_t					difference_type;
	};

	template<class T>
	struct IteratorTraits<const T*> {
		typedef random_access_iterator_tag	iterator_category;
		typedef T							value_type;
		typedef const T* pointer;
		typedef const T& reference;
		typedef ptrdiff_t					difference_type;
	};

	template<class Iterator>
	inline typename IteratorTraits<Iterator>::iterator_category
		iterator_category(const Iterator& It) {
		typedef typename IteratorTraits<Iterator>::iterator_category category;
		return category();
	}
	template<class Iterator>
	inline typename IteratorTraits<Iterator>::value_type*
		value_type(const Iterator& It) {
		return static_cast<typename IteratorTraits<Iterator>::value_type*>(0);
	}
	template<class Iterator>
	inline typename IteratorTraits<Iterator>::difference_type*
		difference_type(const Iterator& It) {
		return static_cast<typename IteratorTraits<Iterator>::difference_type*>(0);
	}

}