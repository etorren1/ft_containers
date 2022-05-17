#include <iostream>
#include <string>
#include <deque>
#if 0//CREATE A REAL STL EXAMPLE
	#include <map>
	#include <stack>
	#include <vector>
	namespace ft;
    namespace std;
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

class MapBoolTest {
public:
	std::map<int, int> m1, m2, m3, m4;
	std::map<std::string, std::string> m5, m6, m7, m8, m9;
	ft::map<int, int> mp1, mp2, mp3, mp4;
    ft::map<std::string, std::string> mp5, mp6, mp7, mp8, mp9;

	MapBoolTest() {
		m1.insert(std::make_pair(2, 3)); mp1.insert(ft::make_pair(2, 3));
		m2.insert(std::make_pair(3, 3)); mp2.insert(ft::make_pair(3, 3));
		m3.insert(std::make_pair(3, 4)); mp3.insert(ft::make_pair(3, 4));
		m4.insert(std::make_pair(4, 4)); mp4.insert(ft::make_pair(4, 4));
		m4.insert(std::make_pair(4, 5)); mp4.insert(ft::make_pair(4, 5));
		m5.insert(std::make_pair("123", "123")); mp5.insert(ft::make_pair("123", "123"));
		m6.insert(std::make_pair("123", "124")); mp6.insert(ft::make_pair("123", "124"));
		m7.insert(std::make_pair("124", "123")); mp7.insert(ft::make_pair("124", "123"));
		m8.insert(std::make_pair("12", "123")); mp8.insert(ft::make_pair("12", "123"));
		m9.insert(std::make_pair("123", "12")); mp9.insert(ft::make_pair("123", "12"));
	}
};

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
        // ft::pair<ft::map<int, int>::iterator, bool> its;
        // ft::pair<const int,int> pr = ft::make_pair(7,7);
        ft::map<int, int>::iterator yol;
        ft::map<int, int>::iterator cyol;
        ft::map<int, int> maps;
        
        maps.insert(ft::make_pair(6,6));
        maps.insert(ft::make_pair(34,34));
        maps.insert(ft::make_pair(12,12));
        maps.insert(ft::make_pair(3,3));
        maps.insert(ft::make_pair(1,1));
        maps.insert(ft::make_pair(2,2));
        maps.insert(ft::make_pair(9,9));
        maps.insert(ft::make_pair(4,4));
        maps.insert(ft::make_pair(55,55));
        maps.insert(ft::make_pair(79,79));
        maps.insert(ft::make_pair(79,79));
        maps.insert(ft::make_pair(79,79));
        yol = maps.begin();
        cyol = maps.end();
        ft::map<int, int> oth;
        // oth = maps;
        oth.insert(ft::make_pair(100,100));
        oth.insert(ft::make_pair(1006,1006));
        oth.insert(ft::make_pair(1700,1700));

        // maps.clear();

        ft::map<int, int>::reverse_iterator ryol = oth.rbegin();
        ft::map<int, int>::reverse_iterator rcyol;
        
        yol = maps.begin();
        while (yol != maps.end())
        {
            std::cout << "content:" << yol->first << "," << yol->second << " " << \
            &yol->first << "," << &yol->second << "\n";
            // std::cout << "content:" << &(*ryol) << "\n";
            yol++;
        }

        // maps.swap(oth);

        // yol = maps.begin();
        // while (yol != maps.end())
        // {
        //     std::cout << "content:" << yol->first << "," << yol->second << " " << \
        //     &yol->first << "," << &yol->second << "\n";
        //     // std::cout << "content:" << &(*ryol) << "\n";
        //     yol++;
        // }

        // maps.swap(oth);

        // while (1)
        // {

        // }

        // oth.equal_range(12);

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

        // for (ft::vector<int>::iterator it = v.begin(); it != v.end(); it++)
        // {
        //     std::cout << *it << " --\n";
        // }


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
    return (0);
}