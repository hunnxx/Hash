#include "Map.h"
#include "Data.h"

#include <iostream>
#include <set>
#include <vector>

using namespace std;

// ---------------------------------------------------------------------------
// static

// Bucket의 최대 크기
template <class K, class V>
int Map<K,V>::MAXIMUM_INITIAL_CAPACITY = INT_MAX; // 2147483647

// Bucket의 크기
template <class K, class V>
int Map<K,V>::CAPACTIY = 17;

// Bucket의 크기를 조정하기 위한 수치값(Probing)
template <class K, class V>
int Map<K,V>::PROB = CAPACTIY * 0.5;

// Bucket의 크기를 조정하기 위한 수치값(LoadFactor)
template <class K, class V>
float Map<K,V>::OFFSET = CAPACTIY * 0.6;

// Hash 계산
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

// Map 클래스 생성자
template <class K, class V>
Map<K,V>::Map(int init_capacity){
    if(init_capacity < 0) init_capacity = CAPACTIY;
    else if(init_capacity > MAXIMUM_INITIAL_CAPACITY) init_capacity = MAXIMUM_INITIAL_CAPACITY;

    size = 0;
    buckets = new Map<K,V>::Entry*[(CAPACTIY = init_capacity)];
}

// Map 클래스 소멸자
template <class K, class V>
Map<K,V>::~Map(){
    for(int i = 0; i < CAPACTIY; i++) delete buckets[i];
    delete[] buckets;
}

// Bucket에 채워진 Slot의 수
template <class K, class V>
int Map<K,V>::getSize(){
    return (size < CAPACTIY) ? size : CAPACTIY;
}

// Bucket의 크기
template <class K, class V>
int Map<K,V>::getCapacity(){
    return CAPACTIY;
}

// Bucket 크기 조정
template <class K, class V>
void Map<K,V>::resize(){
    // Data 수집 목적
    data.increaseResizeCnt(); data.reset();

    // 기존의 Bucket에 존재하는 Entry{key,value} 수집
    set< pair<K,V> > entries = entrySet();
    int old_capacity = CAPACTIY;
    if((CAPACTIY *= 2) > MAXIMUM_INITIAL_CAPACITY) CAPACTIY = MAXIMUM_INITIAL_CAPACITY;
    
    // 기존 Bucket 메모리 해제 및 Bucket 재생성
    for(int i = 0; i < old_capacity; i++){
        delete buckets[i]; buckets[i] = nullptr;
    }
    delete[] buckets; buckets = nullptr;
    size = 0;
    buckets = new Map<K,V>::Entry*[CAPACTIY];

    // 새로운 Bucket에 모든 Entry 입력
    typename set< pair<K,V> >::iterator it;
    for (it = entries.begin(); it != entries.end(); it++) put(it->first, it->second);
}

// Bucket이 비었는지 확인
template <class K, class V>
bool Map<K,V>::isEmpty(){
    return size == 0;
}

// 특정 key에 대한 Slot 위치 검색
template <class K, class V>
int Map<K,V>::searchEntry(K key){
    // Hash 값 계산
    int hash = computeHash(key);

    while(buckets[hash]){ // 해당 위치의 Bucket이 비었는지 확인
        if(buckets[hash]->getKey() != key){ // 해당 위치 Bucket의 Key 비교
            if(buckets[hash]->getNext() != -1) { // 해당 위치 Bucket의 Probing 위치 확인
                hash = buckets[hash]->getNext();
                continue;
            } else return -1;
        }
        break;
    }
    return hash;
}

// Linear Probing
template <class K, class V>
int Map<K,V>::probing(K key){
    // Hash 계산
    int hash = computeHash(key); int prev = hash;

    // 빈 Slot 또는 key가 동일한 Slot 반환
    while(buckets[hash] == nullptr ? 0 : (key == buckets[hash]->getKey() ? 0 : 1)) {
        hash = ++hash % CAPACTIY;
    }
    
    // Data 수집 목적
    if(abs(prev - hash)) data.increaseProbCnt();
    return hash;
}

// Key에 대응되는 Entry 존재 확인
template <class K, class V>
bool Map<K,V>::containsKey(K key){
    int pos = searchEntry(key);
    if(pos == -1) return false;
    return buckets[pos] ? true : false;
}

// Value에 대응되는 Entry 존재 확인
template <class K, class V>
bool Map<K,V>::containsValue(V value){
    for(int i = 0; i < CAPACTIY; i++){
        if(buckets[i]){
            if(buckets[i]->getValue() == value) return true;
        }
    }
    return false;
}

// Key에 대한 Entry의 Value값 반환
template <class K, class V>
V Map<K,V>::get(K key){
    int pos = searchEntry(key);
    if(pos == -1) return NULL;
    return buckets[pos] == nullptr ? NULL : buckets[pos]->getValue();
}

// Entry{key,val} 입력 또는 대체
template <class K, class V>
V Map<K,V>::put(K key, V value){
    // Hash 계산 및 (빈 Slot 또는 Key에 대응되는 Slot 탐색)
    int cur_pos = computeHash(key);
    int next_pos = probing(key);

    // Key에 대응되는 Slot 탐색 시, 대체
    if(buckets[next_pos]){
        data.increaseReplaceCnt();
        V oldValue = buckets[next_pos]->getValue();
        buckets[next_pos]->setValue(value);
        return oldValue;
    }
    // 높은 Probing 또는 높은 LoadFactor가 발생할 경우, Bucket 재조정
    if(abs(next_pos - cur_pos) > PROB || size > CAPACTIY * OFFSET){
        resize();
        cur_pos = computeHash(key);
        next_pos = probing(key);
    }

    // 새로운 Entry를 Bucket에 입력
    buckets[next_pos] = new Map<K,V>::Entry(next_pos, key, value);
    if(abs(next_pos - cur_pos)){
        while(buckets[cur_pos]->getNext() != -1) cur_pos = buckets[cur_pos]->getNext();
        buckets[cur_pos]->setNext(next_pos);
    }
    // Data 수집 목적
    size++; data.increaseInputCnt();
    return NULL;
}

// Key에 대응되는 Entry 삭제
template <class K, class V>
V Map<K,V>::remove(K key){
    // Key에 대응되는 Slot 탐색
    int cur_pos = searchEntry(key);
    // Key 대응되는 Slot이 없는 경우
    if(cur_pos == -1) return NULL;
    // 해당 Slot이 비어있는 경우
    if(buckets[cur_pos] == nullptr) return NULL;

    V oldValue = buckets[cur_pos]->getValue();

    // Probing 된 Entry 재정렬
    int next_pos = buckets[cur_pos]->getNext();
    while(next_pos != -1){
        K key = buckets[next_pos]->getKey();
        V val = buckets[next_pos]->getValue();

        delete buckets[cur_pos]; buckets[cur_pos] = nullptr;
        buckets[cur_pos] = new Map<K,V>::Entry(cur_pos, key, val);

        int tmp_pos = next_pos;
        if((next_pos = buckets[next_pos]->getNext()) != -1){
            buckets[cur_pos]->setNext(tmp_pos);
            cur_pos = tmp_pos;
        } else { 
            cur_pos = tmp_pos;
            break;
        }
    }
    delete buckets[cur_pos]; buckets[cur_pos] = nullptr;
    size--;

    return oldValue;
}

// Key와 Value에 대응되는 Entry 삭제
template <class K, class V>
bool Map<K,V>::remove(K key, V value){
    int cur_pos = searchEntry(key);
    if(cur_pos == -1) return false;
    if(buckets[cur_pos] == nullptr ? true : (buckets[cur_pos]->getValue() != value)) return false;
    remove(key);
    return true;
}

// Map에 모든 Entry를 복사
template <class K, class V>
void Map<K,V>::putAll(Map<K,V> m){
    set< pair<K,V> > entries = m.entrySet();
    typename set< pair<K,V> >::iterator it;
    for(it = entries.begin(); it != entries.end(); it++) put(it->first, it->second);
}

// Bucket 초기화
template <class K, class V>
void Map<K,V>::clear(){
    size = 0;
    for(int i = 0; i < CAPACTIY; i++) {
        delete buckets[i]; buckets[i] = nullptr;
    }
}

// Bucket의 Key Set 반환
template <class K, class V>
set<K> Map<K,V>::keySet(){
    set<K> keyset;
    for(int i = 0; i < CAPACTIY; i++){
        if(buckets[i]) keyset.insert(buckets[i]->getKey());
    }
    return keyset;
}

// Bucket의 Value Vector 반환
template <class K, class V>
vector<V> Map<K,V>::values(){
    vector<V> valueVector;
    for(int i = 0; i < CAPACTIY; i++){
        if(buckets[i]) valueVector.push_back(buckets[i]->getValue());
    }
    return valueVector;
}

// Bucket의 Entry Set 반환
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

// 모든 Entry의 Hashcode Sum 반환
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

// Key와 Value에 대응되는 Entry 값 대체
template <class K, class V>
V Map<K,V>::replace(K key, V value){
    if(containsKey(key)) return put(key, value);
    else return NULL;
}

// Key와 Value에 대응되는 Entry 값을 newValue 값으로 대체
template <class K, class V>
bool Map<K,V>::replace(K key, V oldValue, V newValue){
    int pos = searchEntry(key);
    if(pos == -1) return false;
    if(buckets[pos] ? (buckets[pos]->getValue() == oldValue ? true : false) : false) return put(key, newValue);
    else return false;
}

// 시각적인 Bucket 출력 목적
template <class K, class V>
void Map<K,V>::printBuckets(){
    vector< pair< pair<K,V>, int > > vec; 
    typename vector< pair< pair<K,V>, int > >::iterator it;
    int num = 10; int width = 16 * num;

    printLine(width);
    for(int i = 0; i <= CAPACTIY; i++) {
        if((i % num == 0 && i != 0) || i == CAPACTIY){
            cout.flags(ios::right); cout << endl; printLine(width);
            cout.fill(' ');
            for(it = vec.begin(); it != vec.end(); it++){
                if((it->first).first == 0 && (it->first).second == 0) {
                    cout << "NULL "; cout << "NULL "; cout << "NULL |";
                }
                else {
                    cout.width(4); cout << it->first.first << ":";
                    cout.width(4); cout<< it->first.second << ":";
                    cout.width(4); cout<< it->second << " |";
                }
            }
            vec.clear();
            cout << endl; printLine(width);
            if(i == CAPACTIY) break;
        }

        cout.flags(ios::left); cout.width(14); cout.fill(' '); cout << i << " |";
        // if(buckets[i]) vec.push_back(make_pair(buckets[i]->getKey(), buckets[i]->getValue()));
        if(buckets[i]) vec.push_back(make_pair(make_pair(buckets[i]->getKey(), buckets[i]->getValue()), buckets[i]->getNext()));
        else vec.push_back(make_pair(make_pair(NULL, NULL), -1));
    }
}

// 시각적인 Bucket 출력 목적
template <class K, class V>
void Map<K,V>::printLine(int width){
    cout.width(width); cout.fill('-'); cout << "" << endl;
}

// ---------------------------------------------------------------------------
// Map::Entry

// Entry 생성자
template <class K, class V>
Map<K,V>::Entry::Entry(int hash, K key, V value){
    this->hash = hash;
    this->key = key;
    this->value = value;
    this->next = -1;
}

// Entry 소멸자
template <class K, class V>
K Map<K,V>::Entry::getKey(){
    return key;
}

// Entry와 Probing으로 연관된 Entry 위치 반환
template <class K, class V>
int Map<K,V>::Entry::getNext(){
    return next;
}

// Entry의 Value 반환
template <class K, class V>
V Map<K,V>::Entry::getValue(){
    return value;
}

// Entry의 Value 초기화
template <class K, class V>
V Map<K,V>::Entry::setValue(V newValue){
    V oldValue = value;
    this->value = newValue;
    return oldValue;
}

// Entry와 Probing으로 연관된 Entry 위치 초기화
template <class K, class V>
void Map<K,V>::Entry::setNext(int next){
    this->next = next;
}

// 두 개의 Entry 비교
template <class K, class V>
bool Map<K,V>::Entry::equals(Map<K,V>::Entry e){
    return (key == NULL ? e.getKey() == NULL : key == e.getKey()) &&
    (value == NULL ? e.getValue() == NULL : value == e.getValue());
}

// Entry의 HashCode(key^value) 반환
template <class K, class V>
int Map<K,V>::Entry::hashCode(){
    return (key == NULL ? 0 : computeHash(key)) ^ 
    (value == NULL ? 0 : computeHash(value));
}

// ---------------------------------------------------------------------------
// Explicit Template Instantiation

template class Map<int, int>;

// ---------------------------------------------------------------------------