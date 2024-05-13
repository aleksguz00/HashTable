#include <iostream>
#include <memory>
#include <vector>
#include <initializer_list>
#include <list>
#include <optional>
#include <algorithm>
#include <memory>
#include <math.h>
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
    explicit HashTable() = default;
    explicit HashTable(std::initializer_list<HashNode<Key, Value>> elements) {

    }

    void Insert(Key key, Value value) {
        size_t index = GetIndex_(key);

        if (!values_[index]) {
            std::list<HashNode<Key, Value>> list;
            // list.remove_if()
            values_[index] = list;
        }
        HashNode<Key, Value> node{ key, value };
        values_[index].pop_back(node);
    }

    void Update(Key key, Value value) {
        size_t index = GetIndex_(key);

        if (!values_[index]) return;

        auto it = std::find_if(values_[index].begin(), values_[index].end(),
                            [value](const HashNode<Key, Value>& node){ return node.value_ == value; });

        if (it != values_[index].end()) {
            it->value_ = value;
        }
    }

    void Delete(Key key) {
        size_t index = GetIndex_(key);

        if (!values_[index]) return;

        if (values_[index].size() < 2) {
            values_[index].pop_back();
            values_[index] = nullptr;

            return;
        }

        values_[index].remove_if([key](const HashNode<Key, Value>& node) {
            return node.key_ == key;
        });
    }

private:
    std::optional<std::list<Value>> values_;
    static constexpr std::unique_ptr<size_t[]> sizes = std::make_unique<size_t[]>(GetSizes_());

    size_t GetHash_(std::string_view key) {
        size_t hash = 0;

        for (size_t i; i < key.size(); ++i) {
            hash = (hash << 5) - hash + static_cast<size_t>(key[i]);
        }

        return hash;
    }

    size_t GetHash_(size_t key) {
        return key;
    }

    size_t GetIndex_(Key key) {
        size_t hash = GetHash_(key);

        // Add %
        return hash;
    }

    static constexpr std::unique_ptr<size_t[]> GetSizes_() {
        uint32_t size = pow(2, sizeof(uint32_t) * 8);

        std::unique_ptr<size_t[]> sizes = std::make_unique<size_t[]>(size);

        for (size_t i = 0; i < size; ++i) {
            if ((i & (i + 1)) == 0) {
                continue;;
            }

            if ((i & (i + 1)) == 1) {
                continue;
            }

            sizes[i] = i;
        }

        return sizes;
    }
};

int main() {
    // HashNode<bool, int> hash = HashNode<bool, int>(true, 2);

    std::cout << pow(2, sizeof(uint32_t) * 8) << '\n';
}