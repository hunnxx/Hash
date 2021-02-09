#ifndef MAP_HPP
#define MAP_HPP

#include <set>
#include <vector>

template <class K, class V>
class Map{
    // template <class K, class V>
    class Entry{
        int hashcode;
        K key;
        V value;
    public:
        Entry(int hashcode, K key, V value);
        K getKey();
        V getValue();
        V setValue(V newValue);
        bool equals(Map<K,V>::Entry e);
        int hashCode();
        // comparingByKey();
        // comparingByValue();
        // comparingByKey();
        // comparingByValue();
    };
    static int MAXIMUM_INITIAL_CAPACITY;
    static int capacity;
    int size;
    Map<K,V>::Entry **buckets;
public:
    Map(int initCapacity = capacity);
    ~Map();
    int getSize();
    bool isEmpty();
    Map<K,V>::Entry* searchEntry(K key);
    bool containsKey(K key);
    // bool containsValue(Object value);
    V get(K key);
    V put(K key, V value);
    V remove(K key);
    void putAll(Map<K,V> m);
    void clear();
    std::set<K> keySet();
    std::vector<V> values();
    std::set<Map<K,V>::Entry> entrySet();
    // bool equals(Object o);
    static int hash(K key);
    int hashCode();
    // V getOrDefault(Object key, V defaultValue);
    void forEach(std::function<void(K,V)> action);
    void replaceAll(std::function<V(K,V)> func);
    V putIfAbsent(K key, V value);
    // bool remove(Object key, Object value);
    bool replace(K key, V oldValue, V newValue);
    V replace(K key, V value);
    V computeIfAbsent(K key, std::function<V(K)> mappingFunc);
    V computeIfPresent(K key, std::function<V(K,V)> remappingFunc);
    V compute(K key, std::function<V(K,V)> remappingFunc);
    V merge(K key, V value, std::function<V(K,V)> remappingFunc);
};
#endif // ifndef MAP_HPP