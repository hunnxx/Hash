#ifndef MAP_HPP
#define MAP_HPP

#include <set>
#include <vector>

template <class K, class V>
class Map{
    // template <class K, class V>
    class Entry{
        int hash;
        K key;
        V value;
    public:
        Entry(int hash, K key, V value);
        int getHash();
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
    static int CAPACTIY;
    int size;
    Map<K,V>::Entry **buckets;
public:
    Map(int initCapacity = CAPACTIY);
    ~Map();
    int getSize();
    void resize();
    bool isEmpty();
    Map<K,V>::Entry* searchEntry(K key);
    bool containsKey(K key);
    bool containsValue(V value);
    V get(K key);
    V put(K key, V value);
    V putVal(int hash, K key, V value);
    V remove(K key);
    bool remove(K key, V value);
    void putAll(Map<K,V> m);
    void clear();
    std::set<K> keySet();
    std::vector<V> values();
    std::set< std::pair<K,V> > entrySet();
    // bool equals(Object o);
    static int computeHash(K key);
    int hashCode();
    // V getOrDefault(Object key, V defaultValue);
    V putIfAbsent(K key, V value);
    bool replace(K key, V oldValue, V newValue);
    V replace(K key, V value);
    void replaceAll(std::function<V(K,V)> func);
    void forEach(std::function<void(K,V)> action);
    V computeIfAbsent(K key, std::function<V(K)> mappingFunc);
    V computeIfPresent(K key, std::function<V(K,V)> remappingFunc);
    V compute(K key, std::function<V(K,V)> remappingFunc);
    V merge(K key, V value, std::function<V(K,V)> remappingFunc);
};
#endif // ifndef MAP_HPP