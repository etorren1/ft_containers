#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__

#include <iostream>
#include <stdexcept>
#include <memory>
#include <limits>
#include "utilites/iterator_vector.hpp"
#include "utilites/lexicographical_compare.hpp"
#include "utilites/enable_if.hpp"
#include "utilites/is_integral.hpp"
#include "utilites/equal.hpp"

namespace ft {

template<typename T, class Allocator = std::allocator<T> >
class vector
{
	public:
		typedef	T									value_type;
		typedef Allocator							allocator_type;
		typedef size_t		 						size_type;
		typedef	std::ptrdiff_t						difference_type;
		typedef value_type&							reference;
		typedef const value_type&					const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer 		const_pointer;
		typedef Iterator_v<T>						iterator;
		typedef	Iterator_v<const T>					const_iterator;
		typedef	RevIterator_v<T>					reverse_iterator;
		typedef	RevIterator_v<const T>				const_reverse_iterator;

		explicit vector( const allocator_type& allocator = allocator_type() ) 
		{
			_container = NULL;
			_size = 0; 
			_capacity = 0;
			_allocator = allocator;
		}

		explicit vector (size_type n, const T& value, const allocator_type& allocator = allocator_type())
		{
			_container = _allocator.allocate(n);
			_size = n; 
			_capacity = n;
			_allocator = allocator;
			for (size_type i = 0; i < n; i++)
				_allocator.construct(_container + i, value);
		}

		template <class InputIt>
		vector (typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type first, InputIt last , const allocator_type& allocator = allocator_type())
		{
			_container = NULL;
			_size = 0; 
			_capacity = 0;
			_allocator = allocator;
			insert(begin(), first, last);
		}
	
		vector (const vector& x, const allocator_type& allocator = allocator_type())
		{
			_container = NULL;
			_size = 0; 
			_capacity = 0;
			_allocator = allocator;
			*this = x;
		}

		~vector( void )
		{
			for (size_type i = 0; i < _size; i++) {
				_allocator.destroy(_container + i);
			}
			_allocator.deallocate(_container, _capacity);
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
				pointer tmp = _allocator.allocate(new_cap);
				try {
					for (size_type i = 0; i < _size; i++)
					{
						_allocator.construct(tmp + i, _container[i]);
						_allocator.destroy(_container + i);
					}
				}
				catch(...) {
					for (size_type i = 0; i < _size; i++)
						_allocator.destroy(tmp + i);
					_allocator.deallocate(tmp, new_cap);
					throw;
				}
				_allocator.deallocate(_container, _capacity);
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
				if (_capacity < count)
					reserve(_capacity * 2 > count ? _capacity * 2 : count);
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
			clear();
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

		template< class InputIt >
		void assign( InputIt first, InputIt last )
		{
			clear();
			insert(begin(), first, last);
		}

		iterator insert( iterator pos, const T& value )
		{
			difference_type new_pos = pos - begin();
			insert(pos, 1, value);
			return begin() + new_pos;
		}

		void insert( iterator pos, size_type count, const T& value )
		{
			size_type index = pos - begin();
			if (!count || index > _size)
				return ;
			if (_capacity < _size + count && _capacity * 2 > _size + count)
				reserve(_capacity * 2);
			else if (_capacity)
				reserve(_size + count);
			else if (!_capacity)
				reserve(count);
			_size += count;
			size_type idx = _size;
			for ( ; idx != index + count; idx--)
				_allocator.construct(_container + idx, _container[idx - count]);
			for ( ; count > 0; count--)
				_allocator.construct(_container + --idx, value);
		}

		template<typename InputIt>
		typename ft::enable_if<!ft::is_integral<InputIt>::value, void>::type
		insert( iterator pos, InputIt first, InputIt last )
		{
			size_type count = last - first;
			size_type index = pos - begin();
			if (count <= 0 || index > _size)
				return ;
			if (_capacity < _size + count)
			{
				size_type new_cap =	_capacity * 2 >= _size + count ? _capacity * 2 : _size + count;
				pointer tmp = _allocator.allocate(new_cap);
				try {
					for (size_type i = 0; i < index; i++) {
						_allocator.construct(tmp + i, _container[i]);
						_allocator.destroy(_container + i);
					}
					for (size_type i = 0; i < size_type(count); i++, first++)
						_allocator.construct(tmp + index + i, *first);
					for (size_type i = index; i < _size; i++) {
						_allocator.construct(tmp + count + i, _container[i]);
						_allocator.destroy(_container + index + i);
					}
					
				}
				catch (...) {
					for (size_type i = 0; i < new_cap; i++)
						_allocator.destroy(tmp + i);
					_allocator.deallocate(tmp, new_cap);
					throw;
				}
				_allocator.deallocate(_container, _capacity);
				_size += count;
				_capacity = new_cap;
				_container = tmp;
			}
			else
			{
				for (size_type i = _size; i > size_type(index); i--) 
					_allocator.construct(_container + i + count - 1, *(_container + i - 1));
				for (size_type i = 0; i < size_type(count); i++, first++)
					_allocator.construct(_container + index + i, *first);
				_size += count;			
			}
		}

		iterator erase (iterator pos)
		{
			size_type index = pos - begin();
			if (index < 0 || index >= _size)
				return pos;
			for (size_type idx = index ; idx < _size; idx++)
				_container[idx] = _container[idx + 1];
			_size--;
			_allocator.destroy(_container + _size);
			return iterator(_container + index);
		}

		iterator erase (iterator first, iterator last)
		{
			size_type count = last - first;
			size_type index = first - begin() - 1;
			if (count <= 0 || index > _size)
				return last;
			size_type new_cap = _size - count;
			pointer tmp = _allocator.allocate(new_cap);
			for (size_type i = 0; i < index; i++)
				_allocator.construct(tmp + i, _container[i]);
			for (size_type i = 0; i < _size - index - count; i++)
				_allocator.construct(tmp + index + i, _container[index + i + count]);
			clear();
			_allocator.deallocate(_container, _capacity);		
			_size = new_cap;
			_container = tmp;
			return _container + index + 1;
		}

		void swap (vector& x)
		{
			size_type tmp_size = _size;
			size_type tmp_capasity = _capacity;
			pointer	tmp_container = _container;
			allocator_type tmp_allocator = _allocator;

			_size = x._size;
			_capacity = x._capacity;
			_container = x._container;
			_allocator = x._allocator;

			x._size = tmp_size;
			x._capacity = tmp_capasity;
			x._container = tmp_container;
			x._allocator = tmp_allocator;
		}

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

		reverse_iterator	rbegin( void ) { return (reverse_iterator(_container + _size - 1)); }
		const_reverse_iterator	rbegin( void ) const { return (const_reverse_iterator(_container + _size - 1)); }

		reverse_iterator	rend( void ) { return (reverse_iterator(_container - 1)); }
		const_reverse_iterator	rend( void ) const { return (const_reverse_iterator(_container - 1)); }

	private:
		pointer			_container;
		size_type		_size;
		size_type		_capacity;
		allocator_type	_allocator;
};

template <class T>
bool operator==(const vector<T>& lhs, const vector<T>& rhs) { return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()); }
template <class T>
bool operator!=(const vector<T>& lhs, const vector<T>& rhs) { return !(lhs == rhs); }
template <class T>
bool operator<(const vector<T>& lhs, const vector<T>& rhs) { return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); }
template <class T>
bool operator>(const vector<T>& lhs, const vector<T>& rhs) { return rhs < lhs; }
template <class T>
bool operator<=(const vector<T>& lhs, const vector<T>& rhs) { return !(lhs > rhs); }
template <class T>
bool operator>=(const vector<T>& lhs, const vector<T>& rhs) { return !(lhs < rhs); }

}

namespace std
{
	template< class T >
	void swap(ft::vector<T>& lhs, ft::vector<T>& rhs ) {
		lhs.swap(rhs);
	}
}

#endif
