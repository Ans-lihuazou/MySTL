#pragma once
#include "Iterator.h"
#include "TypeTraits.h"
#include "Allocator.h"
#include <cassert>

namespace MySTL {
	
	//deque_buffer_size
	size_t __deque_buffer_size(size_t n, size_t type_size) {
		if (n != 0) return n;
		if (type_size > 512) return 512 / type_size;
		return 1;
	}

	//distance 计算迭代器的距离
	//一步一步计算:InputIterator,OutputIterator,ForwardIterator,BidirectionalIterator
	template<class InputIterator>
	inline  typename InputIterator::difference_type
		_distance(InputIterator first, InputIterator last, input_iterator_tag) {
		typename InputIterator::difference_type n = 0;
		while (first != last) n++, first++;
		return n;
	}

	//直接计算:RandomAccessIterator
	template<class RandomAccessIterator>
	inline  typename RandomAccessIterator::difference_type
		_distance(RandomAccessIterator first, RandomAccessIterator last, random_access_iterator_tag) {
		typename IteratorTraits::difference_type n = last - first;
		return n;
	}

	template<class InputIterator>
	inline typename InputIterator::difference_type distance(InputIterator first, InputIterator last) {
		typedef IteratorTraits<InputIterator>::iterator_category iterator_category;
		return _distance(first, last, iterator_category());
	}



	//advance
	template<class InputIterator, class Distance>
	void _advance(InputIterator& it, Distance n, input_iterator_tag) {//单向一步一步
		assert(n >= 0);
		while (n--) ++it;
	}
	template<class BidirectionIterator, class Distance>//前后一步一步
	void _advance(BidirectionIterator& it, Distance n, bidirectional_iterator_tag) {
		if (n < 0) while (n++) --it;
		else while (n--) ++it;
	}
	template<class RandomIterator, class Distance>//随意
	void _advance(RandomIterator& it, Distance n, random_access_iterator_tag) {
		it += n;
	}
	template <class InputIterator, class Distance>
	void advance(InputIterator& it, Distance n) {
		typedef IteratorTraits<InputIterator>::iterator_category iterator_category;
		_advance(it, n, iterator_category());
	}

	//fill
	template<class ForwardIterator, class T>
	void fill(ForwardIterator first, ForwardIterator last, const T& value) {
		for (; first != last; ++first)
			*first = value;
	}

	inline void fill(char* first, char* last, const char& value) {
		memset(first, static_cast<unsigned char>(value), last - first);
	}

	inline void fill(wchar_t* first, wchar_t* last, const wchar_t& value) {
		memset(first, static_cast<unsigned char>(value), (last - first) * sizeof(wchar_t));
	}
	//********* [fill_n] ********************
	//********* [Algorithm Complexity: O(N)] ****************
	template<class OutputIterator, class Size, class T>
	OutputIterator fill_n(OutputIterator first, Size n, const T& value) {
		//std::cout << "1 " << n<<" "<<value << std::endl;
		for (; n > 0; --n, ++first) {
			*first = value;
		}

		/*std::cout << "end 1\n";*/
		return first;
	}

	template<class Size>
	char* fill_n(char* first, Size n, const char& value) {
		/*std::cout << "2\n";*/
		memset(first, static_cast<unsigned char>(value), n);
		return first + n;
	}

	template<class Size>
	wchar_t* fill_n(wchar_t* first, Size n, const wchar_t& value) {
		//std::cout << "3\n";
		memset(first, static_cast<unsigned char>(value), n * sizeof(wchar_t));
		return first + n;
	}

	template<class InputIterator, class OutputIterator>
	OutputIterator __copy(InputIterator first, InputIterator last, OutputIterator result, _true_type) {
		auto dist = distance(first, last);
		memcpy(result, first, sizeof(*first) * dist);
		advance(result, dist);
		return result;
	}
	template<class InputIterator, class OutputIterator>
	OutputIterator __copy(InputIterator first, InputIterator last, OutputIterator result, _false_type) {
		while (first != last) {
			*result = *first;
			++result;
			++first;
		}
		return result;
	}
	template<class InputIterator, class OutputIterator, class T>
	OutputIterator _copy(InputIterator first, InputIterator last, OutputIterator result, T*) {
		typedef typename MySTL::_type_traits<T>::is_POD_type is_pod;
		return __copy(first, last, result, is_pod());
	}

	template <class InputIterator, class OutputIterator>
	OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result) {
		return _copy(first, last, result, value_type(first));
	}

	template<>
	inline char* copy(char* first, char* last, char* result) {
		auto dist = last - first;
		memcpy(result, first, sizeof(*first) * dist);
		return result + dist;
	}

	template<>
	inline wchar_t* copy(wchar_t* first, wchar_t* last, wchar_t* result) {
		auto dist = last - first;

		memcpy(result, first, sizeof(*first) * dist);
		return result + dist;
	}

	//less
	template<class T>
	struct less {

		bool operator()(const T& x, const T& y) {
			return x < y;
		}
	};

	//greater
	template<class T>
	struct greater {

		bool operator()(const T& x, const T& y) {
			return x > y;
		}
	};

}