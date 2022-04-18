#ifndef __Iterator_v_HPP__
#define __Iterator_v_HPP__

#include "iterators_traits.hpp"
#include <iostream>
#include "../vector.hpp"

template<typename V, class Allocator> class vector;

namespace ft
{

template<class T>
class Iterator_v
{
    template<typename V, class Allocator> friend class vector;
    public:
        typedef T _base;
        typedef typename ft::iterator_traits<T*>::difference_type 	difference_type;
        typedef typename ft::iterator_traits<T*>::value_type		value_type;
        typedef typename ft::iterator_traits<T*>::pointer			pointer;
        typedef typename ft::iterator_traits<T*>::reference			reference;
        // typedef typename ft::iterator_traits<T*>::iterator_category	iterator_category; 
        typedef	std::random_access_iterator_tag	iterator_category; // for compare std:: with ft::
        typedef pointer iterator_type;

        Iterator_v() { _ptr = NULL; }
        Iterator_v( pointer ptr ) { _ptr = ptr; }
        Iterator_v( const Iterator_v<value_type>& It ) { _ptr = It.getPtr(); }
        virtual ~Iterator_v() {}

        // Iterator_v<value_type>& operator=( const Iterator_v<value_type>& It ) { _ptr = It.getPtr(); return *this; }
        Iterator_v<T>& operator=( pointer ptr ) { _ptr = ptr; return *this; }
        Iterator_v<T>& operator+=( const difference_type& move) { _ptr += move; return *this; }
        Iterator_v<T>& operator-=( const difference_type& move) { _ptr -= move; return *this; }
        Iterator_v<T>& operator++( void ) { ++_ptr; return *this; }
        Iterator_v<T>& operator--( void ) { --_ptr; return *this; }
        Iterator_v<T> operator++(int) { pointer tmp = _ptr; ++_ptr; return tmp; }
        Iterator_v<T> operator--(int) { pointer tmp = _ptr; --_ptr; return tmp; }
        Iterator_v<T> operator+( const difference_type& move )
        {
            pointer old = _ptr;
            _ptr += move;
            pointer tmp = _ptr;
            _ptr = old;
            return tmp;
        }
        Iterator_v<T> operator-( const difference_type& move )
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
std::ptrdiff_t operator-(const Iterator_v<A> & lhs, const Iterator_v<B> & rhs) { return (lhs.getPtr() - rhs.getPtr()); }
template<typename A, typename B>
bool operator==(const Iterator_v<A> & lhs, const Iterator_v<B> & rhs) { return lhs.getPtr() == rhs.getPtr(); }
template<typename A, typename B>
bool operator!=(const Iterator_v<A> & lhs, const Iterator_v<B> & rhs) { return !(lhs == rhs); }
template<typename A, typename B>
bool operator>(const Iterator_v<A> & lhs, const Iterator_v<B> & rhs) { return lhs.getPtr() > rhs.getPtr(); }
template<typename A, typename B>
bool operator<(const Iterator_v<A> & lhs, const Iterator_v<B> & rhs) { return lhs.getPtr() < rhs.getPtr(); }
template<typename A, typename B>
bool operator>=(const Iterator_v<A> & lhs, const Iterator_v<B> & rhs) { return lhs.getPtr() >= rhs.getPtr(); }
template<typename A, typename B>
bool operator<=(const Iterator_v<A> & lhs, const Iterator_v<B> & rhs) { return lhs.getPtr() <= rhs.getPtr(); }

template<class T>
class RevIterator_v
{
    public:
        typedef typename ft::iterator_traits<T*>::difference_type 	difference_type;
        typedef typename ft::iterator_traits<T*>::value_type		    value_type;
        typedef typename ft::iterator_traits<T*>::pointer			pointer;
        typedef typename ft::iterator_traits<T*>::reference			reference;
        // typedef typename ft::iterator_traits<T*>::iterator_category	iterator_category;
        typedef	std::random_access_iterator_tag	iterator_category; // for compare std:: with ft::
        typedef pointer iterator_type;

        RevIterator_v() { _ptr = NULL; }
        RevIterator_v( pointer ptr ) { _ptr = ptr; }
        RevIterator_v( const RevIterator_v<value_type>& It ) { _ptr = It.getPtr(); }
        virtual ~RevIterator_v() {}

        // Iterator_v<value_type>& operator=( const RevIterator_v<value_type>& It ) { _ptr = It.getPtr(); return *this; }
        RevIterator_v<value_type>& operator=( pointer ptr ) { _ptr = ptr; return *this; }
        RevIterator_v<value_type>& operator+=( const difference_type& move) { _ptr -= move; return *this; }
        RevIterator_v<value_type>& operator-=( const difference_type& move) { _ptr += move; return *this; }
        RevIterator_v<value_type>& operator++( void ) { --_ptr; return *this; }
        RevIterator_v<value_type>& operator--( void ) { ++_ptr; return *this; }
        RevIterator_v<value_type> operator++(int) { pointer tmp = _ptr; --_ptr; return tmp; }
        RevIterator_v<value_type> operator--(int) { pointer tmp = _ptr; ++_ptr; return tmp; }
        RevIterator_v<value_type> operator+( const difference_type& move )
        {
            pointer old = _ptr;
            _ptr -= move;
            pointer tmp = _ptr;
            _ptr = old;
            return tmp;
        }
        RevIterator_v<value_type> operator-( const difference_type& move )
        {
            pointer old = _ptr;
            _ptr += move;
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
std::ptrdiff_t operator-(const RevIterator_v<A> & lhs, const RevIterator_v<B> & rhs) { return (lhs.getPtr() - rhs.getPtr()); }
template<typename A, typename B>
bool operator==(const RevIterator_v<A> & lhs, const RevIterator_v<B> & rhs) { return lhs.getPtr() == rhs.getPtr(); }
template<typename A, typename B>
bool operator!=(const RevIterator_v<A> & lhs, const RevIterator_v<B> & rhs) { return !(lhs == rhs); }
template<typename A, typename B>
bool operator>(const RevIterator_v<A> & lhs, const RevIterator_v<B> & rhs) { return lhs.getPtr() > rhs.getPtr(); }
template<typename A, typename B>
bool operator<(const RevIterator_v<A> & lhs, const RevIterator_v<B> & rhs) { return lhs.getPtr() < rhs.getPtr(); }
template<typename A, typename B>
bool operator>=(const RevIterator_v<A> & lhs, const RevIterator_v<B> & rhs) { return lhs.getPtr() >= rhs.getPtr(); }
template<typename A, typename B>
bool operator<=(const RevIterator_v<A> & lhs, const RevIterator_v<B> & rhs) { return lhs.getPtr() <= rhs.getPtr(); }

}

#endif
