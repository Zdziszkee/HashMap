//
// Created by Kacper Kuchta on 12/24/23.
//

#ifndef HASH_HPP
#define HASH_HPP
#include <string>


inline unsigned int strip_sign_bit(const int& hash) {
    return (hash & 0x7fffffff);
}

template<class KEY>
unsigned int hash(const KEY& key);

template<>
inline unsigned int hash(const std::string& key) {
    unsigned int hash = 0;
    const size_t size = key.size();
    if (hash == 0 && size > 0) {
        for (size_t i = 0; i < size; ++i) {
            hash = 31 * hash + (key[i] - 'a');
        }
    }
    return strip_sign_bit(hash);
}

template<>
inline unsigned int hash(const int& key) {
    return strip_sign_bit(key);
}

template<>
inline unsigned int hash(const long long& key) {
    return strip_sign_bit(key ^ (key >> 32));
}

template<>
inline unsigned int hash(const char& key) {
    return strip_sign_bit(key);
}
#endif //HASH_HPP
