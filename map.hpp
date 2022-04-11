#ifndef __MAP_HPP__
#define __MAP_HPP__

#include <iostream>
#include "utilites/pair.hpp"
#include "utilites/less.hpp"
#include <map>

namespace ft {

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
		// typedef iter		iterator;
		// typedef c_iter		const_iterator;
		// typedef r_iter		reverse_iterator;
		// typedef c_r_iter		const_reverse_iterator;
		typedef std::ptrdiff_t						difference_type;
		typedef size_t								size_type;

		class map<Key, T, Compare, Allocator>::value_compare : public ft::binary_function<value_type, value_type, bool>
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
		}

		//empty (1)	
		explicit map (const key_compare& compare = key_compare(), const allocator_type& allocator = allocator_type())
		{
			_container = NULL;
			_size = 0;
			_allocator = allocator;
			_compare = compare;
		}
		
		//range (2)	
		// template <class InputIterator>
		// map (InputIterator first, InputIterator last, const key_compare& compare = key_compare(), const allocator_type& allocator = allocator_type()) {}
		
		//copy (3)	
		// map (const map& x) {}

	private:
		pointer				_container;
		size_type			_size;
		allocator_type		_allocator;
		key_compare			_compare;

};

}

#endif