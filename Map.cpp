#include "Map.h"
#include "Data.h"

#include <iostream>
#include <set>
#include <vector>

using namespace std;

// ---------------------------------------------------------------------------
// static

template <class K, class V>
int Map<K,V>::MAXIMUM_INITIAL_CAPACITY = INT_MAX; // 2147483647

template <class K, class V>
int Map<K,V>::CAPACTIY = 17;

template <class K, class V>
int Map<K,V>::PROB = CAPACTIY * 0.5;

template <class K, class V>
float Map<K,V>::OFFSET = 0.5;

template <class K, class V>
unsigned int Map<K,V>::computeHash(K key){
    // Multiplicative Hashing
    unsigned long long a = 2147483647;
    int w = 48; int m = 32;
    key ^= key >> (w-m);
    return ((a*key) >> (w-m)) % CAPACTIY;
}

// ---------------------------------------------------------------------------
// Map

template <class K, class V>
Map<K,V>::Map(int init_capacity){
    if(init_capacity < 0) init_capacity = CAPACTIY;
    else if(init_capacity > MAXIMUM_INITIAL_CAPACITY) init_capacity = MAXIMUM_INITIAL_CAPACITY;

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
int Map<K,V>::getCapacity(){
    return CAPACTIY;
}

template <class K, class V>
void Map<K,V>::resize(){
    data.increaseResizeCnt(); data.reset();

    set< pair<K,V> > entries = entrySet();
    int old_capacity = CAPACTIY;
    if((CAPACTIY *= 2) > MAXIMUM_INITIAL_CAPACITY) CAPACTIY = MAXIMUM_INITIAL_CAPACITY;
    
    int i;
    for(i = 0; i < old_capacity; i++){
        delete buckets[i]; buckets[i] = nullptr;
    }
    delete[] buckets; buckets = nullptr;
    size = 0;
    buckets = new Map<K,V>::Entry*[CAPACTIY];

    typename set< pair<K,V> >::iterator it;
    for (it = entries.begin(); it != entries.end(); it++) put(it->first, it->second);
}

template <class K, class V>
bool Map<K,V>::isEmpty(){
    return size == 0;
}

template <class K, class V>
int Map<K,V>::searchEntry(K key){
    int hash = computeHash(key);
    while(buckets[hash] == nullptr ? 0 : (key == buckets[hash]->getKey() ? 0 : 1)) hash = ++hash % CAPACTIY;
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
    if(!cur_pos) return NULL;
    int next_pos = searchEntry(key);

    if(buckets[next_pos]){
        data.increaseReplaceCnt();
        cout << "REPLACE" << endl;
        V oldValue = buckets[next_pos]->getValue();
        buckets[next_pos]->setValue(value);
        return oldValue;
    }
    if(next_pos - cur_pos > PROB || size > CAPACTIY * OFFSET){ // |a|
        cout << "RESIZE" << endl;
        resize();
        cur_pos = computeHash(key);
        next_pos = searchEntry(key);
    }
    cout << "NEW PUT : " << next_pos << endl;
    buckets[next_pos] = new Map<K,V>::Entry(next_pos, key, value);
    size++; data.increaseInputCnt();
    return NULL;
}

template <class K, class V>
V Map<K,V>::remove(K key){
    // UnsupportedOperationException
    cout << "DELETION" << endl;
    int cur_pos = searchEntry(key);
    if(buckets[cur_pos] == nullptr) return NULL;

    V oldValue = buckets[cur_pos]->getValue();
    int hash = computeHash(buckets[cur_pos]->getKey());
    delete buckets[cur_pos]; buckets[cur_pos] = nullptr;
    size--;

     // deleete marking
    int next_pos = (cur_pos + 1) % CAPACTIY;
    while(buckets[next_pos]){
        if(computeHash(buckets[next_pos]->getKey()) != hash) break;
        cout << "START" << endl;
        buckets[next_pos - 1] = new Map<K,V>::Entry(next_pos - 1, buckets[next_pos]->getKey(), buckets[next_pos]->getValue());
        delete buckets[next_pos]; buckets[next_pos] = nullptr;
        next_pos = ++next_pos % CAPACTIY;
    }

    return oldValue;
}

template <class K, class V>
bool Map<K,V>::remove(K key, V value){
    cout << "REMOVE2" << endl;
    int cur_pos = searchEntry(key);
    if(buckets[cur_pos] == nullptr ? true : (buckets[cur_pos]->getValue() != value)) return false;
    cout << cur_pos << " " << key << " " << value << endl;
    remove(key);
    return true;
}

template <class K, class V>
void Map<K,V>::putAll(Map<K,V> m){
    // UnsupportedOperationException
    // ClassCastException
    // NullPointerException
    // IllegalArgumentException
    set< pair<K,V> > entries = m.entrySet();
    typename set< pair<K,V> >::iterator it;
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
set<K> Map<K,V>::keySet(){
    set<K> keyset;
    for(int i = 0; i < CAPACTIY; i++){
        if(buckets[i]) keyset.insert(buckets[i]->getKey());
    }
    return keyset;
}

template <class K, class V>
vector<V> Map<K,V>::values(){
    vector<V> valueVector;
    for(int i = 0; i < CAPACTIY; i++){
        if(buckets[i]) valueVector.push_back(buckets[i]->getValue());
    }
    return valueVector;
}

template <class K, class V>
set< pair<K,V> > Map<K,V>::entrySet(){
    set< pair<K,V> > entryset; pair<K,V> p;
    for(int i = 0; i < CAPACTIY; i++){
        if(buckets[i]) {
            p = make_pair(buckets[i]->getKey(), buckets[i]->getValue());
            entryset.insert(p);
        }
    }
    return entryset;
}

// template <class K, class V>
// bool Map<K,V>::equasl(Object o){}

template <class K, class V>
int Map<K,V>::hashCode(){
    set<K> keys = keySet();
    typename set<K>::iterator it;
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


template <class K, class V>
void Map<K,V>::printBuckets(){
    vector< pair<K,V> > vec; typename vector< pair<K,V> >::iterator it;
    int num = 10; int width = 11 * num;

    printLine(width);
    for(int i = 0; i <= CAPACTIY; i++) {
        if((i % num == 0 && i != 0) || i == CAPACTIY){
            cout.flags(ios::right); cout << endl; printLine(width);
            cout.fill(' ');
            for(it = vec.begin(); it != vec.end(); it++){
                if(it->first == 0) {
                    cout << "NULL "; cout << "NULL |";
                }
                else {
                    cout.width(4); cout << it->first << ":";
                    cout.width(4); cout<< it->second << " |";
                }
            }
            vec.clear();
            cout << endl; printLine(width);
            if(i == CAPACTIY) break;
        }

        cout.flags(ios::left); cout.width(9); cout.fill(' '); cout << i << " |";
        if(buckets[i]) vec.push_back(make_pair(buckets[i]->getKey(), buckets[i]->getValue()));
        else vec.push_back(make_pair(NULL, NULL));
    }
}

template <class K, class V>
void Map<K,V>::printLine(int width){
    cout.width(width); cout.fill('-'); cout << "" << endl;
}

// template <class K, class V>
// void Map<K,V>::replaceAll(function<V(K,V)> func){
//     // UnsupportedOperationException
//     // ClassCastException
//     // NullPointerException
//     // ConcurrentModificationException
// }

// template <class K, class V>
// void Map<K,V>::forEach(function<void(K,V)> action){
//     // NullPointerException
//     // ConcurrentModificationException
// }

// template <class K, class V>
// V Map<K,V>::computeIfAbsent(K key, function<V(K)> mappingFunc){
//     // NullPointerException
// }

// template <class K, class V>
// V Map<K,V>::computeIfPresent(K key, function<V(K,V)> remappingFunc){
//     // NullPointerException
// }

// template <class K, class V>
// V Map<K,V>::compute(K key, function<V(K,V)> remappingFunc){
//     // NullPointerException
// }

// template <class K, class V>
// V Map<K,V>::merge(K key, V value, function<V(K,V)> remappingFunc){
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