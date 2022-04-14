#ifndef __RBTREE_HPP__
#define __RBTREE_HPP__

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
// #define NIL

template<typename T>
struct _Node
{
	int			color;
	T				key;
	struct _Node*	 p;
	struct _Node*	 left;
	struct _Node*	 right;
};

template<typename T>
class RBTree
{
	public:
		
		typedef	T		   			value_type;
		typedef _Node<value_type>	Node;

		RBTree( void ) {
			nil.color = BLACK;
			nil.p = NIL;
			nil.left = NIL;
			nil.right = NIL;
			nil.key = 0;
			root = NIL;
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

		void RB_delete(T key) {
			
			Node *node = FoundNode(key);
			Node *child, *near;

			if (!node || node == NIL) return;


			if (node->Left == NIL || node->Right == NIL)
				near = node;
			else 
				near = Min(node->Right);
			
			if (near->Left != NIL)
				child = near->Left;
			else
				child = near->Right;

			child->Parent = near->Parent;
			if (Parent(near))
				if (IamLeftOrRight(near) == LEFT)
					near->Parent->Left = child;
				else
					near->Parent->Right = child;
			else
				this->root = child;

			if (near != node) node->value = near->value; //А если константа? Конст каст?


			if (near->colour == Black)
				FixDelete(child);
			
			ClearTerm();
			std::cout << "Удаление узлов дерева" << std::endl;
			this->PrintGraph(tumbler);
			this->PrintInfo();
			std::this_thread::sleep_for(std::chrono::milliseconds(SPEED));
			delete near;
		}

		const Node *nil( void ) {
				return (NIL);
		}

		const Node *root( void ) {
				return (this->root);
		}

		// temp showcase
		void showTree( void ) {
			if (root) {
				std::cout << GREENC << "-------TREE--------\n";
				printKey(root, "root");
			}
		}

	private:

		// temp showcase
		void printKey(Node *tmp, std::string str) {
			if (tmp != NIL) {
				std::string col;
				if (tmp->color == RED) {
					col = "red";
					std::cout << REDC;
				}
				else {
					col = "black";
					std::cout << BLACKC;
				}
				std::cout << str << " = " << tmp->key << " color-" << col;
				if (tmp->p != NIL)
					std::cout << " parrent = " << tmp->p->key;
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
			// std::cout << NIL << "=nil " << node << " && " << node->p\
			//  << " && " << node->p->left << " && " << node->p->right <<"\n";
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