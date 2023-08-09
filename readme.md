# LRU算法

LRU 的英文全称是 Least Recently Used，中文意思是最近最久未使用。
在访问缓存（Cache）时，总是希望最近使用的、最频繁使用的数据存储在比较靠前的位置。于是，LRU 缓存要具备以下特点：

- 插入某个数据时，它应该被放到 Cache 的最前面
- 查询某个数据之后，它应该被挪到 Cache 的最前面
- 插入数据时，如果 Cache 的容量不够时，把 Cache 尾部的数据移出

**回顾下哈希表**

数据的存储一般都基于哈希表实现的，其中一个主要原因是查找起来方便。基于 <key, value> 存储数据需要开辟两块内存，一块是内存池，存放实际数据的；一块是哈希表，存放 key 和数据地址。

# 实现过程

## .h与.cpp文件

`.h` & `.cpp`文件，要学习，使用`.h`来定义类与函数声明，`.cpp` 文件用来完成函数定义

## 链接问题

因为使用了范型，在这个里遇见bug

```
ld: symbol(s) not found for architecture arm64
clang: error: linker command failed with exit code 1 (use -v to see invocation)
ninja: build stopped: subcommand failed.
```

**在C++中，模板的成员函数实际上只有在被使用（即被调用）时才会被实例化，然后链接到程序中。这就是为什么你在编译和链接过程中可能会遇到模板成员函数找不到定义的问题。**

通过在你的 `.cpp` 文件中添加以下代码：

```cpp
template class LRU<int>;
template std::ostream& operator<<(std::ostream& stream, const LRU<int>& lru);
```

你在实际使用 `LRU<int>` 类和 `operator<<` 函数之前，强制进行了模板实例化。这样，编译器就会生成特定类型的模板实例，然后链接器就能找到这些实例的定义，从而解决了链接错误问题。

这种方法叫做“显式实例化”，它确保在编译过程中生成了特定类型的模板实例，从而避免了链接错误。

**如果你想使用隐式实例化**，即让编译器在需要的时候自动实例化模板，通常可以将模板的声明和定义都放在头文件中。这样，在编译单元中包含头文件时，编译器就能够在需要的地方自动实例化模板，并将生成的实例链接到最终的可执行文件中。

**所以，将模板的声明和定义都放在头文件 `.h` 中，而不是分离到 `.cpp` 文件中，可以让编译器隐式地处理模板的实例化和链接，从而避免链接错误。这是一种常用的做法，特别是对于模板类和模板函数。**这个版本我定义在`_h`中。

## 编写习惯问题

对于范型所有的函数，希望在`.h`中可以将所有的 `template <typename T>` 写在每一个函数之前

因为对于friend函数，我就是没有写，导致重载`<<` 符号时候，无法进行访问函数，因为l是私有变量，也就是在每一个函数前都写一次templat，相当于对于这个函数的typename不会影响其他函数

```c++
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
```

friend函数一定需要！如果私有没有这个，我就每一个函数都去写了，这个是一个问题，我需要再思考一下。