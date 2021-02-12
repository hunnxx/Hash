#include "Map.h"

#include <iostream>
#include <set>
#include <vector>

// ---------------------------------------------------------------------------
// static

template <class K, class V>
int Map<K,V>::MAXIMUM_INITIAL_CAPACITY = INT_MAX; // 2147483647

template <class K, class V>
int Map<K,V>::CAPACTIY = 100;

template <class K, class V>
int Map<K,V>::computeHash(K key){
    // Hashing
    return key % CAPACTIY;
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
    buckets = new Map<K,V>::Entry*[(CAPACTIY = initCapacity)];
}

template <class K, class V>
Map<K,V>::~Map(){
    for(int i = 0; i < CAPACTIY; i++) delete buckets[i];
    delete[] buckets;
}

template <class K, class V>
int Map<K,V>::getSize(){
    return (size < CAPACTIY) ? size : CAPACTIY;
}

template <class K, class V>
void Map<K,V>::resize(){
    std::set<K> keyset = keySet();
    int oldCapacity = CAPACTIY; CAPACTIY *= 2;
    std::cout << "RESIZE " << CAPACTIY << std::endl;
    Map<K,V>::Entry **newBuckets = new Map<K,V>::Entry*[CAPACTIY];
    
    Map<K,V>::Entry *e; int hash; K key; V value;
    for(typename std::set<K>::iterator it = keyset.begin(); it != keyset.end(); it++) {
        e = searchEntry(*it);
        hash = e->getHash();
        key = e->getKey();
        value = e->getValue();
        newBuckets[hash] = new Map<K,V>::Entry(hash, key, value);
    }

    for(int i = 0; i < oldCapacity; i++) delete buckets[i];
    delete[] buckets;
    buckets = newBuckets;
}

template <class K, class V>
bool Map<K,V>::isEmpty(){
    return size == 0;
}

template <class K, class V>
typename Map<K,V>::Entry* Map<K,V>::searchEntry(K key){
    Map<K,V>::Entry *e; int hash = computeHash(key);
    do{
        e = buckets[hash++]; // Linear Probing
    }while(e == nullptr ? 0 : (key == e->getKey() ? 0 : 1));
    return e;
}

template <class K, class V>
bool Map<K,V>::containsKey(K key){
    // (key==null ? k==null : key.equals(k))
    Map<K,V>::Entry *e = searchEntry(key);
    return (key == NULL ? e == NULL : (e == nullptr ? NULL : key == e->getKey()));
}

template <class K, class V>
bool Map<K,V>::containsValue(V value){}

template <class K, class V>
V Map<K,V>::get(K key){
    // NULL 확인 해야함
    // (key==null ? k==null : key.equals(k))

    // Map<K,V>::Entry *e = searchEntry(key));
    // return (key == NULL ? e->getKey() == NULL : 
    // (key == e->getKey() ? e->getValue() : NULL));

    // Map<K,V>::Entry *e;
    // if(e = searchEntry(key)){
    //     return (key == NULL ? e->getKey() == NULL : (key == e->getKey() ? e->getValue() : NULL));
    // } else return NULL;

    Map<K,V>::Entry *e;
    return (e = searchEntry(key)) ? (key == NULL ? e->getKey() == NULL : (key == e->getKey() ? e->getValue() : NULL)) : NULL;
}

template <class K, class V>
V Map<K,V>::put(K key, V value){
    // UnsupportedOperationException
    // ClassCastException
    // NullPointerException
    // IllegalArgumentException
    return putVal(computeHash(key), key, value);
}

template <class K, class V>
V Map<K,V>::putVal(int hash, K key, V value){
    Map<K,V>::Entry *e;
    if(buckets[hash] == nullptr){
        std:: cout << "NEW PUT : " <<  hash << std::endl;
        e = new Map<K,V>::Entry(hash, key, value);
        buckets[hash] = e;
        size++;
        return NULL;
    } else {
        if(containsKey(key)){
            std::cout << "REPLACE : " << hash << std::endl;
            e = searchEntry(key);
            V oldValue = e->getValue();
            e->setValue(value);
            return oldValue;
        } else {
            // Linear Probing
            std::cout << "Probing Next: " << hash + 1 << std::endl;
            return putVal(++hash, key, value);
        }
    }
}

template <class K, class V>
V Map<K,V>::remove(K key){
    // UnsupportedOperationException
    Map<K,V>::Entry *e;
    int hash = computeHash(key);
}

template <class K, class V>
void Map<K,V>::putAll(Map<K,V> m){
    // UnsupportedOperationException
    // ClassCastException
    // NullPointerException
    // IllegalArgumentException
}

template <class K, class V>
void Map<K,V>::clear(){
    // UnsupportedOperationException
    size = 0;
    for(int i = 0; i < CAPACTIY; i++) delete buckets[i];
}

template <class K, class V>
std::set<K> Map<K,V>::keySet(){
    std::set<K> keyset; Map<K,V>::Entry *e;
    for(int i = 0; i < CAPACTIY; i++){
        if((e = buckets[i])) keyset.insert(e->getKey());
    }
    return keyset;
}

template <class K, class V>
std::vector<V> Map<K,V>::values(){
    std::vector<V> valueVector; Map<K,V>::Entry *e;
    for(int i = 0; i < CAPACTIY; i++){
        if((e = buckets[i])) valueVector.push_back(e->getValue());
    }
    return valueVector;
}

template <class K, class V>
std::set< std::pair<K,V> > Map<K,V>::entrySet(){
    std::set< std::pair<K,V> > entryset; Map<K,V>::Entry *e;
    std::pair<K,V> p;
    for(int i = 0; i < CAPACTIY; i++){
        if((e = buckets[i])) {
            p = std::make_pair(e->getKey(), e->getValue());
            entryset.insert(p);
        }
    }
    return entryset;
}

// template <class K, class V>
// bool Map<K,V>::equasl(Object o){}

template <class K, class V>
int Map<K,V>::hashCode(){
    return 0;
}

// template <class K, class V>
// V getOrDefault(Objcet key, V defaultValue){}

template <class K, class V>
void Map<K,V>::forEach(std::function<void(K,V)> action){
    // NullPointerException
    // ConcurrentModificationException
}

template <class K, class V>
void Map<K,V>::replaceAll(std::function<V(K,V)> func){
    // UnsupportedOperationException
    // ClassCastException
    // NullPointerException
    // ConcurrentModificationException
}

template <class K, class V>
V Map<K,V>::putIfAbsent(K key, V value){}

template <class K, class V>
bool Map<K,V>::remove(K key, V Value){
    // if (containsKey(key) && Objects.equals(map.get(key), value)) {
    //     map.remove(key);
    //     return true;
    // } else
    //     return false;
}

template <class K, class V>
bool Map<K,V>::replace(K key, V oldValue, V newValue){
    // ClassCastException
    // NullPointerException
    // IllegalArgumentException
}

template <class K, class V>
V Map<K,V>::replace(K key, V value){
    // NullPointerException
    // IllegalArgumentException
}

template <class K, class V>
V Map<K,V>::computeIfAbsent(K key, std::function<V(K)> mappingFunc){
    // NullPointerException
}

template <class K, class V>
V Map<K,V>::computeIfPresent(K key, std::function<V(K,V)> remappingFunc){
    // NullPointerException
}

template <class K, class V>
V Map<K,V>::compute(K key, std::function<V(K,V)> remappingFunc){
    // NullPointerException
}

template <class K, class V>
V Map<K,V>::merge(K key, V value, std::function<V(K,V)> remappingFunc){
    // NullPointerException
}

// ---------------------------------------------------------------------------
// Map::Entry

template <class K, class V>
Map<K,V>::Entry::Entry(int hash, K key, V value){
    this->hash = hash;
    this->key = key;
    this->value = value;
}

template <class K, class V>
int Map<K,V>::Entry::getHash(){
    // IllegalArgumentException
    return hash;
}

template <class K, class V>
K Map<K,V>::Entry::getKey(){
    // IllegalArgumentException
    return key;
}

template <class K, class V>
V Map<K,V>::Entry::getValue(){
    // IllegalArgumentException
    return value;
}

template <class K, class V>
V Map<K,V>::Entry::setValue(V newValue){
    // UnsupportedOperationException
    // ClassCastException
    // NullPointerException
    // IllegalArgumentException
    // IllegalStateException
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
    return (key == NULL ? 0 : computeHash(key)) ^ 
    (value == NULL ? 0 : computeHash(value));
}

// ---------------------------------------------------------------------------
// Explicit Template Instantiation
template class Map<int, int>;
// ---------------------------------------------------------------------------