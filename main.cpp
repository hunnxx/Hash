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

    // 0. null에 대한 처리 수정
    // 1. 0이 들어오는 상황
    // 2. 충돌 및 중간에 값 존재할 때, remove 처리
    // 1 2 2 상황
    // 1 3 2 2 상황
    // 1 - 2 2 상황
    // 2 3 2 2 4 상황
    // 2 1 상황

    cout << "INPUT" << endl;
    cout << map.put(2, 1) << endl; // 2
    cout << map.put(3, 2) << endl; // 3
    cout << map.put(19, 3) << endl; // 2 -> 4
    cout << map.put(36, 4) << endl; // 2 -> 5
    cout << map.put(0, 5) << endl; // 0
    cout << map.put(6, 6) << endl; // 6

    cout << "REMOVE" << endl;
    // cout << map.remove(2) << endl;

    cout << "GET" << endl;
    cout << map.get(0) << endl;

    map.printBuckets();
    map.data.print(map.getSize(), map.getCapacity());

    return 0;
}