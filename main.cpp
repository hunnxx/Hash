#include <iostream>
#include "Map.h"
#include <set>

class A{
    int key = 10;
public:
    int getKey(){ return key; }
};

int main(){
    Map<int,int> test;
    std::cout << "PUT" << std::endl;
    std::cout << test.put(10, 1) << std::endl;
    std::cout << test.put(110, 2) << std::endl; 
    std::cout << test.put(210, 3) << std::endl; 
    std::cout << test.put(110, 4) << std::endl; 
    std::cout << test.put(310, 5) << std::endl; 
    std::cout << test.put(410, 6) << std::endl; 

    std::cout << "GET" << std::endl;
    std::cout << test.get(10) << std::endl;
    std::cout << test.get(110) << std::endl;
    std::cout << test.get(210) << std::endl;
    std::cout << test.get(310) << std::endl;
    std::cout << test.get(410) << std::endl;

    return 0;
}