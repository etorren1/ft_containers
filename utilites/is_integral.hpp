#ifndef __IS_INTEGRAL__
#define __IS_INTEGRAL__

namespace ft {

template< class T > struct remove_const                { typedef T type; };
template< class T > struct remove_const<const T>       { typedef T type; };

template <class Tp, Tp v>
struct integral_constant    {
	static  const Tp            value = v;
	typedef Tp                  value_type;
	typedef integral_constant   type;
	operator value_type() const {return value;}
};

typedef integral_constant<bool, true>  true_type;
typedef integral_constant<bool, false> false_type;

template <class T> struct is_integral                     : public false_type {};
template <>        struct is_integral<bool>               : public true_type {};
template <>        struct is_integral<char>               : public true_type {};
template <>        struct is_integral<signed char>        : public true_type {};
template <>        struct is_integral<unsigned char>      : public true_type {};
template <>        struct is_integral<wchar_t>            : public true_type {};
template <>        struct is_integral<char16_t>           : public true_type {};
template <>        struct is_integral<char32_t>           : public true_type {};
template <>        struct is_integral<short>              : public true_type {};
template <>        struct is_integral<unsigned short>     : public true_type {};
template <>        struct is_integral<int>                : public true_type {};
template <>        struct is_integral<unsigned int>       : public true_type {};
template <>        struct is_integral<long>               : public true_type {};
template <>        struct is_integral<unsigned long>      : public true_type {};
template <>        struct is_integral<long long>          : public true_type {};
template <>        struct is_integral<unsigned long long> : public true_type {};
template <>        struct is_integral<__int128_t>         : public true_type {};
template <>        struct is_integral<__uint128_t>        : public true_type {};

}

#endif