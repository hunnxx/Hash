#include "Map.h"

#include <iostream>
#include <set>
#include <string>
#include <random>

using namespace std;

unsigned int hash(int key){
    unsigned long long a = 2147483647;
    int w = 48;
    int m = 32;
    key ^= key >> (w-m);
    return (a*key) >> (w-m);
}

int main(){
    // // To use a non-deterministic seed
    // random_device random_dev;
    // static mt19937 gen(random_dev());
    // // static mt19937 gen(3267);
    // uniform_int_distribution<> distr(0, 9999);

    Map<int, int> map;

    // for (int i = 0; i < 10; i++)
    // {
    //     int key = distr(gen);
    //     int val = distr(gen);
    //     cout << key << " : " << val << endl;
    //     map.put(key, val);
    // }

    map.put(10, 1);

    map.printBuckets();
    map.data.print(map.getSize(), map.getCapacity());

    return 0;
}