#ifndef _RB_TREE_H_
#define _EB_TREE_H_

#include "Iterator.h"

namespace MySTL {

	namespace MyEBTree {

		typedef typename bool color_type;
		const color_type red = false;
		const color_type black = true;

		template<class T>
		struct rb_tree_node {

			typedef typename rb_tree_node<T>* node_ptr;
			typedef typename rb_tree_node<T> node;

			node_ptr parent;
			node_ptr left;
			node_ptr right;
			color_type color;
			T value;

			rb_tree_node() :parent(nullptr), left(nullptr), right(nullptr), color(red) {};
			explicit rb_tree_node(node_ptr cParent) :parent(cParent), left(nullptr), right(nullptr), color(red) {};
			rb_tree_node(const node& cNode) :parent(cNode.parent), left(cNode.left),
				right(cNode.right), color(cNode.color), value(cNode.value) {};
		};

		template<class T>
		class rb_tree_iterator :public Iterator<bidirectional_iterator_tag, T> {
		private:

			typedef typename rb_tree_node::node_ptr node_ptr;
			typedef typename rb_tree_node<T> node;

		public:

			rb_tree_iterator() :node() {};
			explicit rb_tree_iterator(const node& cNode) {};

		private:

			node rb_node;

		};

	}//end of namespace MyRBTree

}//end of namespace MySTL

#endif // !_RB_TREE_H_
