#include "Map.h"
#include <iostream>
#include <set>
#include <vector>

// ---------------------------------------------------------------------------
// static

template <class K, class V>
int Map<K,V>::MAXIMUM_INITIAL_CAPACITY = INT_MAX; // 2147483647

template <class K, class V>
int Map<K,V>::capacity = 10000;

template <class K, class V>
int Map<K,V>::hash(K key){
    // Hashing
    return key % capacity;
}

// ---------------------------------------------------------------------------
// Map

template <class K, class V>
Map<K,V>::Map(int initCapacity){
    if(initCapacity < 0){
        // Error IllegalArgumentException
        // throw
    }
    if(initCapacity > MAXIMUM_INITIAL_CAPACITY){
        // Error
        // throw 
    }
    size = 0;
    buckets = new Map<K,V>::Entry*[(capacity = initCapacity)];
}

template <class K, class V>
Map<K,V>::~Map(){
    for(int i = 0; i < capacity; i++) delete buckets[i];
    delete[] buckets;
}

template <class K, class V>
int Map<K,V>::getSize(){
    return (size < capacity) ? size : capacity;
}

template <class K, class V>
bool Map<K,V>::isEmpty(){
    return size == 0;
}

template <class K, class V>
typename Map<K,V>::Entry* Map<K,V>::searchEntry(K key){
    Map<K,V>::Entry *e = buckets[hash(key)];
    return e == nullptr ? NULL : e;
}

template <class K, class V>
bool Map<K,V>::containsKey(K key){
    // (key==null ? k==null : key.equals(k))
    Map<K,V>::Entry *e = searchEntry(key);
    return (key == NULL ? e == NULL : key == e->getKey());
}

template <class K, class V>
V Map<K,V>::get(K key){
    // NULL 확인 해야함
    // (key==null ? k==null : key.equals(k))
    Map<K,V>::Entry *e = searchEntry(key);
    return (key == NULL ? e->getKey() == NULL : 
    (key == e->getKey() ? e->getValue() : NULL));
}

template <class K, class V>
V Map<K,V>::put(K key, V value){
    // hash 계산
    int h = hash(key);
    Map<K,V>::Entry *e;
    if (buckets[h] == nullptr)
    { // 매핑된게 없음
        e = new Map<K,V>::Entry(h, key, value);
        buckets[h] = e;
        return NULL;
    } else { // 매핑된게 있음
        if(containsKey(key)){
            Map<K,V>::Entry *e = searchEntry(key);
            V oldValue = e->getValue();
            e->setValue(value);
            return oldValue;
        } else {
            // Probing
        }
    }
    return value;
}

template <class K, class V>
V Map<K,V>::remove(K key){}

template <class K, class V>
void Map<K,V>::putAll(Map<K,V> m){}

template <class K, class V>
void Map<K,V>::clear(){}

template <class K, class V>
std::set<K> Map<K,V>::keySet(){}

template <class K, class V>
std::vector<V> Map<K,V>::values(){}

template <class K, class V>
std::set<typename Map<K,V>::Entry> Map<K,V>::entrySet(){}

template <class K, class V>
int Map<K,V>::hashCode(){
    return 0;
}

template <class K, class V>
void Map<K,V>::forEach(std::function<void(K,V)> action){}

template <class K, class V>
void Map<K,V>::replaceAll(std::function<V(K,V)> func){}

template <class K, class V>
V Map<K,V>::putIfAbsent(K key, V value){}

template <class K, class V>
bool Map<K,V>::replace(K key, V oldValue, V newValue){}

template <class K, class V>
V Map<K,V>::replace(K key, V value){}

template <class K, class V>
V Map<K,V>::computeIfAbsent(K key, std::function<V(K)> mappingFunc){}

template <class K, class V>
V Map<K,V>::computeIfPresent(K key, std::function<V(K,V)> remappingFunc){}

template <class K, class V>
V Map<K,V>::compute(K key, std::function<V(K,V)> remappingFunc){}

template <class K, class V>
V Map<K,V>::merge(K key, V value, std::function<V(K,V)> remappingFunc){}

// ---------------------------------------------------------------------------
// Map::Entry

template <class K, class V>
Map<K,V>::Entry::Entry(int hashcode, K key, V value){
    this->hashcode = hashcode;
    this->key = key;
    this->value = value;
}

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

template <class K, class V>
bool Map<K,V>::Entry::equals(Map<K,V>::Entry e){
    // (e1.getKey()==null ?
    //   e2.getKey()==null : e1.getKey().equals(e2.getKey()))  &&
    //  (e1.getValue()==null ?
    //   e2.getValue()==null : e1.getValue().equals(e2.getValue()))
    return (key == NULL ? e.getKey() == NULL : key == e.getKey()) &&
    (value == NULL ? e.getValue() == NULL : value == e.getValue());
}

template <class K, class V>
int Map<K,V>::Entry::hashCode(){
    // (e.getKey()==null   ? 0 : e.getKey().hashCode()) ^
    //  (e.getValue()==null ? 0 : e.getValue().hashCode())
    return (key == NULL ? 0 : hash(key)) ^ 
    (value == NULL ? 0 : hash(value));
}

// ---------------------------------------------------------------------------
// Explicit Template Instantiation
template class Map<int, int>;
// ---------------------------------------------------------------------------