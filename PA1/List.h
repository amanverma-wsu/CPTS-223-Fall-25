#ifndef LIST_H
#define LIST_H

#include "Node.h"
#include <iostream>

template <typename T>
class List {
private:
    Node<T>* head;
    int size;

public:
    List() : head(nullptr), size(0) {}

    ~List() {
        clear();
    }

    List(const List<T>& other) : head(nullptr), size(0) {
        *this = other;
    }

    List<T>& operator=(const List<T>& other) {
        if (this != &other) {
            clear();
            Node<T>* current = other.head;
            while (current != nullptr) {
                insertBack(current->data);
                current = current->next;
            }
        }
        return *this;
    }

    void insertFront(const T& data) {
        Node<T>* newNode = new Node<T>(data);
        newNode->next = head;
        head = newNode;
        size++;
    }

    void insertBack(const T& data) {
        Node<T>* newNode = new Node<T>(data);
        if (head == nullptr) {
            head = newNode;
        } else {
            Node<T>* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
        size++;
    }

    bool remove(const T& data) {
        if (head == nullptr) {
            return false;
        }

        if (head->data == data) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
            size--;
            return true;
        }

        Node<T>* current = head;
        while (current->next != nullptr && !(current->next->data == data)) {
            current = current->next;
        }

        if (current->next != nullptr) {
            Node<T>* temp = current->next;
            current->next = temp->next;
            delete temp;
            size--;
            return true;
        }

        return false;
    }

    bool find(const T& data) const {
        Node<T>* current = head;
        while (current != nullptr) {
            if (current->data == data) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    int getSize() const {
        return size;
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    void clear() {
        while (head != nullptr) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
        size = 0;
    }

    T& at(int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of bounds");
        }
        Node<T>* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->data;
    }

    const T& at(int index) const {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of bounds");
        }
        Node<T>* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->data;
    }

    void display() const {
        Node<T>* current = head;
        while (current != nullptr) {
            std::cout << current->data << std::endl;
            current = current->next;
        }
    }
};

#endif
