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
#define NIL 	&(this->nil)


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

template<typename T>
class RBTree
{
	public:
		
		typedef	T		   					value_type;
		typedef _Node<T>					Node;
		typedef Iterator_t<value_type>		iterator;

		RBTree( void ) {
			nil.color = BLACK;
			nil.p = NIL;
			nil.left = NIL;
			nil.right = NIL;
			// nil.key = NULL;
			root = NIL;
			// std::cout << "Tree construct\n";
			// std::cout << root << " " << NIL << "\n";
		}

		~RBTree( void ) {
			delete_node(root);
		}

		void RB_insert(value_type key) {
			Node *prev = NIL;
			Node *curr = root;
			Node *node = init_node(key);

			while (curr != NIL)
			{
				prev = curr;
				if (node->key < curr->key)
					curr = curr->left;
				else
					curr = curr->right;
			}
			node->p = prev;
			if (prev == NIL)
				root = node;
			else if (node->key < prev->key)
				prev->left = node;
			else
				prev->right = node;
			RB_insert_fixup(node);
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
			else
				root = child;
			if (near != node)
				node->key = near->key;
			if (near->color == BLACK && child != NIL)
				RB_delete_fixup(child);
			delete near;
		}

		Node *found_node(value_type key) {
			Node *end = root;
			while (end != NIL) {
				if (end->key > key)
					end = end->left;
				else if (end->key < key)
					end = end->right;
				else
					return (end);
			}
			return (NIL);
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

		const Node *get_nil( void ) {
				return (NIL);
		}

		const Node *get_root( void ) {
				return (this->root);
		}

		iterator begin( void ) {
			std::cout << "begin\n";
			std::cout << root->key->first << "\n";
			return (iterator(root));
		}

		// temp showcase
		void showTree( void ) {
			if (root != NIL) {
				std::cout << GREENC << NIL << "-------TREE--------\n";
				printKey(root, "root");
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
				// if (tmp->p != NIL)
				// 	std::cout << " parrent = " << tmp->p->key;
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
				root = found_root(node);
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
			root = found_root(node);
			root->color = BLACK;
		}

		void RB_delete_fixup(Node *node) {
			while (node != root && node->color == BLACK) {
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
						node = root;
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
						node = root;
					}
				}
			}
			node->color = BLACK;
			root = found_root(node);
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

			std::cout << value->first << "," << value->second << "- node get val \n";

			node->color = RED;
			node->left = NIL;
			node->right = NIL;
			node->p = NIL;
			node->key = value;

			std::cout << node << "- new node \n";
			std::cout << node->key->second << "," << node->key->second << "- init value \n";
			return (node);
		}

		void	delete_node(Node *ptr) {
			if (ptr == NIL)
				return ;
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
		Node   *root;
		Node   nil;
};

} // namespace ft 

#endif