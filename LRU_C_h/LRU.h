//
// Created by Shawn Zhao on 2023/8/9.
//

#ifndef LRU_C_H_LRU_H
#define LRU_C_H_LRU_H
#include <iostream>
#include <list>
#include <unordered_map>
template <typename T>
class LRU{
public:
    explicit LRU(int c) : capacity(c) {}

    ~LRU() {
        l.clear();
        m.clear();
    }

    int Get(int key) {
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

    void Put(int key, T value) {
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

    template<class U>
    friend std::ostream & operator<<(std::ostream& stream, const LRU<U>& lru) {
        for (auto p : lru.l) {
            stream << "key: " << p.first << " value: " << p.second << " ";
        }
        return stream;
    }


    int getCapacity(LRU<T> &lru) const {
        return lru.capacity;
    }

private:
    std::list<std::pair<int, T>> l; // key value
    int capacity;
    std::unordered_map<int, typename std::list<std::pair<int, T>>::iterator> m;
    // key address
    // typename 告诉编译器这是一个类型名字，不是其他东西
    // 值是一个指向列表中特定元素的迭代器，这样的数据结构通常被用于在常数时间内查找和更新列表中的元素，因为迭代器可以直接指向元素，而无需遍历整个列表。
};
#endif //LRU_C_H_LRU_H
