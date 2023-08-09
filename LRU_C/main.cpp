#include <iostream>
#include "LRU.h"

int main() {
    LRU<int> lru(2);

    std::cout << "LRU 缓存大小为： " << lru.getCapacity(lru) << std::endl;
    std::cout << lru << std::endl;
    lru.Put(0, 10);
    std::cout << lru << std::endl;
    lru.Put(3, 30);
    std::cout << lru << std::endl;
    std::cout << lru.Get(2) << std::endl;
    std::cout << lru.Get(0) << std::endl;
    std::cout << lru << std::endl;
    lru.Put(2, 20);
    std::cout << lru << std::endl;
    std::cout << "LRU 缓存大小为： " << lru.getCapacity(lru) << std::endl;
    return 0;
}
