#ifndef __RBTREE_HPP__
#define __RBTREE_HPP__

namespace ft {

#define RED     0
#define BLACK   1


#define BLACKC  "\033[47;30m"
#define YELLOWC    "\033[22;33m"
#define REDC  "\033[47;31m"
#define GREENC "\e[0;32m"
#define BLUEC  "\033[40;34m"
#define RESETC "\033[0m"
// #define NIL

template<typename T>
struct Node
{
    short            color;
    T                key;
    struct Node*     p;
    struct Node*     left;
    struct Node*     right;
};

template<typename U>
class RBTree
{
    public:
        
        typedef	U           value_type;

        RBTree( void ) {
            // T.color = BLACK;
            // T.p = nullptr;
            // T.left = nullptr;
            // T.right = nullptr;
            // T.key = NULL;
            // root = &T;
            root = NULL;
        }

        ~RBTree( void ) {
            deleteNode(root);
        }

        void RB_insert(value_type key) {
            Node<value_type> *prev = NULL;
            Node<value_type> *curr = root;
            Node<value_type> *node = initNode(key);

            while (curr != NULL)
            {
                prev = curr;
                if (node->key < curr->key)
                    curr = curr->left;
                else
                    curr = curr->right;
            }
            node->p = prev;
            if (prev == NULL)
                root = node;
            else if (node->key < prev->key)
                prev->left = node;
            else
                prev->right = node;
            // RB_insert_fixup(node);
        }

        void showTree( void ) {
            if (root) {
                std::cout << GREENC << "-------TREE--------\n";
                printKey(root, "root");
            }
        }

    private:

        // temp showcase
        void printKey(Node<value_type> *tmp, std::string str) {
            if (tmp) {
                std::string col;
                if (tmp->color) {
                    col = "red";
                    std::cout << REDC;
                }
                else {
                    col = "black";
                    std::cout << BLACKC;
                }
                std::cout << str << " = " << tmp->key << " color-" << col;
                if (tmp->p)
                    std::cout << " parrent = " << tmp->p->key;
                std::cout << RESETC << std::endl;
                printKey(tmp->left, "left");
                printKey(tmp->right, "right");
            }
        }

        Node<value_type> *initNode(value_type value)
        {
            Node<value_type> * node = new Node<value_type>();

            node->color = RED;
            node->left = nullptr;
            node->right = nullptr;
            node->p = nullptr;
            node->key = value;
            return (node);
        }

        void    deleteNode(Node<value_type> *ptr) {
            if (ptr == NULL)
                return ;
            deleteNode(ptr->left);
            deleteNode(ptr->right);
            delete ptr;
        }

    private:
        Node<value_type>   *root;
        // Node<value_type>   T;
};

} // namespace ft 

#endif