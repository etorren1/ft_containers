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

// template< class T, class U >
// class mapTree;

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
		// typedef c_iter		const_iterator;
		// typedef r_iter		reverse_iterator;
		// typedef c_r_iter		const_reverse_iterator;

		//empty (1)	
		explicit map (const key_compare& compare = key_compare(), const allocator_type& allocator = allocator_type()) : _tree(compare)
		{
			_pair = NULL;
			_size = 0;
			_allocator = allocator;
			_compare = compare;
		}
		
		//range (2)	
		// template <class InputIterator>
		// map (InputIterator first, InputIterator last, const key_compare& compare = key_compare(), const allocator_type& allocator = allocator_type()) {}
		
		//copy (3)	
		// map (const map& x) {}

		mapped_type& operator[] (const key_type& key)
		{
			// return _tree.get_value(key);
			return (*( (this->insert( make_pair(key, mapped_type()) ) ).first)).second;
		}

		// single element (1)	
		pair<iterator, bool> insert (const value_type& value)
		{
			iterator it = _tree.found_node(value);
			if (it != _tree.get_nil())
				return ft::make_pair(iterator(it),  false);
			_pair = _allocator.allocate(1);
			_allocator.construct(_pair ,value);
			it = _tree.RB_insert(_pair);
			return ft::make_pair(iterator(it), true);
		}

		void	test(void)
		{

			// iterator yol = _tree.begin();
			// std::cout << yol->second << " << yol\n";
			_tree.showTree();
			// std::cout << _tree.get_root() << "=" << *yol << "\n";
			// std::cout << _tree.get_root() << *yol << "\n";
		}

		iterator begin( void )
		{
			return iterator(_tree.begin());
		}

		iterator end( void )
		{
			return iterator(_tree.end());
		}

		// with hint (2)	
		// iterator insert (iterator position, const value_type& val);
		// range (3)	
		// template <class InputIterator>
		// void insert (InputIterator first, InputIterator last);

	private:
		tree_type			_tree;
		pointer				_pair;
		size_type			_size;
		allocator_type		_allocator;
		key_compare			_compare;

};

// template< class T, class U >
// class mapTree : public RBTree< T,U > {
// 	public:

// 		typedef	T		pointer;
// 		typedef	U		value_type;

// 		void	find_value(value_type& value) {
			
// 		}
// };

}

#endif