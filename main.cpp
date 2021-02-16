#include "Map.h"

#include <iostream>
#include <set>
#include <random>
#include <vector>

using namespace std;

void autoProcessing(){
    // To use a non-deterministic seed
    random_device random_dev;
    static mt19937 gen(random_dev());
    uniform_int_distribution<> distr(0, 9999);

    Map<int, int> map;

    vector< pair<int,int> > vec_input;
    vector< pair<int,int> >::iterator v_it;

    // PUT
    for (int i = 0; i < 20; i++)
    {
        int key = distr(gen);
        int val = distr(gen);
        vec_input.push_back(make_pair(key,val));
        map.put(key, val);
    }

    // GET
    cout << "\n\r\n\rPUT : ";
    for(v_it = vec_input.begin(); v_it != vec_input.end(); v_it++){
        cout << "{" << v_it->first << ":" << v_it->second << "}";
    }
    cout<< "\n\rGET : ";
    for(v_it = vec_input.begin(); v_it != vec_input.end(); v_it++){
        cout << "{" << v_it->first << ":" << map.get(v_it->first) << "}";
    }
    cout<<endl;
    map.data.print(map.getSize(), map.getCapacity());
    map.printBuckets();
    
}

void Processing(){
    static mt19937 gen(3267);
    uniform_int_distribution<> distr(0, 9999);

    Map<int, int> map;

    vector< pair<int,int> > vec_input;
    vector< pair<int,int> >::iterator v_it;

    // PUT
    for (int i = 0; i < 20; i++)
    {
        int key = distr(gen);
        int val = distr(gen);
        vec_input.push_back(make_pair(key,val));
        map.put(key, val);
    }

    // GET
    cout << "\n\r\n\rPUT : ";
    for(v_it = vec_input.begin(); v_it != vec_input.end(); v_it++){
        cout << "{" << v_it->first << ":" << v_it->second << "}";
    }
    cout<< "\n\rGET : ";
    for(v_it = vec_input.begin(); v_it != vec_input.end(); v_it++){
        cout << "{" << v_it->first << ":" << map.get(v_it->first) << "}";
    }
    cout<<endl;
    map.data.print(map.getSize(), map.getCapacity());
    map.printBuckets();

    // REPLACE
    cout << "\n\r\n\rREPLACE" << endl;
    int cnt = 0;
    for(v_it = vec_input.begin(); v_it != vec_input.end(); v_it++){
        map.replace(v_it->first, cnt++);
    }
    map.printBuckets();

    // REMOVE
    cout << "\n\r\n\rREMOVE1 : 1762 return "; cout << map.remove(1762) << endl;
    map.printBuckets();
    cout << "\n\r\n\rREMOVE2 : 9070 return "; cout << map.remove(9070) << endl;
    map.printBuckets();
}

int main(){
    int n;
    while(n > 0){
        cout << "\n\r\n\r\n\rSELECT T(0) AP(1) P(2) : ";
        cin >> n;
        switch (n)
        {
        case 1:
            autoProcessing(); // 자동
            break;
        case 2:
            Processing(); // 수동
            break;
        default:
            break;
        }
    }   
    return 0;
}