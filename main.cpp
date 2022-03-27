#include <iostream>
#include <string>
#include <deque>
#if 0 //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <stack>
	#include <vector>
	namespace ft = std;
    #define STD     1
#else
	// #include "map.hpp"
	// #include "stack.hpp"
	#include "vector.hpp"
    #define STD     0
#endif

#include <stdlib.h>

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};


void    cont_data(const int *p, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        std::cout << "i = " << i << " >> " << +p[i] << "\n";
    }
}

#define COUNT (MAX_RAM / (int)sizeof(Buffer))
int     main(void)
{
    STD ? std::cout << "\e[34mstd\e[31m::container\e[0m\n" : std::cout << "\e[32mft\e[31m::container\e[0m\n";


    
    ft::vector<int> arr;
    arr.push_back(0);
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    arr.push_back(4);
    arr.push_back(5);
    // arr.reserve(10);
    // std::cout << arr.back() << "\n";
    // std::cout << ">>= " << arr.back() << "\n";
    // arr.pop_back();
    // arr.reserve(15);
    // arr.resize(10);
    // cont_data(arr.data(), arr.size());
    // arr.clear();
    // cont_data(arr.data(), arr.size());
    ft::vector<int> opt;

    ft::vector<int>::const_iterator it;
    ft::vector<int>::iterator at;
    ft::vector<int>::iterator st;
    it = arr.begin();
    at = arr.begin();
    it = at = st;
    // at = it; // doesn't work
    ft::vector<int>::const_iterator tt(it);
    if ( at == it )
        std::cout << "at == it\n";
    at++;
    if ( at != tt )
        std::cout << "at != tt\n";
    if ( at > tt )
        std::cout << "at > tt\n";
    at = arr.begin() + 3;
    std::cout << "iterator_begin = " << (*at) << "\n";
    

    opt = arr;
    opt.assign(3, 4);
    // // arr.swap(opt);
    cont_data(opt.data(), opt.size());
    // arr.push_back(3);
    // arr.push_back(3);
    // arr.push_back(3);
    // arr.reserve(4);
    std::cout << "\e[33msize = " << opt.size() << "\n";
    std::cout << "\e[33mcapacity = " << opt.capacity() << "\n";
    std::cout << "\e[33mempty = " << opt.empty() << "\n";
    std::cout << "\e[33mmax_size = " << opt.max_size() << "\n";
    return (0);
}