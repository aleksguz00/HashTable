#include <iostream>
#include <memory>
// #include "../lists/main.cpp"

class TypeChecker {
public:
    static void Check(std::string_view type_name) {
        if (type_name != typeid(const char*).name() && 
            type_name != typeid(int).name() &&
            type_name != typeid(std::string).name() &&
            type_name != typeid(std::string_view).name()) {
                
            std::cout << "Invalid key type - only int or strings\n";

            throw std::bad_typeid();
        }
    }
};

template <class Key, class Value>
class HashTable;

template <class Key, class Value>
class HashNode {
public:
    HashNode() = delete;
    
    explicit HashNode(Key key, Value value) : key_{ key }, value_{ value } {
        TypeChecker::Check(typeid(Key).name());
    }

    friend HashTable<Key, Value>;

private:
    Key key_;
    Value value_;
};

template <class Key, class Value>
class HashTable {
public:

private:
    std::unique_ptr<Value[]> values; 

    size_t GetIndex_() {
        return 5;
    }
};

int main() {
    HashNode<bool, int> hash = HashNode<bool, int>(true, 2);
}