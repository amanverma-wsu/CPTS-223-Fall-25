#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <functional>
#include <stdexcept>
#include <vector>
#include <string>

// HashTable template class
// ------------------------
// Implements a simple generic hash table with chaining.
// Uses linked lists (Node*) to handle collisions.
// Supports insert, find, remove, resize, and basic utilities.
template <typename K, typename V>
class HashTable {
private:
    // Node structure for linked list (each bucket)
    struct Node {
        K key;        // key of the element
        V value;      // stored value
        Node* next;   // pointer to next node (for collisions)
        
        Node(const K& k, const V& v) : key(k), value(v), next(nullptr) {}
    };
    
    Node** table;       // array of pointers to linked lists (buckets)
    size_t capacity;    // total number of buckets
    size_t size;        // number of stored key-value pairs
    std::hash<K> hasher; // hash function from STL
    
    // Returns hash index for a given key
    size_t getHash(const K& key) const {
        return hasher(key) % capacity;
    }
    
    // Doubles the capacity of the table when load factor > 0.7
    // Rehashes all existing keys into the new table
    void resize() {
        size_t oldCapacity = capacity;
        Node** oldTable = table;
        
        capacity *= 2; // double the table size
        table = new Node*[capacity];
        for (size_t i = 0; i < capacity; i++) {
            table[i] = nullptr;
        }
        size = 0; // will be recalculated as we reinsert
        
        // reinsert all elements into new table
        for (size_t i = 0; i < oldCapacity; i++) {
            Node* current = oldTable[i];
            while (current != nullptr) {
                Node* next = current->next;
                insert(current->key, current->value);
                delete current; // cleanup old nodes
                current = next;
            }
        }
        
        delete[] oldTable; // free old bucket array
    }
    
public:
    // Constructor: initializes hash table with a given size
    HashTable(size_t initialCapacity = 100) 
        : capacity(initialCapacity), size(0) {
        table = new Node*[capacity];
        for (size_t i = 0; i < capacity; i++) {
            table[i] = nullptr;
        }
    }
    
    // Destructor: clears all memory used by the table
    ~HashTable() {
        clear();
        delete[] table;
    }
    
    // Inserts or updates a key-value pair
    // If key exists, replaces the old value
    void insert(const K& key, const V& value) {
        // if load factor > 0.7, resize table
        if ((double)size / capacity > 0.7) {
            resize();
        }
        
        size_t index = getHash(key);
        Node* current = table[index];
        
        // check if key already exists
        while (current != nullptr) {
            if (current->key == key) {
                current->value = value; // update existing
                return;
            }
            current = current->next;
        }
        
        // otherwise, create a new node at the head
        Node* newNode = new Node(key, value);
        newNode->next = table[index];
        table[index] = newNode;
        size++;
    }
    
    // Searches for a key in the table
    // Returns true if found and sets 'value' output parameter
    bool find(const K& key, V& value) const {
        size_t index = getHash(key);
        Node* current = table[index];
        
        while (current != nullptr) {
            if (current->key == key) {
                value = current->value;
                return true;
            }
            current = current->next;
        }
        
        return false; // not found
    }
    
    // Quick check if a key exists
    bool contains(const K& key) const {
        V dummy;
        return find(key, dummy);
    }
    
    // Removes a key from the table (if it exists)
    bool remove(const K& key) {
        size_t index = getHash(key);
        Node* current = table[index];
        Node* prev = nullptr;
        
        while (current != nullptr) {
            if (current->key == key) {
                if (prev == nullptr) {
                    table[index] = current->next; // head of chain
                } else {
                    prev->next = current->next;
                }
                delete current;
                size--;
                return true;
            }
            prev = current;
            current = current->next;
        }
        
        return false; // key not found
    }
    
    // Clears all data from the hash table
    void clear() {
        for (size_t i = 0; i < capacity; i++) {
            Node* current = table[i];
            while (current != nullptr) {
                Node* next = current->next;
                delete current;
                current = next;
            }
            table[i] = nullptr;
        }
        size = 0;
    }
    
    // Returns number of stored elements
    size_t getSize() const {
        return size;
    }
    
    // Returns true if table is empty
    bool isEmpty() const {
        return size == 0;
    }
    
    // Helper function to collect all stored values
    // Used mainly for cleanup or iteration
    void getAllValues(std::vector<V>& values) const {
        for (size_t i = 0; i < capacity; i++) {
            Node* current = table[i];
            while (current != nullptr) {
                values.push_back(current->value);
                current = current->next;
            }
        }
    }
};

#endif
