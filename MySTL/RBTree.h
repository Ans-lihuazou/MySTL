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

				//Ϊend()�ڵ�
				if (rb_node.color == red && rb_node.parent->parent == rb_node) {
					throw("error::operator++");
				}

				//���ڵ���������������ĺ�̽ڵ�Ϊ������������ڵ�
				if (rb_node.right != nullptr) {
					rb_node = MIN(rb_node.right);
				}
				//���ڵ㲻���������������̽ڵ�Ϊ���������ҵ��ĵ�һ�����ϴ������Ľڵ�:Ŀ��ڵ�������������
				else {
					node nParent = rb_node.parent;
					while (rb_node.right == rb_node) {
						rb_node = nParent;
						nParent = nParent.parent;
					}
					//���Ŀ��ڵ㲻��������������ڵ㣬��nParent��Ϊ��̽ڵ�
					//��֮��̽ڵ�Ϊend�ڵ�
					//��root��������ʱ,end()->right = root
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
				
				//Ϊend�ڵ�
				if (rb_node.color == red && rb_node.parent->parent == rb_node) {
					rb_node = rb_node.right;
				}
				//�������������
				else if (rb_node.left != nullptr) {
					rb_node = MAX(rb_node.left);
				}
				//++��--���˶����ڱ߽磬��end()Ϊ�ұ߽磬��߽�Խ������ѭ��
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
