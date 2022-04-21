#ifndef __MAP_HPP__
#define __MAP_HPP__

#include <iostream>
#include "utilites/pair.hpp"
#include "utilites/less.hpp"
#include "utilites/RBTree.hpp"
#include <map>

namespace ft {

template< class T, class U , class Comp>
class RBTree;

template< class Key, class T, class Compare = ft::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
class map {

	public:
		typedef Key								 	key_type;
		typedef T			 						mapped_type;
		typedef typename ft::pair<const Key, T>		value_type;
		typedef Compare	 							key_compare;
		typedef Allocator	 						allocator_type;
		typedef typename allocator_type::reference	reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer	pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef std::ptrdiff_t						difference_type;
		typedef size_t								size_type;

		// class map<Key, T, Compare, Allocator>::value_compare : public ft::binary_function<value_type, value_type, bool>
		class value_compare : public ft::binary_function<value_type, value_type, bool>
		{	 // in C++98, it is required to inherit binary_function<value_type,value_type,bool>
			friend class map;
			protected:
				Compare comp;
				value_compare (Compare c) : comp(c) {}	// constructed with map's comparison object
			public:
				typedef bool result_type;
				typedef value_type first_argument_type;
				typedef value_type second_argument_type;
				bool operator() (const value_type& x, const value_type& y) const { return comp(x.first, y.first); }
		};

		typedef RBTree<pointer, value_type, value_compare>			tree_type;
		typedef typename tree_type::iterator						iterator;
		typedef typename tree_type::const_iterator					const_iterator;
		// typedef r_iter		reverse_iterator;
		// typedef c_r_iter		const_reverse_iterator;

		//empty (1)	
		explicit map (const key_compare& compare = key_compare(), const allocator_type& allocator = allocator_type()) : _tree(compare)
		{
			_pair = NULL;
			_allocator = allocator;
			_compare = compare;
		}
		
		//range (2)	
		template <class InputIterator>
		map (InputIterator first, InputIterator last, const key_compare& compare = key_compare(), const allocator_type& allocator = allocator_type()) : _tree(compare)
		{
			_compare = compare;
			_allocator = allocator;
			// insert(first, last);
		}
		
		//copy (3)	
		map ( map& other ) : _tree(other._compare)
		{
			_allocator = other._allocator;
			_compare = other._compare;
			*this = other;
			insert(other.begin(), other.end());
		}

		map& operator=( map& other )
		{
			if (this == &other)
				return *this;
			clear();
			_allocator = other._allocator;
			_compare = other._compare;
			insert(other.begin(), other.end());
			return *this;
		}

		mapped_type& operator[] (const key_type& key)
		{
			// return _tree.get_value(key);
			return (*( (this->insert( ft::make_pair(key, mapped_type()) ) ).first)).second;
		}

		void clear( void )
		{
			for (iterator it = begin(); it != end(); it++)
			{
				_pair = it.node()->key;
				_allocator.destroy(_pair);
				_allocator.deallocate(_pair, 1);
			}
			_tree.delete_tree();
		}

		// single element (1)	
		pair<iterator, bool> insert (const value_type& value)
		{
			iterator it = _tree.found_node(value);
			if (it != _tree.get_nil())
				return ft::make_pair(iterator(it), false);
			_pair = _allocator.allocate(1);
			_allocator.construct(_pair ,value);
			it = _tree.RB_insert(_tree.get_root(), _pair);
			return ft::make_pair(iterator(it), true);
		}

		// with hint (2) <- slower?
		// iterator insert (iterator position, const value_type& value)
		// {
		// 	position = _tree.found_node(value);
		// 	if (position != _tree.get_nil())
		// 		return position;
		// 	_pair = _allocator.allocate(1);
		// 	_allocator.construct(_pair ,value);
		// 	position = _tree.RB_insert(_tree.get_root(), _pair);
		// 	return position;
		// }

		// with hint (2) <- faster?
		iterator insert (iterator position, const value_type& value)
		{
			if (_compare(position->first, _pair->first))
			{
				iterator it = _tree.found_node(position, value);
				if (it != _tree.get_nil())
					return it;
				_pair = _allocator.allocate(1);
				_allocator.construct(_pair ,value);
				position = _tree.RB_insert(position, _pair);
			}
			else {
				ft::pair<ft::map<Key, T, Compare, Allocator>::iterator, bool> its;
				its = insert(value);
				position = its.first;
			}
			return position;
		}

		// range (3)	
		template <class InputIterator>
		void insert (InputIterator first, InputIterator last)
		{
			for ( ; first != last; first++)
				insert(*first);
		}


		iterator begin( void ) {
			return iterator(_tree.begin());
		}

		const_iterator begin( void ) const {
			return const_iterator(_tree.begin());
		}

		iterator end( void ) {
			return iterator(_tree.end());
		}

		const_iterator end( void ) const {
			return const_iterator(_tree.end());
		}

		bool	empty( void ) {
			return _tree.empty();
		}

		iterator find (const key_type& k) {
			return _tree.found_node(ft::make_pair(k, mapped_type()));
		}

		const_iterator find (const key_type& k) const {
			return _tree.found_node(ft::make_pair(k, mapped_type()));
		}

		size_type count (const key_type& k) const {
			return _tree.count(ft::make_pair(k, mapped_type()));
		}

		size_type size( void ) const {
			return _tree.size();
		}

		size_type max_size( void ) const {
			return _allocator.max_size();
		}

		key_compare key_comp( void ) const {
			return key_compare();
		}

		value_compare value_comp( void ) const {
			return _tree.value_comp();
		}

		iterator lower_bound(const key_type& k) {
			return (_tree.lower_bound(ft::make_pair(k, mapped_type())));
		}

		const_iterator lower_bound(const key_type& k) const {
			return (_tree.lower_bound(ft::make_pair(k, mapped_type())));
		}

		iterator upper_bound(const key_type& k) {
			return (_tree.upper_bound(ft::make_pair(k, mapped_type())));
		}

		const_iterator upper_bound(const key_type& k) const {
			return (_tree.upper_bound(ft::make_pair(k, mapped_type())));
		}

		ft::pair<iterator, iterator> equal_range(const key_type & k) {
			return (_tree.equal_range(ft::make_pair(k, mapped_type())));
		}	

		ft::pair<const_iterator, const_iterator> equal_range(const key_type & k) const {
			return (_tree.equal_range(ft::make_pair(k, mapped_type())));
		}	

		allocator_type get_allocator( void ) const {
			return _allocator;
		}

		void	test(void) { // test
			_tree.showTree();
		}
	private:
		tree_type			_tree;
		pointer				_pair;
		allocator_type		_allocator;
		key_compare			_compare;

};

}

#endif