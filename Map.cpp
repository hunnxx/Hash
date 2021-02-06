#include "Map.h"

// ---------------------------------------------------------------------------
// static
template <class K, class V>
int Map<K,V>::MAXIMUM_INITIAL_CAPACITY = INT_MAX;
// ---------------------------------------------------------------------------
// Map
template <class K, class V>
Map<K,V>::Map(int initCapacity){
    if(initCapacity < 0){
        // Error IllegalArgumentException
        // throw
    }
    if(initCapacity >= MAXIMUM_INITIAL_CAPACITY){
        // Error
        // throw 
    }
    size = 0;
    buckets = new Map<K,V>::Entry[initCapacity];
}

template <class K, class V>
Map<K,V>::~Map(){
    delete[] buckets;
}

template <class K, class V>
int Map<K,V>::getSize(){
    return size;
}

template <class K, class V>
bool Map<K,V>::isEmpty(){
    return size == 0;
}

template <class K, class V>
V Map<K,V>::put(K key, V value){
    return value;
}
// ---------------------------------------------------------------------------
// Map::Entry
// template <class K, class V>
// Map<K,V>::Entry::Entry(int hash, K key, V value){
//     this->hash = hash;
//     this->key = key;
//     this->value = value;
// }

template <class K, class V>
K Map<K,V>::Entry::getKey(){
    return key;
}

template <class K, class V>
V Map<K,V>::Entry::getValue(){
    return value;
}

template <class K, class V>
V Map<K,V>::Entry::setValue(V newValue){
    V oldValue = value;
    this->value = newValue;
    return oldValue;
}
// ---------------------------------------------------------------------------
// Explicit Template Instantiation
template class Map<int, int>;
// ---------------------------------------------------------------------------