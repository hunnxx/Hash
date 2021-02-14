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
int Map<K,V>::PROB = 3;

template <class K, class V>
float Map<K,V>::OFFSET = 0.6;

template <class K, class V>
int Map<K,V>::computeHash(K key){
    // Hashing
    return key % CAPACTIY;
}

// ---------------------------------------------------------------------------
// Map

template <class K, class V>
Map<K,V>::Map(int init_capacity){
    if(init_capacity < 0){
        // Error IllegalArgumentException
        // throw
    }
    if(init_capacity > MAXIMUM_INITIAL_CAPACITY){
        // Error
        // throw
    }
    size = 0;
    buckets = new Map<K,V>::Entry*[(CAPACTIY = init_capacity)];
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
    std::set< std::pair<K,V> > entries = entrySet();
    int old_capacity = CAPACTIY; CAPACTIY *= 2;
    
    int i;
    for(i = 0; i < old_capacity; i++){
        delete buckets[i]; buckets[i] = nullptr;
    }
    delete[] buckets; buckets = nullptr;
    buckets = new Map<K,V>::Entry*[CAPACTIY];

    typename std::set< std::pair<K,V> >::iterator it;
    for (it = entries.begin(); it != entries.end(); it++) put(it->first, it->second);
}

template <class K, class V>
bool Map<K,V>::isEmpty(){
    return size == 0;
}

template <class K, class V>
int Map<K,V>::searchEntry(K key){
    int hash = computeHash(key);
    while(buckets[hash] == nullptr ? 0 : (key == buckets[hash]->getKey() ? 0 : 1)) hash++ % CAPACTIY;
    return hash;
}

template <class K, class V>
bool Map<K,V>::containsKey(K key){
    // (key==null ? k==null : key.equals(k))
    int pos = searchEntry(key);
    // return (key == NULL ? e == nullptr : (e == nullptr ? false : key == e->getKey()));
    return (key == NULL ? buckets[pos] == nullptr : (buckets[pos] == nullptr ? false : true));
}

template <class K, class V>
bool Map<K,V>::containsValue(V value){
    for(int i = 0; i < CAPACTIY; i++){
        if(buckets[i]){
            if(buckets[i]->getValue() == value) return true;
        }
    }
    return false;
}

template <class K, class V>
V Map<K,V>::get(K key){
    // (key==null ? k==null : key.equals(k))
    int pos = searchEntry(key);
    return (key == NULL ? buckets[pos] == nullptr : (buckets[pos] == nullptr) ? NULL : buckets[pos]->getValue());
}

template <class K, class V>
V Map<K,V>::put(K key, V value){
    // UnsupportedOperationException
    // ClassCastException
    // NullPointerException
    // IllegalArgumentException
    int cur_pos = computeHash(key);
    int next_pos = searchEntry(key);
    if(buckets[next_pos]){
        std::cout << "REPLACE" << std::endl;
        V oldValue = buckets[next_pos]->getValue();
        buckets[next_pos]->setValue(value);
        return oldValue;
    }
    if(next_pos - cur_pos > PROB || size > CAPACTIY * OFFSET){
        std::cout << "RESIZE" << std::endl;
        resize();
        cur_pos = computeHash(key);
        next_pos = searchEntry(key);
    }
    std::cout << "NEW PUT : " << next_pos << std::endl;
    buckets[next_pos] = new Map<K,V>::Entry(cur_pos, key, value);
    size++;
    return NULL;
}

template <class K, class V>
V Map<K,V>::remove(K key){
    // UnsupportedOperationException
    std::cout << "DELETION" << std::endl;
    int cur_pos = searchEntry(key);
    if(buckets[cur_pos] == nullptr) return NULL;

    V oldValue = buckets[cur_pos]->getValue();
    int hash = buckets[cur_pos]->getHash();
    delete buckets[cur_pos]; buckets[cur_pos] = nullptr;
    size--;

    int next_pos = (cur_pos + 1) % CAPACTIY;
    while(buckets[next_pos]){
        if(buckets[next_pos]->getHash() != hash) break;
        std::cout << "START" << std::endl;
        buckets[next_pos - 1] = new Map<K,V>::Entry(hash, buckets[next_pos]->getKey(), buckets[next_pos]->getValue());
        delete buckets[next_pos]; buckets[next_pos] = nullptr;
        next_pos = (next_pos + 1) % CAPACTIY;
    }

    return oldValue;
}

template <class K, class V>
bool Map<K,V>::remove(K key, V value){
    return false;
}

template <class K, class V>
void Map<K,V>::putAll(Map<K,V> m){
    // UnsupportedOperationException
    // ClassCastException
    // NullPointerException
    // IllegalArgumentException
    std::set< std::pair<K,V> > entries = m.entrySet();
    typename std::set< std::pair<K,V> >::iterator it;
    for(it = entries.begin(); it != entries.end(); it++) put(it->first, it->second);
}

template <class K, class V>
void Map<K,V>::clear(){
    // UnsupportedOperationException
    size = 0;
    for(int i = 0; i < CAPACTIY; i++) {
        delete buckets[i]; buckets[i] = nullptr;
    }
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
    std::set<K> keys = keySet();
    typename std::set<K>::iterator it;
    int pos; int sum = 0;
    for(it = keys.begin(); it != keys.end(); it++) {
        pos = searchEntry(*it);
        sum += buckets[pos]->hashCode();
    }
    return sum;
}

// template <class K, class V>
// V getOrDefault(Objcet key, V defaultValue){}

// template <class K, class V>
// V Map<K,V>::putIfAbsent(K key, V value){}

template <class K, class V>
V Map<K,V>::replace(K key, V value){
    // NullPointerException
    // IllegalArgumentException
    if(containsKey(key)) return put(key, value);
    else return NULL;
}

template <class K, class V>
bool Map<K,V>::replace(K key, V oldValue, V newValue){
    // ClassCastException
    // NullPointerException
    // IllegalArgumentException
    int pos = searchEntry(key);
    if(buckets[pos] ? (buckets[pos]->getValue() == oldValue ? true : false) : false) return put(key, newValue);
    else return false;
}

// template <class K, class V>
// void Map<K,V>::replaceAll(std::function<V(K,V)> func){
//     // UnsupportedOperationException
//     // ClassCastException
//     // NullPointerException
//     // ConcurrentModificationException
// }

// template <class K, class V>
// void Map<K,V>::forEach(std::function<void(K,V)> action){
//     // NullPointerException
//     // ConcurrentModificationException
// }

// template <class K, class V>
// V Map<K,V>::computeIfAbsent(K key, std::function<V(K)> mappingFunc){
//     // NullPointerException
// }

// template <class K, class V>
// V Map<K,V>::computeIfPresent(K key, std::function<V(K,V)> remappingFunc){
//     // NullPointerException
// }

// template <class K, class V>
// V Map<K,V>::compute(K key, std::function<V(K,V)> remappingFunc){
//     // NullPointerException
// }

// template <class K, class V>
// V Map<K,V>::merge(K key, V value, std::function<V(K,V)> remappingFunc){
//     // NullPointerException
// }

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