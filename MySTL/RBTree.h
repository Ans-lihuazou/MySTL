#ifndef _RB_TREE_H_
#define _EB_TREE_H_

#include "Iterator.h"
#include "Allocator.h"
#include "Algorithm.h"

namespace MySTL {

	namespace MyRBTree {

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

			bool operator==(const node& rhs) {

				if (parent == rhs.parent && left == rhs.left && right == rhs.right &&
					color == rhs.color && value == rhs.value) {
					return true;
				}

				return false;
			}
			bool operator!=(const node& rhs) { return !(*this).operator==(rhs); }
			
		};

		template<class T>
		class rb_tree_iterator :public Iterator<bidirectional_iterator_tag, T> {
		private:

			typedef typename rb_tree_node::node_ptr node_ptr;
			typedef typename rb_tree_node::node node;

		public:

			typedef typename rb_tree_iterator<T> iterator;

			rb_tree_iterator() :rb_node() {};
			explicit rb_tree_iterator(const node& cNode):rb_node(cNode) {};
			rb_tree_iterator(const iterator& iter) :rb_node(iter.rb_node) {};

			reference operator*() { return rb_node.value; };
			pointer operator->() { return &(operator*()); };

			node MAX(node_ptr root) {
				while (root->right != nullptr) {
					root = root->right;
				}
				return *root;
			}

			node MIN(node_ptr root) {
				while (root->left != nullptr) {
					root = root->left;
				}
				return *root;
			}

			iterator& operator++() {

				//为end()节点
				if (rb_node.color == red && rb_node.parent->parent == rb_node) {
					throw("error::operator++");
				}

				//当节点具有右子树，他的后继节点为右子树的最左节点
				if (rb_node.right != nullptr) {
					rb_node = MIN(rb_node.right);
				}
				//当节点不具有右子树，其后继节点为从下往上找到的第一个符合此条件的节点:目标节点在他的左子树
				else {
					node nParent = rb_node.parent;
					while (rb_node.right == rb_node) {
						rb_node = nParent;
						nParent = nParent.parent;
					}
					//如果目标节点不是中序遍历的最后节点，则nParent则为后继节点
					//反之后继节点为end节点
					//当root无右子树时,end()->right = root
					if (rb_node.right != nParent) {
						rb_node = nParent;
					}
				}
				return *this;
			};

			iterator operator++(int) {
				iterator result = *this;
				operator++();
				return result;
			}
			
			iterator& operator--() {
				
				//为end节点
				if (rb_node.color == red && rb_node.parent->parent == rb_node) {
					rb_node = rb_node.right;
				}
				//如果存在左子树
				else if (rb_node.left != nullptr) {
					rb_node = MAX(rb_node.left);
				}
				//++或--两端都存在边界，以end()为右边界，左边界越界置死循环
				else {
					node nParent = rb_node.parent;
					while (rb_node == nParent.left) {
						rb_node = nParent;
						nParent = nParent.parent;
					}
					rb_node = nParent;
				}
				return *this;
			}

			iterator operator--(int) {
				iterator result = *this;
				operator--();
				return result;
			}

			bool operator == (const iterator& iter) { return iter->rb_node == rb_node; }
			bool operator !=(const iterator& iter) { return iter->rb_node != rb_node; }

		protected:

			node rb_node;
		};

	}//end of namespace MyRBTree

	template<class T, class Alloc = allocator<T>, class Compare = MySTL::less<T>>
	class rb_tree {
	private:
		typedef typename MyRBTree::rb_tree_node::node_ptr node_ptr;
		typedef typename MyRBTree::rb_tree_node::node node;

	public:
		typedef	typename T				value_type;
		typedef typename T*				pointer;
		typedef typename const T*		const_pointer;
		typedef typename T&				reference;
		typedef typename const T&		const_reference;
		typedef typename size_t			size_type;
		typedef typename ptrdiff_t		difference_type;
		
		typedef typename MyRBTree::rb_tree_iterator<T> iterator;
		typedef typename MyRBTree::rb_tree_iterator<const T> const_iterator;

		rb_tree(const Compare& c = Compare());
		explicit rb_tree(const node& rhs, const Compare& c = Compare());
		template<class InputIterator>
		rb_tree(InputIterator first, InputIterator last, const Compare& c = Compare());
		rb_tree(const rb_tree& rhs);
		rb_tree(rb_tree&&);


	private:

		iterator end;
		Compare cmp;
	};



}//end of namespace MySTL

#include "RBTree.imp.h"
#endif // !_RB_TREE_H_
