#include <iostream>
#include "Map.h"
#include <set>

int main(){
    std::cout << "START" << std::endl;
    Map<int,int> test;
    std::cout << test.put(10,20) << std::endl; // new put
    std::cout << test.put(20,30) << std::endl;
    std::cout << test.put(110,40) << std::endl;

    std::cout << "KEYS" << std::endl;
    std::set<int> keys = test.keySet();
    for (std::set<int>::iterator it = keys.begin(); it != keys.end(); it++)
    {
        std::cout << *it << std::endl;
    }
    
    std::cout << "VALUES" << std::endl;
    std::vector<int> values = test.values();
    for (std::vector<int>::iterator it = values.begin(); it < values.end(); it++)
    {
        std::cout << *it << std::endl;
    }

    std::cout << "ENTRIES" << std::endl;
    std::set< std::pair<int,int> > entries = test.entrySet();
    for (std::set< std::pair<int,int> >::iterator it = entries.begin(); it != entries.end(); it++)
    {
        std::cout << it->first << " : " << it->second << std::endl;
    }
    
    return 0;
}