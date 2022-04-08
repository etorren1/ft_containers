#ifndef __STACK_HPP__
#define __STACK_HPP__

#include "vector.hpp"

namespace ft {

template <typename T, class Container = ft::vector<T> >
class stack {
	public:
		typedef Container							container_type;
		typedef typename Container::value_type		value_type;
		typedef typename Container::size_type		size_type;

		explicit stack (const container_type& ctnr) : _container(ctnr) {}
		stack( void ): _container(container_type()) {}
		stack(const stack& other) : _container(other._container){}
		stack& operator = (const stack& other){ if (this == &other) return *this; _container = other._container; return *this; }

		size_type	size( void ) const { return _container.size(); }
		bool empty( void ) const { return _container.empty(); }
		value_type& top( void ) { return _container.back(); }
		const value_type& top( void ) const { return _container.back(); }
		void push (const value_type& val) { _container.push_back(val); }
		void pop( void ) { _container.pop_back(); }
	
		template <class Y, class X>
		friend bool operator == (const stack<Y, X> &lhs, const stack<Y, X> &rhs);
		template <class Y, class X>
		friend bool operator > (const stack<Y, X> &lhs, const stack<Y, X> &rhs);
		template <class Y, class X>
		friend bool operator >= (const stack<Y, X> &lhs, const stack<Y, X> &rhs);

	protected:
		container_type	_container;

};

template <class T, class Container>
bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return lhs._container == rhs._container; }
template <class T, class Container>
bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return !(lhs == rhs); }
template <class T, class Container>
bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return lhs._container > rhs._container; }
template <class T, class Container>
bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return rhs > lhs; }
template <class T, class Container>
bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return lhs._container >= rhs._container; }
template <class T, class Container>
bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return rhs >= lhs; }
}

#endif