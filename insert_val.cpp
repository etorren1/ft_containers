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
	// #include "map.hpp"
	// #include "stack.hpp"
    #include <vector>
	#include "vector.hpp"
    #define STD     0
#endif

#include <stdlib.h>

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
#define _ratio 1000
struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};


class B {
public:
	char *l;
	int i;
	B():l(nullptr), i(1) {};
	B(const int &ex) {
		this->i = ex;
		this->l = new char('a');
	};
	virtual ~B() {
		delete this->l;
		this->l = nullptr;
	};
};

class A : public B {
public:
	A():B(){};
	A(const B* ex){
		this->l = new char(*(ex->l));
		this->i = ex->i;
		if (ex->i == -1) throw "n";
	}
	~A() {
		delete this->l;
		this->l = nullptr;
	};
};

void    cont_cmp(int *p, int *d, size_t count)
{
    for (size_t i = 0; i < count; i++)
    {
        if (p[i] != d[i])
            std::cout << "i = " << i << +p[i] << " != " << +d[i] << "\n";
    }
}

// template <typename T>
// std::vector<int> insert_test_1(std::vector<T> vector) {
//     std::vector<int> v;
//     vector.assign(2600 * _ratio, 1);
//     g_start1 = timer();
//     v.push_back(*(vector.insert(vector.end() - 800 * _ratio, 44)));
//     g_end1 = timer();
//     v.push_back(vector.size());
//     v.push_back(vector.capacity());
//     std::unique_ptr<B> k2(new B(3));
//     std::unique_ptr<B> k3(new B(4));
//     std::unique_ptr<B> k4(new B(-1));
//     std::vector<A> vv;
//     std::vector<B*> v1;

//     v1.push_back(&(*k2));
//     v1.push_back(&(*k3));
//     v1.push_back(&(*k4));
//     try { vv.insert(vv.begin(), v1.begin(), v1.end()); }
//     catch (...) {
//     	v.push_back(vv.size());
//     	v.push_back(vv.capacity());
//     }
//     return v;
// }

int main() {
    // ft::vector<int> vector;
    // std::vector<int> v;
    // vector.assign(2600 * _ratio, 1);
    // v.push_back(*(vector.insert(vector.end() - 800 * _ratio, 44)));
    // v.push_back(vector.size());
    // v.push_back(vector.capacity());
    std::unique_ptr<B> k2(new B(3));
    std::unique_ptr<B> k3(new B(4));
    std::unique_ptr<B> k4(new B(-1));
    ft::vector<A> vv;
    ft::vector<B*> v1;

    // std::vector<int> ss;
    // ss.insert(ss.begin(), 10, 8);
    // ft::vector<int> ar;
    // ar.insert(ar.begin(), ss.begin(), ss.end());
        // cont_cmp(ss.data(), ar.data(), ss.size());

    // vv.push_back();

    v1.push_back(&(*k2));
    v1.push_back(&(*k3));
    v1.push_back(&(*k4));
    // std::cout << "   it[" << 0 << "]= " << *(v1.begin() + 0) << "\n";
    // std::cout << "   it[" << 0 << "]= " << *(v1.begin() + 1) << "\n";
    // std::cout << "   it[" << 0 << "]= " << *(v1.begin() + 2) << "\n";
    // std::cout << "first[" << 0 << "]= " << v1[0] << "\n";
    // std::cout << "first[" << 1 << "]= " << v1[1] << "\n";
    // std::cout << "first[" << 2 << "]= " << v1[2] << "\n";
    // std::cout << "-------------------\n";
    // try { 
        vv.insert(vv.begin(), v1.begin(), v1.end());
    // }
    // catch (...) {
    // 	v.push_back(vv.size());
    // 	v.push_back(vv.capacity());
    // }

    std::cout << "endmain!\n";
    return 0;
}
