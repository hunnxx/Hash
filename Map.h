#ifndef MAP_HPP
#define MAP_HPP

#include <set>
#include <vector>

template <class K, class V>
class Map{
    class Entry{
        int hash;
        K key;
        V value;
    public:
        K getKey();
        V getValue();
        V setValue(V newValue);
        // bool equals(Object o);
        int hashCode();
        // comparingByKey();
        // comparingByValue();
        // comparingByKey();
        // comparingByValue();
    };
    int size;
    static int MAXIMUM_INITIAL_CAPACITY;
    Map<K,V>::Entry *buckets;
public:
    Map(int initialCapacity = 256);
    ~Map();
    int getSize();
    bool isEmpty();
    // bool containsKey(Object o);
    // bool containsValue(Object value);
    // V get(Object key);
    V put(K key, V value);
    // V remove(Object key);
    // void putAll(Map<> m);
    void clear();
    std::set<K> keySet();
    std::vector<V> values();
    // std::set<?> entrySet();
    // bool equals(Object o);
    int hashCode();
    // V getOrDefault(Object key, V defaultValue);
    // void forEach();
    // void replaceAll();
    V putIfAbsent(K key, V value);
    // bool remove(Object key, Object value);
    bool replace(K key, V oldValue, V newValue);
    V replace(K key, V value);
    // V computeIfAbsent(K key, );
    // V computeIfPresent(K key, );
    // V compute(K key, );
    // V merge(K key, V value, );
};
#endif // ifndef MAP_HPP