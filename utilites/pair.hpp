#ifndef __PAIR_HPP__
#define __PAIR_HPP__

namespace ft {

template< class U, class V >
struct pair
{
    typedef U first_type;
	typedef V second_type;

    first_type first;
    second_type second;

    pair() : first(), second() {}

    pair( const first_type& a, const second_type& b ) : first(a), second(b) {}

    template<class A, class S>
    pair ( const pair<A,S>& pr ) : first(pr.first), second(pr.second) {}

    ~pair() {}

    pair &operator=(const pair &pr) {
        first = pr.first;
        second = pr.second;
        return (*this);
    }

};

template <class U, class V>
pair<U, V> make_pair(U a, V b)
{
    return pair<U, V>(a, b);
}

template <class U, class V>
bool operator == (const pair<U, V>& a, const pair<U, V>& b) { return a.first == b.first && a.second == b.second; }

template <class U, class V>
bool operator != (const pair<U, V>& a, const pair<U, V>& b) { return !(a == b); }

template <class U, class V>
bool operator < (const pair<U, V>& a, const pair<U, V>& b) { return a.first < b.first || (!(a.first < b.first) && a.second < b.second); }

template <class U, class V>
bool operator > (const pair<U, V>& a, const pair<U, V>& b) { return a.first > b.first || (!(a.first > b.first) && a.second > b.second); }

template <class U, class V>
bool operator <= (const pair<U, V>& a, const pair<U, V>& b) { return !(a < b); }

template <class U, class V>
bool operator >= (const pair<U, V>& a, const pair<U, V>& b) { return !(a < b); }

}

#endif