#ifndef __RBTREE_HPP__
#define __RBTREE_HPP__

#include "pair.hpp"
#include "iterators_traits.hpp"
#include "iterator_tree.hpp"

namespace ft {

#define RED		0
#define BLACK   1
#define ROOT	3
#define LEFT	4
#define RIGHT	5
#define NCHILD	6
#define NIL 	&(this->_nil)


#define BLACKC  "\033[47;30m"
#define YELLOWC	"\033[22;33m"
#define REDC  "\033[47;31m"
#define GREENC "\e[0;32m"
#define BLUEC  "\033[40;34m"
#define RESETC "\033[0m"

template<typename T>
struct _Node
{
	int				 color;
	T				 key;
	struct _Node*	 p;
	struct _Node*	 left;
	struct _Node*	 right;
};

template<typename Pointer, typename Value, class Compare = ft::less<Value> >
class RBTree
{
	public:
		
		typedef	Pointer		   				value_type;
		typedef Value						iterator_type;
		typedef	Compare						pair_compare;
		typedef	std::size_t					size_type;
		typedef _Node<value_type>			Node;
		typedef Iterator_t<iterator_type>	iterator;
		typedef Iterator_t<const iterator_type>	const_iterator;

		RBTree( const Compare& compare ) : _compare(compare) {
			_root = NIL;
			_nil.color = BLACK;
			_nil.p = _root;
			_nil.left = NIL;
			_nil.right = NIL;
			_nil.key = NULL;
			_size = 0;
			// _compare = compare;
			// std::cout << "Tree construct\n";
			// std::cout << root << " " << NIL << "\n";
		}

		~RBTree( void ) {
			delete_tree();
		}

		RBTree& operator=( RBTree& other)
		{
			if (this == &other)
				return *this;
			delete_tree();
			iterator pos = get_root();
			for (iterator it = other.begin(); it != other.end(); it++)
				pos = RB_insert(pos, it.node()->key);
			return *this;
		}

		void	all_tree() const /// iterate from begin to end
		{
			Node* node = begin().node();
			while (node != NIL)
			{
				if (node != NIL)
					std::cout << "show tree: " << node->key->first << "," << node->key->second << "\n";
				if (node->right != NIL) {
					node = min(node->right);
				}
				else {
					Node* y = node->p;
					while (y != NIL && node == y->right) {
						node = y;
						y = y->p;
					}
					node = y;
				}
			}
		}

		iterator RB_insert(iterator pos, value_type key) {
			Node *prev = NIL;
			Node *curr = pos.node();
			Node *node = init_node(key);

			while (curr != NIL)
			{
				prev = curr;
				if (_compare(*node->key, *curr->key))
					curr = curr->left;
				else
					curr = curr->right;
			}
			node->p = prev;
			if (prev == NIL) {
				_root = node;
				_nil.p = _root;
			}
			else if (_compare(*node->key, *prev->key))
				prev->left = node;
			else 
				prev->right = node;
			RB_insert_fixup(node);
			_size++;
			return node;
		}

		void RB_delete(value_type key) {
			Node *node = found_node(key);
			Node *child, *near;

			if (!node || node == NIL)
				return;
			if (node->left == NIL || node->right == NIL)
				near = node;
			else 
				near = min(node->right);
			if (near->left != NIL)
				child = near->left;
			else
				child = near->right;
			child->p = near->p;
			if (get_parent(near) != NIL) {
				if (who_i_am(near) == LEFT)
					near->p->left = child;
				else
					near->p->right = child;
			}
			else {
				_root = child;
				_nil.p = _root;
			}
			if (near != node)
				node->key = near->key;
			if (near->color == BLACK && child != NIL)
				RB_delete_fixup(child);
			_size--;
			delete near;
		}

		iterator found_node(const iterator_type& key){
			Node *end = _root;
			// std::cout << "NEW COMPAIR key = " << key.first << "\n";
			while (end != NIL) {
				if (_compare(key, *end->key))
				{
					// std::cout << (*end->key).first << " > " <<  key.first << "\n";
					end = end->left;
				}
				else if (_compare(*end->key, key))
				{
					// std::cout << (*end->key).first << " < " <<  key.first << "\n";
					end = end->right;
				}
				else
				{
					// std::cout << "copy found!\n";
					return (iterator(end));
				}
			}
			// std::cout << "copy not found\n";
			return (iterator(NIL));
		}

		iterator found_node(iterator pos, const iterator_type& key){
			Node *end = pos.node();
			while (end != NIL) {
				if (_compare(key, *end->key))
					end = end->left;
				else if (_compare(*end->key, key))
					end = end->right;
				else
					return (iterator(end));
			}
			return (iterator(NIL));
		}

		Node *max(Node *ptr) {
			if (ptr == NIL)
				return (ptr);
			Node *tmp = ptr;
			while (tmp->right != NIL)
				tmp = tmp->right;
			return (tmp);
		}

		Node *min(Node *ptr) {
			if (ptr == NIL)
				return (ptr);
			Node *tmp = ptr;
			while (tmp->left != NIL)
				tmp = tmp->left;
			return (tmp);
		}

		Node *min(Node *ptr) const {
			if (ptr == NIL)
				return (ptr);
			Node *tmp = ptr;
			while (tmp->left != NIL)
				tmp = tmp->left;
			return (tmp);
		}

		iterator get_nil( void ) {
				return (iterator(NIL));
		}

		iterator get_root( void ) {
				return (iterator(this->_root));
		}

		iterator	end() {
			return (iterator(NIL));
		}

		const_iterator	end() const {
			return (const_iterator(NIL));
		}

		iterator	begin() {
			return (iterator(min(_root)));
		}

		const_iterator	begin() const {
			return (const_iterator(min(_root)));
		}

		size_type size( void ) const {
			return _size;
		}

		bool empty( void ) {
			return _size == 0;
		}

		pair_compare value_comp() const {
			return (_compare);
		}

		size_type	count( const iterator_type& key) const {
			Node *end = _root;
			while (end != NIL) {
				if (_compare(key, *end->key))
					end = end->left;
				else if (_compare(*end->key, key))
					end = end->right;
				else
					return 1;
			}
			return 0;
		}

		void	delete_tree( void )
		{
			delete_node(_root);
			_root = NIL;
			_nil.p = _root;
		}

		// temp showcase
		void showTree( void ) {
			if (_root != NIL) {
				std::cout << GREENC << NIL << "-------TREE--------\n";
				printKey(_root, "root");
			}
			else
				std::cout << GREENC << "----TREE_EMPTY-----\n";
		}

		void showTree(Node *node ) {
			if (node != NIL) {
				std::cout << GREENC << NIL << "-------FRAGMENT--------\n";
				printKey(node, "node");
			}
		}


	private:

		// temp showcase
		void printKey(Node *tmp, std::string str) {
			if (tmp != NIL) {
				std::string col;
				if (tmp->color == RED) {
					col = "RED";
					std::cout << REDC;
				}
				else {
					col = "BLACK";
					std::cout << BLACKC;
				}
				std::cout << tmp << " " << str << " = " << tmp->key->first << "," << tmp->key->second << " color-" << col;
				if (tmp->p != NIL)
					std::cout << " parrent = " << tmp->p->key->first << "," << tmp->p->key->second;
				std::cout << RESETC << std::endl;
				printKey(tmp->left, "left");
				printKey(tmp->right, "right");
			}
		}

		void RB_insert_fixup(Node *node) {
			if (get_parent(node) == NIL) {
				node->color = BLACK;
				return ;
			}
			while (get_parent(node)->color == RED) {
				_root = found_root(node);
				_nil.p = _root;
				if (who_i_am(get_parent(node)) == LEFT) {
					if (get_uncle(node)->color == RED) {
						get_parent(node)->color = BLACK;
						get_uncle(node)->color = BLACK;
						get_grandfather(node)->color = RED;
						node = get_grandfather(node);
					}
					else {
						if (who_i_am(node) == RIGHT) {
							node = get_parent(node);
							rotate_left(node);
						}
						get_parent(node)->color = BLACK;
						get_grandfather(node)->color = RED;
						rotate_right(get_grandfather(node));
					}
				}
				else if (who_i_am(get_parent(node)) == RIGHT) {
					if (get_uncle(node)->color == RED) {
						get_parent(node)->color = BLACK;
						get_uncle(node)->color = BLACK;
						get_grandfather(node)->color = RED;
						node = get_grandfather(node);
					}
					else {
						if (who_i_am(node) == LEFT) {
							node = get_parent(node);
							rotate_right(node);
						}
						get_parent(node)->color = BLACK;
						get_grandfather(node)->color = RED;
						rotate_left(get_grandfather(node));
					}
				}
			}
			_root = found_root(node);
			_root->color = BLACK;
			_nil.p = _root;
		}

		void RB_delete_fixup(Node *node) {
			while (node != _root && node->color == BLACK) {
				if (who_i_am(node) == LEFT) {
					Node *w = node->p->right;
					if (w->color == RED) {
						w->color = BLACK;
						node->p->color = RED;
						rotate_left(node->p);
						w = node->p->right;
					}
					if (w->left->color == BLACK && w->right->color == BLACK) {
						w->color = RED;
						node = node->p;
					}
					else {
						if (w->right->color == BLACK) {
							w->left->color = BLACK;
							w->color = RED;
							rotate_right(w);
							w = node->p->right;
						}
						w->color = node->p->color;
						node->p->color = BLACK;
						w->right->color = BLACK;
						rotate_left(node->p);
						node = _root;
					}
				}
				else {
					Node *w = node->p->left;
					if (w->color == RED && w != NIL) {
						w->color = BLACK;
						node->p->color = RED;
						rotate_right(node->p);
						w = node->p->left;
					}
					if (w->right->color == BLACK && w->left->color == BLACK) {
						w->color = RED;
						node = node->p;
					}
					else {
						if (w->left->color == BLACK) {
							w->right->color = BLACK;
							w->color = RED;
							rotate_left(w);
							w = node->p->left;
						}
						w->color = node->p->color;
						node->p->color = BLACK;
						w->left->color = BLACK;
						rotate_right(node->p);
						node = _root;
					}
				}
			}
			node->color = BLACK;
			_root = found_root(node);
			_nil.p = _root;
		}

		Node *get_parent(Node *node) {
			if (node != NIL)
				return (node->p);
			return (NIL);
		}

		Node *get_grandfather(Node *node){
			if (node != NIL && get_parent(node) != NIL)
				return (node->p->p);
			return (NIL);
		}

		Node *get_uncle(Node *node) {
			Node *grand = get_grandfather(node);
			if (grand == NIL)
				return (NIL);
			if (grand->left == get_parent(node))
				return grand->right;
			else
				return grand->left;
		}

		int who_i_am(Node *node) {
			if (node != NIL && node->p == NIL)
				return (ROOT);
			if (node != NIL && node->p != NIL && node->p->left == node)
				return (LEFT);
			if (node != NIL && node->p != NIL && node->p->right == node)
				return (RIGHT);
			return (NCHILD);
		}

		Node *init_node(value_type value)
		{
			Node * node = new Node();

			node->color = RED;
			node->left = NIL;
			node->right = NIL;
			node->p = NIL;
			node->key = value;

			return (node);
		}

		void	delete_node(Node *ptr) {
			if (ptr == NIL)
				return ;
			_size--;
			delete_node(ptr->left);
			delete_node(ptr->right);
			delete ptr;
		}

		void rotate_left(Node *node) {
			if (node == NIL)
				return;
			Node *right = node->right;
			Node *left = NIL;
			left = right->left;
			if (right != NIL) 
				right->p = node->p;
			if (get_parent(node) != NIL){

				if (who_i_am(node) == RIGHT) {
					get_parent(node)->right = right;
				}
				else if (who_i_am(node) == LEFT) {
					get_parent(node)->left = right;
				}
			}
			if (left != NIL)
				left->p = node;			
			if (node != NIL) {
				node->right	= left;
				node->p = right;
			}
			right->left	= node;
		}

		void rotate_right(Node *node) {
			Node	*left = node->left;
			Node	*right = NIL;
			right = left->right; 
			if (left != NIL)
				left->p = node->p;
			if (get_parent(node) != NIL){
				if (who_i_am(node) == RIGHT) {
					get_parent(node)->right = left;
				} else if (who_i_am(node) == LEFT) {
					get_parent(node)->left = left;
				}
			}
			if (right != NIL)
				right->p = node;
			if (node != NIL) {
				node->left = right;
				node->p = left;
			}
			left->right  = node;
		}

		Node *found_root(Node *node){
			while (get_parent(node) != NIL)
				node = get_parent(node);
			return (node);
		}

	private:
		Node   			*_root;
		Node   			_nil;
		size_type		_size;
		pair_compare	_compare;
};

} // namespace ft 

#endif