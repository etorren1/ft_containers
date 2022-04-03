#ifndef __ITERATOR_HPP__
#define __ITERATOR_HPP__

#include <iostream>
#include <stdexcept>
#include <memory>
#include "Iterator_vector.hpp"
#include "enable_if.hpp"
#include "is_integral.hpp"

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
			if (_container)
			{
				// std::cout << "size = " << _size << " cont = " << _container << "\n";
				for (size_type i = 0; i < _size; i++) {
					_allocator.destroy(_container + i);
				// 	std::cout << i << "[i] " << _container << "\n";
				}
				// _allocator.destroy(_container + 2);
				_allocator.deallocate(_container, _capacity + 1);
			}
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
				pointer tmp = _allocator.allocate(new_cap + 1);
				for (size_type i = 0; i < _size; i++)
				{
					_allocator.construct(tmp + i, _container[i]);
					if (_container)
						_allocator.destroy(_container + i);
				}
				if (_container)
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

		template< class InputIt >
		void assign( InputIt first, InputIt last )
		{
			clear();
			insert(begin(), first, last);
		}

		// iterator insert( iterator pos, const T& value )
		// {
		// 	size_type index = 0;
		// 	iterator ret = begin();
		// 	for ( ; ret != pos; ret++)
		// 	{
		// 		index++;
		// 		if (index == _size + 1)
		// 			return pos;
		// 	}
		// 	if ( _capacity && _capacity == _size)
		// 		reserve(_capacity * 2);
		// 	else
		// 		reserve(1);
		// 	size_type idx = ++_size;
		// 	for ( ; idx != index; idx--)
		// 		_container[idx] = _container[idx - 1];
		// 	_container[idx] = value;
		// 	return ret;
		// }

		iterator insert( iterator pos, const T& value )
		{
			insert(pos, 1, value);
			return pos;
		}

		void insert( iterator pos, size_type count, const T& value )
		{
			if (!count)
				return ;
			size_type index = 0;
			iterator ret = begin();
			for ( ; ret != pos; ret++)
			{
				index++;
				if (index == _size + 1)
					return ;
			}
			if (_capacity < _size + count && _capacity * 2 > _size + count)
				reserve(_capacity * 2);
			else if (_capacity)
				reserve(_size + count);
			else
				reserve(count);
			_size += count;
			size_type idx = _size;
			for ( ; idx != index + count; idx--)
				_allocator.construct(_container + idx, _container[idx - count]);
			for ( ; count > 0; count--)
				_allocator.construct(_container + --idx, value);
		}

		// template<typename InputIt>
		// typename ft::enable_if<!ft::is_integral<InputIt>::value, void>::type
		// insert( iterator pos, InputIt first, InputIt last )
		// {
		// 	size_type count = 0;
		// 	for ( ; first != last; first++)
		// 		count++;
		// 	if (count == 0)
		// 		return ;
		// 	size_type index = 0;
		// 	iterator ret = begin();
		// 	for ( ; ret != pos; ret++)
		// 	{
		// 		index++;
		// 		if (index == _size + 1)
		// 			return ;
		// 	}
		// 	if (_capacity < _size + count && _capacity * 2 > _size + count)
		// 		reserve(_capacity * 2);
		// 	else if (_capacity)
		// 		reserve(_size + count);
		// 	else
		// 		reserve(count);
		// 	_size += count;
		// 	size_type idx = _size;
		// 	for ( ; idx != index + count; idx--)
		// 		_allocator.construct(_container + idx, _container[idx - count]);
		// 	// std::cout << _container << "\n";
		// 	// std::cout << _container + 1 << "\n";
		// 	// std::cout << _container + 2 << "\n";
		// 	for ( ; count > 0; count--)
		// 	{
		// 		idx--;
		// 		last--;
		// 		// std::cout << "last[" << count << "]= " << *last << " cont = " << _container + idx << "\n";
		// 		_allocator.construct(_container + idx, *last);
		// 		// _container[idx] = new(*last);
		// 		// std::cout << "asda\n";
		// 	}
		// }

		template <class InputIterator>
    		void insert (iterator position, InputIterator first, InputIterator last, typename enable_if<!is_integral<InputIterator>::value>::type* = 0)
			{
			// if (position < begin() || position > end() || first > last)
			// 	throw std::logic_error("vector");
			size_type start = 0;
			for (iterator ret = begin() ; ret != position; ret++)
			{
				start++;
				if (start == _size + 1)
					return ;
			}
			size_type count = 0;
			for (InputIterator tmp = first ; tmp != last; tmp++)
				count++;
			if (_size + count > _capacity) {
				size_type new_cap = _capacity * 2 >= _size + count ? _capacity * 2 : _size + count;
				pointer new_arr = _allocator.allocate(new_cap);
				std::uninitialized_copy(begin(), position, iterator(new_arr));
				try {
					for (size_type i = 0; i < static_cast<size_type>(count); i++, first++)
						_allocator.construct(new_arr + start + i, *first);
				}
				catch (...){
					for (size_type i = 0; i < count + start; ++i)
						_allocator.destroy(new_arr + i);
					_allocator.deallocate(new_arr, new_cap);
					throw;
				}
				std::uninitialized_copy(position, end(), iterator(new_arr + start + count));
				for (size_type i = 0; i < _size; i++)
					_allocator.destroy(_container + i);
				_allocator.deallocate(_container, _capacity);
				_size += count;
				_capacity = new_cap;
				_container = new_arr;
			}
			else {
				for (size_type i = _size; i > static_cast<size_type>(start); i--) {
					_allocator.destroy(_container + i + count - 1);
					_allocator.construct(_container + i + count - 1, *(_container + i - 1));
				}
				for (size_type i = 0; i < static_cast<size_type>(count); i++, first++) {
					_allocator.destroy(_container + i + count);
					_allocator.construct(_container + start + i, *first);
				}
				_size += count;
			}
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
		T *				_container;
		size_type		_size;
		size_type		_capacity;
		allocator_type	_allocator;
};

template <class T>
bool operator==(const vector<T>& lhs, const vector<T>& rhs)
{
	if (&lhs == &rhs)
		return true;
	if (lhs.size() != rhs.size())
		return false;
	typename ft::vector<T>::const_iterator lit = lhs.begin();
	typename ft::vector<T>::const_iterator rit = rhs.begin();
	for ( ; lit != lhs.end() && rit != rhs.end(); lit++, rit++)
	{
		if (*lit != *rit)
			return false;
	}
	if (lit != lhs.end() || rit != rhs.end())
		return false;
	return true;
}

template <class T>
bool operator!=(const vector<T>& lhs, const vector<T>& rhs) { return !(lhs == rhs); }

template <class T>
bool operator<(const vector<T>& lhs, const vector<T>& rhs)
{
	if (&lhs == &rhs)
		return false;
	typename ft::vector<T>::const_iterator lit = lhs.begin();
	typename ft::vector<T>::const_iterator rit = rhs.begin();
	for ( ; lit != lhs.end() && rit != rhs.end(); lit++, rit++)
	{
		if (*lit < *rit)
			return true;
		if (*lit > *rit)
			return false;
	}
	if (lit == lhs.end() && rit != rhs.end())
		return true;
	return false;
}

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
