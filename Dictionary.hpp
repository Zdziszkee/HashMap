//
// Created by Kacper Kuchta on 12/24/23.
//

#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <iostream>

#include "Hash.hpp"
#include "LinkedList.hpp"

template<class KEY, class VALUE>
class Dictionary {
private:
    LinkedList<std::pair<KEY, VALUE>>* bucket_array{};
    size_t bucket_array_size{};
    size_t number_of_elements{};

public:
    /**
     * Constructor
     * @size should be the power of 2, so we can use bitwise operator &
     */
    explicit Dictionary(size_t size);

    /**
     *  Clears dictionary
     */
    void clear();

    /**
     * Adds key -> value pair to dictionary
     * Returns true if successfully added and false when this pair already exists
     */
    bool insert(const std::pair<KEY, VALUE>& pair);

    /**
     * Checks if dictionary contains key
     * Returns true if pair with given key already exists
     */
    bool find(const KEY& key);

    /**
     * Return value for given key
     */
    VALUE& operator[](const KEY& key);

    /**
     * Removes pair with given key
     * Returns true if pair with given key was deleted
     */
    bool erase(const KEY& key);

    /**
     * Returns number of pairs
     */
    int size();

    /**
     * Checks if dictionary is empty
     */
    bool empty();

    /**
     *The "buckets" function prints to the standard output: the character '#',
     * the number of elements in the dictionary,
     * the number of classes,
     * the size of the shortest and longest list in the classes.
     * All values should be printed in a single line ending with a newline character and separated by spaces.
     */
    void buckets();
};

template<class KEY, class VALUE>
void Dictionary<KEY, VALUE>::buckets() {
    std::cout << "#";
    std::cout << " " << number_of_elements;
    std::cout << " " << bucket_array_size;
    int shortest = bucket_array[0].size();
    for (int i = 1; i < bucket_array_size; ++i) {
        auto bucket_size = bucket_array[i].size();
        if (bucket_size < shortest) {
            shortest = bucket_size;
        }
    }
    std::cout << " " << shortest;
    int longest = bucket_array[0].size();
    for (int i = 1; i < bucket_array_size; ++i) {
        auto bucket_size = bucket_array[i].size();
        if (bucket_size > longest) {
            longest = bucket_size;
        }
    }
    std::cout << " " << longest << std::endl;
}

template<class KEY, class VALUE>
Dictionary<KEY, VALUE>::Dictionary(size_t size) {
    this->bucket_array_size = size;
    this->bucket_array = new LinkedList<VALUE>[size]{new LinkedList<VALUE>()};
}

template<class KEY, class VALUE>
bool Dictionary<KEY, VALUE>::insert(const std::pair<KEY, VALUE>& pair) {
    const auto key = pair.first;
    const auto value = pair.second;
    const auto index = hash(key) % bucket_array_size;
    auto bucket = bucket_array[index];
    if (find(key)) {
        return false;
    }
    bucket.push_back(pair);
    number_of_elements++;
    return true;
}

template<class KEY, class VALUE>
bool Dictionary<KEY, VALUE>::find(const KEY& key) {
    const auto index = hash(key) % bucket_array_size;
    auto bucket = bucket_array[index];
    for (auto element: bucket) {
        auto first = element.first;
        if (first == key) {
            return true;
        }
    }
    return false;
}
template<class KEY, class VALUE>
bool Dictionary<KEY, VALUE>::erase(const KEY& key) {
    const auto index = hash(key) % bucket_array_size;
    auto bucket = bucket_array[index];
    for (auto element: bucket) {
        auto first = element.first;
        if (first == key) {
            bucket.remove(element);
            return true;
        }
    }
    return false;
}

template<class KEY, class VALUE>
VALUE& Dictionary<KEY, VALUE>::operator[](const KEY& key) {
    const auto index = hash(key) % bucket_array_size;
    auto bucket = bucket_array[index];
    for (auto element: bucket) {
        auto first = element.first;
        if (first == key) {
            return element.second;
        }
    }
    VALUE value = VALUE{};
    bucket.push_back(key,value);
    return value;
}

template<class KEY, class VALUE>
bool Dictionary<KEY, VALUE>::empty() {
    return number_of_elements == 0;
}

template<class KEY, class VALUE>
int Dictionary<KEY, VALUE>::size() {
    return number_of_elements;
}


template<class KEY, class VALUE>
void Dictionary<KEY, VALUE>::clear() {
    for (int i = 0; i < bucket_array_size; ++i) {
        this->bucket_array[i] = nullptr;
    }
    number_of_elements = 0;
}


#endif //DICTIONARY_HPP
