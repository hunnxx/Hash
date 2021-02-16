#ifndef MAP_H
#define MAP_H

#include "Data.h"

#include <set>
#include <vector>

template <class K, class V>
class Map{

    class Entry{
        int hash;
        K key;
        V value;
        int next;
    public:
        Entry(int hash, K key, V value);
        K getKey();
        V getValue();
        int getNext();
        V setValue(V newValue);
        void setNext(int next);
        bool equals(Map<K,V>::Entry e);
        int hashCode();
        // comparingByKey();
        // comparingByValue();
        // comparingByKey();
        // comparingByValue();
    };

    static int MAXIMUM_INITIAL_CAPACITY;
    static int CAPACTIY;
    static int PROB;
    static float OFFSET;

    int size;
    Map<K,V>::Entry **buckets;

public:

    Map(int init_capacity = CAPACTIY);
    ~Map();
    
    int getSize();
    int getCapacity();
    void resize();
    bool isEmpty();
    int searchEntry(K key);
    int probing(K key);
    bool containsKey(K key);
    bool containsValue(V value);
    V get(K key);
    V put(K key, V value);
    V remove(K key);
    bool remove(K key, V value);
    void putAll(Map<K,V> m);
    void clear();
    std::set<K> keySet();
    std::vector<V> values();
    std::set< std::pair<K,V> > entrySet();
    // bool equals(Object o);
    static unsigned int computeHash(K key);
    int hashCode();
    // V getOrDefault(Object key, V defaultValue);
    // V putIfAbsent(K key, V value);
    bool replace(K key, V oldValue, V newValue);
    V replace(K key, V value);
    // void replaceAll(std::function<V(K,V)> func);
    // void forEach(std::function<void(K,V)> action);
    // V computeIfAbsent(K key, std::function<V(K)> mappingFunc);
    // V computeIfPresent(K key, std::function<V(K,V)> remappingFunc);
    // V compute(K key, std::function<V(K,V)> remappingFunc);
    // V merge(K key, V value, std::function<V(K,V)> remappingFunc);

    Data data;

    void printBuckets();
    void printLine(int width);

};
#endif // ifndef MAP_H