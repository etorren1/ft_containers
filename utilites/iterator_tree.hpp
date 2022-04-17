#ifndef __ITERATOR_T_HPP__
#define __ITERATOR_T_HPP__

#include "iterators_traits.hpp"
#include "RBTree.hpp"
#include "is_integral.hpp"

namespace ft {

#define NIL 	&(this->nil)

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
		// typedef std::ptrdiff_t              difference_type;
		// typedef T                           value_type;
		// typedef T                           *pointer;
		// typedef T&                          reference; 
		typedef std::bidirectional_iterator_tag iterator_category;
		// typedef _Node<typename ft::remove_const<value_type>::type >* node_pointer;
		typedef _Node<value_type>*	node_pointer;
		// typedef _Node<value_type>									node_pointer;

	private:
		node_pointer _node;

		node_pointer min(node_pointer node) const {
			while(node->left != NIL)
				node = node->left;
			return node;
		}

		node_pointer max(node_pointer node) const {
			while (node->right != NIL)
				node = node->right;
			return node;
		}

	public:
		Iterator_t() {}

		Iterator_t(void *node): _node(static_cast<node_pointer>(node)) {}

		// Iterator_t(const Iterator_t<typename ft::remove_const<value_type>::type > & other)
		Iterator_t(const Iterator_t<value_type>& other)
		{
			*this = other;
		}

		// Iterator_t& operator=(const Iterator_t<typename ft::remove_const<value_type>::type>& other) {
		Iterator_t& operator=(const Iterator_t<value_type>& other) {
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
			if (_node->right != NIL) {
				_node = min_key(_node->right);
			}
			else {
				node_pointer y = _node->parent;
				while (y != NULL && _node == y->right) {
					_node = y;
					y = y->p;
				}
				_node = y;
			}
			return *this;
		}

		Iterator_t operator++(int) {
			Iterator_t<value_type> temp = *this;
			if (!_node->right->is_nil) {
				_node = min_key(_node->right);
			}
			else {
				node_pointer y = _node->parent;
				while (y != NULL && _node == y->right) {
					_node = y;
					y = y->parent;
				}
				_node = y;
			}
			return temp;
		}

		Iterator_t& operator--() {
			if (_node->left && !_node->left->is_nil) {
				_node = max(_node->left);
			}
			else {
				node_pointer y = _node->parent;
				while (y != NULL && _node == y->left) {
					_node = y;
					y = y->p;
				}
				_node = y;
			}
			return *this;
		}

		Iterator_t operator--(int) {
			Iterator_t<value_type> temp = *this;
			if (_node->left && !_node->left->is_nil) {
				_node = max(_node->left);
			}
			else {
				node_pointer y = _node->parent;
				while (y != NULL && _node == y->left) {
					_node = y;
					y = y->p;
				}
				_node = y;
			}
			return temp;
		}

		node_pointer node() const {
			return _node;
		}
	};	

template<typename A, typename B>
bool operator==(const Iterator_t<A> & lhs, const Iterator_t<B> & rhs) { return (lhs.node() == rhs.node()); }

template<typename A, typename B>
bool operator!=(const Iterator_t<A> & lhs, const Iterator_t<B> & rhs) { return (lhs.node() != rhs.node()); }

}

#endif