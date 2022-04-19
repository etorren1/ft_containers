#ifndef __ITERATOR_T_HPP__
#define __ITERATOR_T_HPP__

#include "iterators_traits.hpp"
// #include "RBTree.hpp"
#include "is_integral.hpp"

namespace ft {

// template< class T > struct remove_const                { typedef T type; };
// template< class T > struct remove_const<const T>       { typedef T type; };

template<typename T>
struct _Node;

template<typename T>
class Iterator_t {
	public:
		typedef typename ft::iterator_traits<T*>::value_type 		value_type;
		typedef typename ft::iterator_traits<T*>::reference 		reference;
		typedef typename ft::iterator_traits<T*>::pointer			pointer;
		typedef typename ft::iterator_traits<T*>::difference_type	difference_type;
		// typedef ft::iterator_traits<T*>::iterator_category iterator_category;
		typedef std::bidirectional_iterator_tag iterator_category;
		// typedef std::ptrdiff_t              difference_type;
		// typedef T                           value_type;
		// typedef T                          *pointer;
		// typedef T&                          reference; 
		// typedef _Node<typename ft::remove_const<value_type>::type >* Node*;
		// typedef _Node<pointer>										Node;
		typedef _Node<pointer>											Node;

	private:
		Node* _node;


		Node* min(Node* node) const {
			while(node->left->key != NULL)
				node = node->left;
			return node;
		}

		Node* max(Node* node) const {
			while (node->right->key != NULL)
				node = node->right;
			return node;
		}

	public:
		Iterator_t() {}

		Iterator_t(void *node): _node(static_cast<Node*>(node)) {}

		// Iterator_t(const Iterator_t<value_type>& other)
		Iterator_t(const Iterator_t<typename ft::remove_const<value_type>::type > & other)
		// Iterator_t(const Iterator_t<ft::pair<int,int>> & other)
		{
			*this = other;
		}

		// Iterator_t& operator=(const Iterator_t<value_type>& other)
		Iterator_t& operator=(const Iterator_t<typename ft::remove_const<value_type>::type>& other) 
		// Iterator_t<ft::pair<int,int> >& operator=(const Iterator_t<ft::pair<int,int>> & other)
		{
			// std::cout << std::boolalpha;
			// using type = typename ft::remove_const<const value_type>::type;
			// std::cout << std::is_same<type, value_type>::value << "<2=\n";
			_node = other.node();
			return *this;
		}

		reference operator*() const {
			return (*_node->key);
		}

		pointer operator->() const {
			return _node->key;
		}

		Iterator_t& operator++() {
			if (_node->right->key != NULL) {
				_node = min(_node->right);
			}
			else {
				Node* y = _node->p;
				while (y->key != NULL && _node == y->right) {
					_node = y;
					y = y->p;
				}
				_node = y;
			}
			return *this;
		}

		Iterator_t operator++(int) {
			Iterator_t<value_type> temp = *this;
			if (_node->right->key != NULL) {
				_node = min(_node->right);
			}
			else {
				Node* y = _node->p;
				while (y->key != NULL && _node == y->right) {
					_node = y;
					y = y->p;
				}
				_node = y;
			}
			return temp;
		}

		Iterator_t& operator--() {
			if (_node->key == NULL)
			{
				_node = max(_node->p);
				return *this;
			}
			if (_node->left->key != NULL) {
				_node = max(_node->left);
			}
			else {
				Node* y = _node->p;
				while (y->key != NULL && _node == y->left) {
					_node = y;
					y = y->p;
				}
				_node = y;
			}
			return *this;
		}

		Iterator_t operator--(int) {
			Iterator_t<value_type> temp = *this;
			if (_node->key == NULL)
			{
				_node = max(_node->p);
				return temp;
			}
			if (_node->left->key != NULL) {
				_node = max(_node->left);
			}
			else {
				Node* y = _node->p;
				while (y->key != NULL && _node == y->left) {
					_node = y;
					y = y->p;
				}
				_node = y;
			}
			return temp;
		}

		Node* node() const {
			return _node;
		}

	};	

template<typename A, typename B>
bool operator==(const Iterator_t<A> & lhs, const Iterator_t<B> & rhs) { return (lhs.node() == rhs.node()); }

template<typename A, typename B>
bool operator!=(const Iterator_t<A> & lhs, const Iterator_t<B> & rhs) { return (lhs.node() != rhs.node()); }

}

#endif