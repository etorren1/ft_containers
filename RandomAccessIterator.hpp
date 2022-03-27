#ifndef __Iterator_v_HPP__
#define __Iterator_v_HPP__

#include "iterators_traits.hpp"
#include <iostream>

namespace ft
{
template<class T>
class Iterator_v
{
    public:
        typedef typename ft::iterator_traits<T*>::difference_type 	difference_type;
        typedef typename ft::iterator_traits<T*>::value_type		    value_type;
        typedef typename ft::iterator_traits<T*>::pointer			pointer;
        typedef typename ft::iterator_traits<T*>::reference			reference;
        typedef typename ft::iterator_traits<T*>::iterator_category	iterator_category;

        Iterator_v() { _ptr = nullptr; }
        Iterator_v( pointer ptr ) { _ptr = ptr; }
        Iterator_v( const Iterator_v<value_type>& It ) { _ptr = It.getPtr(); }
        virtual ~Iterator_v() {}

        // Iterator_v<value_type>& operator=( const Iterator_v<value_type>& It ) { _ptr = It.getPtr(); return *this; }
        Iterator_v<value_type>& operator=( pointer ptr ) { _ptr = ptr; return *this; }
        Iterator_v<value_type>& operator+=( const difference_type& move) { _ptr += move; return *this; }
        Iterator_v<value_type>& operator-=( const difference_type& move) { _ptr -= move; return *this; }
        Iterator_v<value_type>& operator++( void ) { ++_ptr; return *this; }
        Iterator_v<value_type>& operator--( void ) { --_ptr; return *this; }
        Iterator_v<value_type> operator++(int) { pointer tmp = _ptr; ++_ptr; return tmp; }
        Iterator_v<value_type> operator--(int) { pointer tmp = _ptr; --_ptr; return tmp; }
        Iterator_v<value_type> operator+( const difference_type& move )
        {
            pointer old = _ptr;
            _ptr += move;
            pointer tmp = _ptr;
            _ptr = old;
            return tmp;
        }
        Iterator_v<value_type> operator-( const difference_type& move )
        {
            pointer old = _ptr;
            _ptr -= move;
            pointer tmp = _ptr;
            _ptr = old;
            return tmp;
        }
        reference operator*( void ) { return (*_ptr); }
        pointer operator->( void ) { return _ptr; }
        reference operator[]( difference_type pos ) const { return(*(_ptr + pos)); }

        pointer getPtr( void ) const { return _ptr; }

    private:
        pointer _ptr;
};

template<typename A, typename B>
bool operator==(const Iterator_v<A> & lhs, const Iterator_v<B> & rhs) { return lhs.getPtr() == rhs.getPtr(); }
template<typename A, typename B>
bool operator!=(const Iterator_v<A> & lhs, const Iterator_v<B> & rhs) { return !(lhs == rhs); }
template<typename A, typename B>
bool operator>(const Iterator_v<A> & lhs, const Iterator_v<B> & rhs) { return lhs.getPtr() > rhs.getPtr(); }
template<typename A, typename B>
bool operator<(const Iterator_v<A> & lhs, const Iterator_v<B> & rhs) { return !(lhs > rhs); }
template<typename A, typename B>
bool operator>=(const Iterator_v<A> & lhs, const Iterator_v<B> & rhs) { return lhs.getPtr() >= rhs.getPtr(); }
template<typename A, typename B>
bool operator<=(const Iterator_v<A> & lhs, const Iterator_v<B> & rhs) { return !(lhs >= rhs); }

}

#endif
