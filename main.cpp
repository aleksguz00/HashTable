#include <iostream>
#include <memory>
#include "../lists/main.cpp"

template <class Key, class Value>
class HashTable;

template <class Key, class Value>
class HashNode {
public:
    HashNode() = delete;
    
    explicit HashNode(Key key, Value value) : key_{ key }, value_{ value } {}

    friend HashTable;

    template<>
    class HashNode<int, Value> {};
    
    template<>
    class HashNode<std::string_view, Value> {};
private:
    Key key_;
    Value value_;
};

template <class Key, class Value>
class HashTable {
public:

private:
    std::unique_ptr<Value>[]> values; 

    size_t GetIndex_()
};

int main() {
    HashNode<bool, int> hash { true, 5 };
}