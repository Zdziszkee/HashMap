//
// Created by Kacper Kuchta on 12/24/23.
//
#ifndef LINKED_LIST
#define LINKED_LIST

#include <stdexcept>

template<class T>
class LinkedList {
private:
    struct Node {
        template<class U>
        explicit Node(U &&value , Node *previous = nullptr, Node *next = nullptr)
                : value(std::forward<U>(value)), previous(previous), next(next) {}

        T value;
        Node *previous;
        Node *next;

    };

    Node *guard;
    size_t current_size = 0;

    template<class U>
    void insertBetween(Node *previous, U &&x, Node *next
    ) {
        Node *node = new Node(std::forward<U>(x), previous, next);
        previous->next = node;
        next->previous = node;
        ++current_size;
    }

    T popBetween(Node *previous, Node *next) {
        Node *middle = previous->next;
        T val = middle->value;
        delete middle;
        previous->next = next;
        next->previous = previous;
        --current_size;
        return val;
    }


public:
    ~LinkedList() {
        delete guard;
    }

    LinkedList() {
        this->guard = new Node(std::forward<T>(nullptr), nullptr, nullptr);
        this->guard->next = this->guard;
        this->guard->previous = this->guard;
    }

    /*
     * Copy constructor
     */
    LinkedList(LinkedList &other) : LinkedList() {
        LinkedList<T>::Iterator iterator = other.begin();
        while (iterator != other.end()) {
            this->push_back(*iterator);
            ++iterator;
        }
    }

    /*
     * Move constructor
     */
    LinkedList(LinkedList &&other) noexcept: guard(std::move(other.guard)),
                                             current_size(std::move(other.current_size)) {}

    template<class U>
    void push_front(U &&x) {
        this->insertBetween(guard, std::forward<U>(x), guard->next);
    }

    T pop_front() {
        if (empty()) {
            throw std::out_of_range("Stack is empty");
        }
        return popBetween(guard, guard->next->next);
    }

    template<class U>
    void push_back(U &&x) {
        this->insertBetween(guard->previous, std::forward<U>(x), guard);
    }

    T pop_back() {
        if (empty()) {
            throw std::out_of_range("Stack is empty");
        }
        return this->popBetween(guard->previous->previous, guard);
    }

    int remove(const T &x) {
        int number = 0;
        LinkedList<T>::Iterator iterator = this->begin();
        while (iterator != this->end()) {
            if (*iterator == x) {
                ++number;
                iterator = this->erase(iterator);
            } else { ++iterator; }
        }
        return number;
    }

    int size() {
        return this->current_size;
    }

    bool empty() {
        return (size() == 0);
    }

    void clear() {
        while (!this->empty()) {
            this->pop_back();
        }
    }

    struct Iterator {
        Node *current;

        explicit Iterator(Node *node) : current(node) {}

        T &operator*() { return this->current->value; }

        Iterator &operator++() {
            this->current = this->current->next;
            return *this;
        }

        Iterator &operator--() {
            this->current = this->current->previous;
            return *this;
        }

        bool operator==(const Iterator &other) {
            return this->current == other.current;
        }

        bool operator!=(const Iterator &other) {
            return this->current != other.current;
        }
    };

    Iterator find(const T &x) {
        LinkedList<T>::Iterator iterator = this->begin();
        while (iterator != end()) {
            if (*iterator == x) {
                return iterator;
            }
            ++iterator;
        }
        throw std::out_of_range("Element does not exist in LinkedList");

    }

    Iterator erase(Iterator iterator) {
        LinkedList<T>::Iterator next = iterator.current->next;
        this->popBetween(iterator.current->previous, iterator.current->next);
        return next;
    }

    template<class U>
    Iterator insert(Iterator iterator, U &&x) {
        this->insertBetween(iterator.current->previous, std::forward<U>(x), iterator.current);
        return Iterator(iterator.current->previous);
    }

    Iterator begin() { return Iterator(guard->next); }

    Iterator end() { return Iterator(guard); }

};


#endif // !LINKED_LIST