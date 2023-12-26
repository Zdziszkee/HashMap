//
// Created by Kacper Kuchta on 12/24/23.
//

#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP
#include <utility>

#include "LinkedList.hpp"

template<class KEY, class VALUE>
class Dictionary {
private:
    LinkedList<VALUE>* bucket_array{};
    size_t bucket_array_size{};

public:
    /**
     * Constructor
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
Dictionary<KEY, VALUE>::Dictionary(size_t size) {
    this->bucket_array_size = size;
    this->bucket_array = new LinkedList<VALUE>[size]{new LinkedList<VALUE>()};
}

template<class KEY, class VALUE>
void Dictionary<KEY, VALUE>::clear() {
    for (int i = 0; i < bucket_array_size; ++i) {
        this->bucket_array[i] = nullptr;
    }
}


#endif //DICTIONARY_HPP
