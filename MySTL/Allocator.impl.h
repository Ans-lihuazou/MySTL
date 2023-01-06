#ifndef _ALLOCATOR_IMPL_H_
#define _ALLOCATOR_IMPL_H_

namespace MySTL {

	template<class T>
	inline void _construct(T* p, const T& v) {
		new(p)T(v);
	}

	template<class T>
	inline void _destory(T* p) {
		p->~T();
	}

	template<class ForwardIterator>
	inline void _destory_aux(ForwardIterator first, ForwardIterator last, _true_type) {}

	template<class ForwardIterator>
	inline void _destory_aux(ForwardIterator first, ForwardIterator last, _false_type) {
		for (; first != last; first++) _destory(&*first);
	}

	//template<class ForwardIterator>
	//inline typename _type_tarits<ForwardIterator>::is_POD_type is_Pod(ForwardIterator iter) {
	//	typename _type_tarits<ForwardIterator>::is_POD_type POD_type;
	//	return POD_type();
	//}

	template<class ForwardIterator>
	inline void _destory(ForwardIterator first, ForwardIterator last) {
		typedef typename
			_type_traits<typename IteratorTraits<ForwardIterator>::value_type>::
			is_POD_type POD_type;
		_destory_aux(first, last, POD_type());
	}

	template<class T>
	T* allocator<T>::allocate() {
		return static_cast<T*> (alloc::allocate(sizeof(T)));
	};

	template<class T>
	T* allocator<T>::allocate(size_t n) {
		if (0 == n) return 0;
		return static_cast<T*>(alloc::allocate(n*sizeof(T)));
	}

	template<class T>
	void allocator<T>::deallocate(T* p) {
		alloc::deallocate(p, sizeof(T));
	}

	template<class T>
	void allocator<T>::deallocate(T* p, size_t n) {
		if (0 == n) return;
		alloc::deallocate(p, sizeof(T) * n);
	}

	template<class T>
	void allocator<T>::construct(T* p) {
		T t();
		_construct(p, t);
	}

	template<class T>
	void allocator<T>::construct(T* p, const T& v) {
		_construct(p, v);
	}

	template<class T>
	void allocator<T>::destroy(T* p) {
		_destory(p);
	}

	template<class T>
	void allocator<T>::destroy(T* first, T* last) {
		_destory(first, last);
	}
}

#endif // !_ALLOCATOR_IMPL_H_