#ifndef __ITERATOR_T_HPP__
#define __ITERATOR_T_HPP__

#include "iterators_traits.hpp"
#include "is_integral.hpp"

namespace ft {

template<typename T>
struct _Node;

template<typename T>
class Iterator_t {
	public:
		typedef T													value_type;
        typedef typename ft::iterator_traits<T*>::pointer			pointer;
        typedef typename ft::iterator_traits<T*>::reference			reference;
		typedef typename ft::iterator_traits<T*>::difference_type 	difference_type;
		typedef std::bidirectional_iterator_tag 					iterator_category;
		typedef _Node<pointer>										Node;

	private:
		Node* _node;


		Node* min(Node* node) const {
			if (!node->left)
				return node;
			while(node->left->key != NULL)
				node = node->left;
			return node;
		}

		Node* max(Node* node) const {
			if (!node->right)
				return node;
			while (node->right->key != NULL)
				node = node->right;
			return node;
		}

	public:
		Iterator_t() {}

		Iterator_t(void *node): _node(static_cast<Node*>(node)) {}

		Iterator_t(const Iterator_t<typename ft::remove_const<value_type>::type > & other) {
			*this = other;
		}

		Iterator_t& operator=(const Iterator_t<typename ft::remove_const<value_type>::type>& other) {
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

template<typename T>
class RevIterator_t {
	public:
		typedef typename ft::iterator_traits<T*>::value_type 		value_type;
		typedef typename ft::iterator_traits<T*>::reference 		reference;
		typedef typename ft::iterator_traits<T*>::pointer			pointer;
		typedef typename ft::iterator_traits<T*>::difference_type	difference_type;
		// typedef ft::iterator_traits<T*>::iterator_category iterator_category;
		typedef std::bidirectional_iterator_tag iterator_category;
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
		RevIterator_t() {}

		RevIterator_t(void *node): _node(static_cast<Node*>(node)) {}

		RevIterator_t(const RevIterator_t<typename ft::remove_const<value_type>::type > & other) {
			*this = other;
		}

		RevIterator_t& operator=(const RevIterator_t<typename ft::remove_const<value_type>::type>& other) {
			_node = other.node();
			return *this;
		}

		reference operator*() const {
			return (*_node->key);
		}

		pointer operator->() const {
			return _node->key;
		}

		RevIterator_t& operator++() {
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

		RevIterator_t operator++(int) {
			RevIterator_t<value_type> temp = *this;
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

		RevIterator_t& operator--() {
			if (_node->key == NULL)
			{
				_node = min(_node->p);
				return *this;
			}
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

		RevIterator_t operator--(int) {
			RevIterator_t<value_type> temp = *this;
			if (_node->key == NULL)
			{
				_node = min(_node->p);
				return temp;
			}
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

		Node* node() const {
			return _node;
		}

	};	

template<typename A, typename B>
bool operator==(const RevIterator_t<A> & lhs, const RevIterator_t<B> & rhs) { return (lhs.node() == rhs.node()); }

template<typename A, typename B>
bool operator!=(const RevIterator_t<A> & lhs, const RevIterator_t<B> & rhs) { return (lhs.node() != rhs.node()); }

}

#endif