#ifndef _RB_TREE_IMP_H_
#define _RB_TREE_IMP_H_

namespace MySTL {

	template<class T, class Alloc , class Compare>
	rb_tree<T, Alloc, Compare>::rb_tree(const Compare& c) {
		com = c;
	}


}//end of namespace MySTL

#endif // !_RB_TREE_IMP_H_