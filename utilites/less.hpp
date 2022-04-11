#ifndef __LESS_H__
#define __LESS_H__

namespace ft{

	template<class argument_one, class argument_two, class result>
	struct binary_function {
		typedef argument_one	first_argument_type;
		typedef argument_two	susecond_argument_type;
		typedef result			result_type;
	};
	
	template <class T>
		struct less : public binary_function<T, T, bool> {
			bool operator () (const T& a, const T& b) const {
				return a < b;
			}
		};
};

#endif