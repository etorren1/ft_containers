#ifndef __ITERATOR_HPP__
#define __ITERATOR_HPP__

#include <iostream>
#include <stdexcept>
#include "RandomAccessIterator.hpp"

namespace ft {

template<class T, class Allocator = std::allocator<T> >
class vector
{
	public:
		typedef	T									value_type;
		typedef std::allocator<T> 					allocator_type;
		typedef size_t		 						size_type;
		typedef	std::ptrdiff_t						difference_type;
		typedef value_type&							reference;
		typedef const value_type&					const_reference;
		typedef typename Allocator::pointer			pointer;
		typedef typename Allocator::const_pointer 	const_pointer;
		typedef Iterator_v<T>						iterator;
		typedef	Iterator_v<const T>					const_iterator;
		//typedef	reverse_iterator;
		//typedef	const_reverse_iterator;


		vector( void ) 
		{ 
			_container = NULL;
			_size = 0; 
			_capacity = 0;
		}

		~vector( void )
		{ 
			for (size_type i = 0; i < _size + 1; i++)
				_allocator.destroy(_container + i);
			_allocator.deallocate(_container, _capacity + 1);
		}


		size_type	max_size( void ) const
		{
			return std::numeric_limits<difference_type>::max() / (sizeof(T) > 2 ? sizeof(T) / 2 : sizeof(T));
		}

		void reserve( size_type new_cap )
		{
			if (new_cap > max_size()) throw std::length_error("vector");
			if (new_cap > _capacity)
			{
				T *tmp = _allocator.allocate(new_cap + 1);
				for (size_type i = 0; i < _size; i++)
				{
					_allocator.construct(tmp + i, _container[i]);
					_allocator.destroy(_container + i);
				}
				_allocator.deallocate(_container, _capacity + 1);
				_capacity = new_cap;
				_container = tmp;
			}
		}

		void	push_back( const T& value )
		{
			if (!_capacity)
				reserve(1);
			else if (_size >= _capacity)
				reserve(2 * _capacity);
			_allocator.construct(_container + _size++, value );
		}

		void	pop_back( void )
		{
			_allocator.destroy(_container + _size--);
		}

		void resize( size_type count, T value = T() )
		{
			if (count > _size)
			{
				reserve(count);
				for ( ;_size < count ;_size++ )
					_allocator.construct(_container + _size, value);
			}
			else if (count < _size)
			{
				for ( ; count < _size; _size--)
					_allocator.destroy(_container + _size);
			}
		}

		void clear( void )
		{
			for ( ; _size > 0; _size--)
				_allocator.destroy(_container + _size);
			_allocator.destroy(_container);	
		}

		vector& operator=( const vector& other )
		{
			if (this == &other)
				return *this;
			_capacity = 0;
			reserve(other.size());
			for(size_type i = 0; i < other.size(); i++)
				push_back(other[i]);
			return *this;
		}

		void assign( size_type count, const T& value )
		{
			clear();
			if (count > _capacity)
				reserve(count);
			for ( ;_size < count; _size++)
				_allocator.construct(_container + _size, value);
		}

		// template< class InputIt >
		// void assign( InputIt first, InputIt last )
		// {

		// }

		allocator_type get_allocator() const { return _allocator; }

		reference operator[]( size_type pos ) { return (_container[pos]); }
		const_reference operator[]( size_type pos ) const { return(_container[pos]); }

		reference at( size_type pos ) { if (_size <= pos) throw std::out_of_range("vector"); return(_container[pos]); }
		const_reference at( size_type pos ) const { if (_size <= pos) throw std::out_of_range("vector"); return(_container[pos]); }

		reference back( void ) { return(_container[_size - 1]); }
		const_reference back( void ) const { return(_container[_size - 1]); }

		reference & front( void ) { return(_container[0]); }
		const_reference & front( void ) const { return(_container[0]); }

		size_type size( void ) const { return(_size); }

		size_type capacity( void ) const { return(_capacity); }

		bool	empty( void ) const { return !(_size); }

		T * data( void ) { return _container; }
		const T * data( void ) const { return _container; }

		iterator	begin( void ) { return (iterator(_container)); }
		const_iterator	begin( void ) const { return (const_iterator(_container)); }

		iterator	end( void ) { return (iterator(_container + _size)); }
		const_iterator	end( void ) const { return (const_iterator(_container + _size)); }

	private:
		T *				_container;
		size_type		_size;
		size_type		_capacity;
		allocator_type	_allocator;
};
}

#endif
