//
// Created by Shawn Zhao on 2023/8/9.
//
#include "LRU.h"
#include <iostream>
template<typename T>
LRU<T>::~LRU<T>() {
    l.clear();
    m.clear();
}

// 获取数据，放置在头部
template<typename T>
int LRU<T>::Get(int key) {
    if (m.find(key) != m.end()) {
        std::pair<int, T> p = *(m[key]);
        l.erase(m[key]);
        l.push_front(p);
        m[key] = l.begin();
        return p.first;
    }
    else {
        return -1;
    }
}
// 插入数据，如果有就跟新，否则就插入头部
// 如果list满了，就移除尾部数据
template<typename T>
void LRU<T>::Put(int key, T value) {
    if (m.find(key) != m.end()) {
        l.erase(m[key]);
        l.push_front({key, value});
        m[key] = l.begin();
    }
    else { // 不存在
        if (l.size() >= capacity) {
            auto last  = l.back();
            l.pop_back(); // 删除最后一个
            m.erase(last.first); // map 删除键值对
            // 插入
            l.push_front(typename std::pair<int, T>(key, value));
            m.insert({key, l.begin()});
        }
        else {
            l.push_front({key, value});
            m.insert({key, l.begin()});
            capacity += 1;
        }
    }
}
/*
template<typename T>
std::ostream& operator<<(std::ostream& stream, const std::list<std::pair<int, T>> &l) {
    for (auto p : l) {
        stream << "key: " << p.first << " value: " << p.second << " ";
    }
    return stream;
}
 */
template<typename T>
std::ostream& operator<<(std::ostream& stream, const LRU<T>& lru) {
    for (auto p : lru.l) {
        stream << "key: " << p.first << " value: " << p.second << " ";
    }
    return stream;
}

template<typename T>
int LRU<T>::getCapacity(LRU<T> &lru) const {
    return lru.capacity;
}


template class LRU<int>;
template std::ostream& operator<<(std::ostream& stream, const LRU<int>& lru);
