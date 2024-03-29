#include "Dictionary.hpp"

#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

int main(int arguments_size, char** arguments) {
    if (arguments_size != 2) {
        std::cout << "Wrong number of arguments!" << std::endl;
        std::exit(EXIT_FAILURE);
        return 1;
    }
    const char* file_name = arguments[1];
    std::ifstream inputFile(file_name);

    if (!inputFile.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }
    Dictionary<std::string, std::string> dictionary(1024);

    std::string first;
    std::string second;
    while (inputFile >> first) {
        inputFile >> second;
        dictionary.insert(std::pair(first, second));
    }
    inputFile.close();

    std::vector<std::string> keys;
    std::string key;

    while (std::cin >> key) {
        keys.push_back(key);
    }

    for (const auto& element: keys) {
        if (dictionary.find(element)) {
            std::string value = dictionary[element];
            std::cout << value << std::endl;
        } else {
            std::cout << "-" << std::endl;
        }
    }

    return 0;
}
