 #ifndef _ALLOC_H_
#define _ALLOC_H_

#include <cstdlib>
#include <iostream>
#include <new>
//空间分配
namespace MySTL {

	//template<int inst>
	class alloc {
		enum { _ALIGN = 8 };//相邻块空间大小差异
		enum { _MAX_BYTES = 128 };//最大块空间大小
		enum { _NFREELISTS = _MAX_BYTES / _ALIGN };//空间类型块数
		enum { _NCHUNKALLOC = 20 };//每个类型空间块的个数
	public:
		static void* allocate(size_t byte);//分配空间
		static void deallocate(void*, size_t);//回收空间
		static void* reallocate(void*, size_t, size_t);//重新分配

	private:
		union obj {
			union obj* free_list_link;
			char client_data[1];
		};

		static obj* volatile free_list[_NFREELISTS];
		static char* chunk_alloc(size_t byte, int& nobjs);//内存池
		static void* refill(size_t);//分配从内存池获取的空间

		static size_t ROUND_UP(size_t sz);
		static size_t FREELIST_INDEX(size_t byte);
		static char* start_free;//内存池开始
		static char* end_free;//内存池结束
		static size_t heap_size;
	};
	//#include "Alloc.impl.h"
		/*template<int inst>*/
	char* alloc::start_free = 0;

	//template<int inst>
	char* alloc::end_free = 0;

	//template<int inst>
	size_t alloc::heap_size = 0;

	//template<int inst>
	alloc::obj* volatile alloc::
		free_list[_NFREELISTS] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

	//template<int inst>
	size_t alloc::ROUND_UP(size_t byte) {
		return ((byte + _ALIGN - 1) & ~(_ALIGN - 1));
	}

	//template<int inst>
	size_t alloc::FREELIST_INDEX(size_t byte) {//定位使用那种类型大小的空间块
		return ((byte + _ALIGN - 1) / _ALIGN) - 1;//if byte is 0，returen -1
	}

	//template<int inst>
	void* alloc::allocate(size_t byte) {//分配
		if (byte > _MAX_BYTES) {
			void* result = malloc(byte);
			if (0 == result) throw (std::bad_alloc());
			return result;
		}
		obj* volatile* use_free_list = free_list + FREELIST_INDEX(byte);
		obj* result = *use_free_list;
		if (0 == result) {//所属块的空间已用尽，通过内存池获取空间
			return refill(ROUND_UP(byte));
		}
		*use_free_list = result->free_list_link;
		return result;
	}

	//template<int inst>
	void alloc::deallocate(void* p, size_t byte) {//回收
		if (byte > _MAX_BYTES) {
			free(p);
			return;
		}
		obj* volatile* use_free_list = free_list + FREELIST_INDEX(byte);
		obj* q = (obj*)p;
		q->free_list_link = *use_free_list;
		*use_free_list = q;
	}

	//template<int inst>
	void* alloc::reallocate(void* p, size_t old_sz, size_t new_sz) {//重新分配
		deallocate(p, old_sz);
		p = allocate(new_sz);
		return p;
	}

	//template<int inst>
	void* alloc::refill(size_t byte) {//分配从内存池获取的空间
		int nobjs = _NCHUNKALLOC;
		char* ret = chunk_alloc(byte, nobjs);
		if (1 == nobjs) return ret;//剩余的空间只够分配一个,如果空间不足在chunk_alloc中处理
		obj* result = (obj*)ret;
		obj* volatile* use_free_list = free_list + FREELIST_INDEX(byte);
		obj* next = (obj*)(ret + byte);
		*use_free_list = next;//调用此函数说明此种类型块已经使用完全
		//nobjs--;
		for (int i = 1;; i++) {
			obj* cur = next;
			next = (obj*)((char*)next + byte);
			if (i + 1 == nobjs) {
				cur->free_list_link = 0;
				break;
			}
			cur->free_list_link = next;
		}
		return result;
	}

	//template<int inst>
	char* alloc::chunk_alloc(size_t sz, int& nobjs) {
		size_t total_byte = sz * nobjs;
		size_t total_diff = end_free - start_free;
		size_t get_malloc_byte = total_byte * 2 + ROUND_UP(heap_size >> 4);
		//std::cout << "malloc_size: " << get_malloc_byte << std::endl;
		char* result = 0;
		if (total_diff >= total_byte) {//足够全部填充
			result = start_free;
			start_free = start_free + total_byte;
			return result;
		}
		else if (total_diff >= sz) {//只能填充部分
			nobjs = total_diff / sz;
			total_byte = nobjs * sz;
			result = start_free;
			start_free = start_free + total_byte;
			return result;
		}
		else {//(向第一级配置器,malloc)申请空间
			//if (total_diff < 8) free(start_free);
			if (total_diff >0) {//整合剩余空间
				//std::cout << total_diff << std::endl;
				obj* volatile* use_free_list = free_list + FREELIST_INDEX(total_diff);
				((obj*)start_free)->free_list_link = *use_free_list;
				(*use_free_list) = (obj*)start_free;
			}
			start_free = (char*)malloc(get_malloc_byte);
			if (!start_free) {//申请失败，从较大的块中获取空间
				obj* volatile* use_free_list;
				for (size_t i = sz + _ALIGN; i <= _MAX_BYTES; i += _ALIGN) {
					use_free_list = free_list + FREELIST_INDEX(i);
					obj* p = *use_free_list;
					if (0 != p) {//较大块还有空间
						start_free = (char*)(p);
						*use_free_list = p->free_list_link;
						end_free = start_free + i;
						return chunk_alloc(sz, nobjs);
					}
				}
				//没有空间了
				end_free = 0;
				throw std::bad_alloc();
			}
			//申请空间成功
			end_free = start_free + get_malloc_byte;
			heap_size += get_malloc_byte;
			return chunk_alloc(sz, nobjs);
		}
	}
}

#endif // !_ALLOC_H