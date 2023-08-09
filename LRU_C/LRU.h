//
// Created by Shawn Zhao on 2023/8/9.
//

#ifndef LRU_C_LRU_H
#define LRU_C_LRU_H
#include <list>
#include <unordered_map>
#include <iostream>
template <typename T>
class LRU{
public:
    explicit LRU(int c) : capacity(c) {};

    ~LRU();

    int Get(int key);

    void Put(int key, T value);

    template<class U>
    friend std::ostream & operator<<(std::ostream& stream, const LRU<U>& lru);

    int getCapacity(LRU<T> &lru) const;

private:
    std::list<std::pair<int, T>> l; // key value
    int capacity;
    std::unordered_map<int, typename std::list<std::pair<int, T>>::iterator> m;
    // key address
    // typename 告诉编译器这是一个类型名字，不是其他东西
    // 值是一个指向列表中特定元素的迭代器，这样的数据结构通常被用于在常数时间内查找和更新列表中的元素，因为迭代器可以直接指向元素，而无需遍历整个列表。
};
#endif //LRU_C_LRU_H
