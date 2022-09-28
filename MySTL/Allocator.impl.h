#pragma once

namespace MySTL {
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
		_Construct_::construct(p, t);
	}

	template<class T>
	void allocator<T>::construct(T* p, const T& v) {
		_Construct_::construct(p, v);
	}

	template<class T>
	void allocator<T>::destroy(T* p) {
		_Construct_::destory(p);
	}

	template<class T>
	void allocator<T>::destroy(T* first, T* last) {
		_Construct_::destory(first, last);
	}
}