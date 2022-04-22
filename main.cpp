#include <iostream>
#include <string>
#include <deque>
#if 0//CREATE A REAL STL EXAMPLE
	#include <map>
	#include <stack>
	#include <vector>
	namespace ft = std;
    #define STD     1
#else
	#include "map.hpp"
	#include "stack.hpp"
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

#include <vector>

#define COUNT (MAX_RAM / (int)sizeof(Buffer))
int     main(void)
{
    STD ? std::cout << "\e[34mstd\e[31m::container\e[0m\n" : std::cout << "\e[32mft\e[31m::container\e[0m\n";

    // { // map

        // std::vector<int> v;
        // ft::map<int, int> mp;

        // for (int i = 0, j = 10; i < 30; ++i, ++j) {
        //     mp.insert(ft::make_pair(i, j));
        // }
        // ft::map<int, int> mp2(mp.begin(), mp.end());
        // ft::map<int, int>::iterator it = mp2.begin();
        // for (int i = 0; i < 30; ++i, it++) {
        //     std::cout << it->first << "," << it->second << "\n";
        //     v.push_back(it->first);
        //     v.push_back(it->second);
        // }
        // std::cout << "here\n";

        // ft::make_pair(5,5);
        // ft::pair<std::string, const int>("aasda", 4);
    //     ft::map<int, int>::iterator yol;
    //     ft::map<int, int>::iterator cyol;
    //     ft::pair<ft::map<int, int>::iterator, bool> its;
    //     ft::map<int, int> maps;
    //     ft::pair<const int,int> pr = ft::make_pair(7,7);
        
    //     maps.insert(ft::make_pair(6,6));
    //     maps.insert(ft::make_pair(34,34));
    //     maps.insert(ft::make_pair(12,12));
    //     maps.insert(ft::make_pair(3,3));
    //     maps.insert(ft::make_pair(79,79));
    //     maps.insert(ft::make_pair(79,79));
    //     maps.insert(ft::make_pair(79,79));
    //     // oth.insert(ft::make_pair(33,33));
    //     // oth.insert(ft::make_pair(22,22));
    //     // oth.insert(ft::make_pair(11,11));
    //     its = maps.insert(pr);
    //     its = maps.insert(pr);
    //     std::cout << "iter = " << its.second << " content:" << its.first->first << "," << its.first->second << "\n";
    //     maps.test();
    //     ft::map<int, int> oth;
    //     ft::map<int, int> soth(maps);
    //     oth = maps;
    //     // std::cout << "find:" << yol->first << "," << yol->second << "\n";
    //     maps.insert(yol, cyol);
    //     maps.clear();
    //     std::cout << "size = " << maps.size() << "\n";
    //     yol = maps.begin();
    //     cyol = maps.end();

    //     // yol = oth.begin();
    //     while (yol != maps.end())
    //     {
    //         std::cout << "content:" << yol->first << "," << yol->second << "\n";
    //         yol++;
    //     }



    //     yol = maps.begin();
    //     while (yol != maps.end())
    //     {
    //         std::cout << "content:" << yol->first << "," << yol->second << "\n";
    //         yol++;
    //     }
    //     // std::cout << yol->second << "----------------\n";

    //     maps.test();
    //     maps.insert(pr);
    //     std::cout << "map size = " << maps.size() << "\n";
    //     std::cout << maps[6] << "\n";
    //     std::cout << "map size = " << maps.size() << "\n";
    //     std::cout << maps[79] << "\n";
    //     std::cout << "map size = " << maps.size() << "\n";
    //     // std::cout << REDC << maps[5] << "\n";
    //     std::cout << RESETC;
    // }

    // { // vector
    //     ft::vector<int> arr;
    //     arr.push_back(100);
    //     arr.push_back(1);
    //     arr.push_back(2);
    //     arr.push_back(3);
    //     arr.push_back(4);
    //     arr.push_back(5);
    //     arr.push_back(6);
    //     arr.push_back(7);
    //     arr.push_back(8);
    //     arr.push_back(9);
    //     arr.push_back(874);

    //     ft::vector<std::string> str;
    //     str.push_back("string");
    //     ft::stack<std::string> st;

    //     ft::stack<int, ft::vector<int> > first(arr);
    //     ft::stack<int, ft::vector<int> > second(arr);

    //     if (second != first)
    //         std::cout <<  "1 != 2\n";
    //     std::cout << "stack size = " << first.size() << "\n";
    //     // ft::stack<int, ft::vector<int> > second;

    //     ft::vector<int>::iterator it;
    //     it = arr.erase(arr.begin() + 2, arr.end() - 4);
    //     it = arr.erase(arr.begin() + 2, arr.end() - 1);
    //     std::cout << "it = " << *it << "\n";
    //     ft::vector<int> opt(arr.begin(), arr.end());
    //     // ft::vector<int> opt;
    //     it = opt.begin();
    //     opt.assign(5, 10);
    //     opt.assign(arr.begin(), arr.end());
    //     opt.insert(opt.begin(), 4);
    //     opt.reserve(30);
    //     opt.insert(it, 4, 100);
    //     opt.insert(opt.begin(), arr.begin(), arr.end());
    //     cont_data(opt.data(), opt.size());
    //     std::cout << "\e[33msize = " << opt.size() << "\n";
    //     std::cout << "\e[33mcapacity = " << opt.capacity() << "\n";
    //     std::cout << "\e[33mempty = " << opt.empty() << "\n";
    //     std::cout << "\e[33mmax_size = " << opt.max_size() << "\n";

    //     ft::vector<std::string> v1;
    //     v1.insert(v1.begin(), 5, "str");
    //     ft::vector<std::string> v2;
    //     v2.insert(v2.begin(), 5, "str");
    //     if (v1 == v2)
    //         std::cout << "true\n";
    // }
    if (ft::is_integral<int>())
        std::cout << "true\n";
    return (0);
}