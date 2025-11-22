#ifndef AVL_MAP_H
#define AVL_MAP_H

#include <algorithm>
#include <stdexcept>
#include <vector>

// Template-based implementation of an AVL Tree Map
// Stores key-value pairs in a balanced binary search tree
// Keys are ordered, and lookup/insertion/deletion all work in O(log n)
template<typename Key, typename Value>
class avl_map {
private:
    // Structure representing a node in the AVL tree
    struct AVLNode {
        Key key;            // Key (used for ordering)
        Value value;        // Value associated with the key
        AVLNode* left;      // Pointer to left child
        AVLNode* right;     // Pointer to right child
        int height;         // Height of this node (for balancing)

        // Constructor for creating a new node
        AVLNode(const Key& k, const Value& v)
            : key(k), value(v), left(nullptr), right(nullptr), height(1) {}
    };

    AVLNode* root;          // Root node of the AVL tree
    int size_count;         // Keeps track of number of nodes in the tree

    // Helper function: returns height of a node (0 if nullptr)
    int height(AVLNode* node) const {
        return node ? node->height : 0;
    }

    // Helper function: returns balance factor of a node
    // Positive means left-heavy, negative means right-heavy
    int getBalance(AVLNode* node) const {
        return node ? height(node->left) - height(node->right) : 0;
    }

    // Updates height of a given node based on its children's heights
    void updateHeight(AVLNode* node) {
        if (node) {
            node->height = 1 + std::max(height(node->left), height(node->right));
        }
    }

    // Performs a right rotation to fix left-heavy imbalance
    AVLNode* rotateRight(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;

        // Rotate nodes
        x->right = y;
        y->left = T2;

        // Update heights after rotation
        updateHeight(y);
        updateHeight(x);
        return x;  // New root after rotation
    }

    // Performs a left rotation to fix right-heavy imbalance
    AVLNode* rotateLeft(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;

        // Rotate nodes
        y->left = x;
        x->right = T2;

        // Update heights after rotation
        updateHeight(x);
        updateHeight(y);
        return y;  // New root after rotation
    }

    // Recursive helper for inserting a new key-value pair
    AVLNode* insertHelper(AVLNode* node, const Key& key, const Value& value) {
        // Base case: reached null, insert here
        if (!node) {
            size_count++;
            return new AVLNode(key, value);
        }

        // BST insert logic (left or right based on key comparison)
        if (key < node->key) {
            node->left = insertHelper(node->left, key, value);
        } else if (key > node->key) {
            node->right = insertHelper(node->right, key, value);
        } else {
            // If key already exists, update its value
            node->value = value;
            return node;
        }

        // Update height after insertion
        updateHeight(node);

        // Get balance factor to check if rebalancing is needed
        int balance = getBalance(node);

        // Case 1: Left Left (heavy on left-left side)
        if (balance > 1 && key < node->left->key)
            return rotateRight(node);

        // Case 2: Right Right (heavy on right-right side)
        if (balance < -1 && key > node->right->key)
            return rotateLeft(node);

        // Case 3: Left Right
        if (balance > 1 && key > node->left->key) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // Case 4: Right Left
        if (balance < -1 && key < node->right->key) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        // Return node pointer (unchanged if already balanced)
        return node;
    }

    // Finds the smallest node in a subtree (used during deletion)
    AVLNode* minValueNode(AVLNode* node) const {
        AVLNode* current = node;
        while (current->left)
            current = current->left;
        return current;
    }

    // Recursive helper for deleting a node by key
    AVLNode* eraseHelper(AVLNode* node, const Key& key) {
        if (!node) return node;

        // Standard BST deletion logic
        if (key < node->key) {
            node->left = eraseHelper(node->left, key);
        } else if (key > node->key) {
            node->right = eraseHelper(node->right, key);
        } else {
            // Node to delete found
            if (!node->left || !node->right) {
                // Case: one child or no child
                AVLNode* temp = node->left ? node->left : node->right;

                if (!temp) {
                    // No child case
                    temp = node;
                    node = nullptr;
                } else {
                    // One child case
                    *node = *temp;  // Copy child data into current node
                }

                delete temp;
                size_count--;
            } else {
                // Case: node with two children
                AVLNode* temp = minValueNode(node->right);
                node->key = temp->key;
                node->value = temp->value;
                node->right = eraseHelper(node->right, temp->key);
            }
        }

        // If the tree had only one node
        if (!node) return node;

        // Update height and balance factor
        updateHeight(node);
        int balance = getBalance(node);

        // Balance the tree using rotations if needed
        if (balance > 1 && getBalance(node->left) >= 0)
            return rotateRight(node);

        if (balance > 1 && getBalance(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (balance < -1 && getBalance(node->right) <= 0)
            return rotateLeft(node);

        if (balance < -1 && getBalance(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    // Recursive search for a given key
    AVLNode* findHelper(AVLNode* node, const Key& key) const {
        if (!node) return nullptr;
        if (key < node->key)
            return findHelper(node->left, key);
        else if (key > node->key)
            return findHelper(node->right, key);
        else
            return node;  // Found the key
    }

    // Frees all memory used by the tree
    void destroyTree(AVLNode* node) {
        if (node) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

public:
    // Simple iterator that wraps a node pointer
    class iterator {
    private:
        AVLNode* node;

    public:
        iterator(AVLNode* n) : node(n) {}

        // Dereference operators to access value
        Value& operator*() {
            if (!node) throw std::out_of_range("Dereferencing end iterator");
            return node->value;
        }

        Value* operator->() {
            if (!node) throw std::out_of_range("Dereferencing end iterator");
            return &(node->value);
        }

        // Equality and inequality checks for iterators
        bool operator==(const iterator& other) const {
            return node == other.node;
        }

        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }

        // Helper to access key from iterator
        Key getKey() const {
            if (!node) throw std::out_of_range("Dereferencing end iterator");
            return node->key;
        }
    };

    // Constructor initializes empty AVL map
    avl_map() : root(nullptr), size_count(0) {}

    // Destructor cleans up all dynamically allocated nodes
    ~avl_map() { destroyTree(root); }

    // Public insert function
    void insert(const Key& key, const Value& value) {
        root = insertHelper(root, key, value);
    }

    // Public erase function
    void erase(const Key& key) {
        root = eraseHelper(root, key);
    }

    // Returns an iterator pointing to the node if found
    iterator find(const Key& key) {
        AVLNode* node = findHelper(root, key);
        return iterator(node);
    }

    // Returns iterator representing "end" (null)
    iterator end() {
        return iterator(nullptr);
    }

    // Returns number of elements in the map
    int size() const {
        return size_count;
    }

    // Checks if the map is empty
    bool empty() const {
        return size_count == 0;
    }
};

#endif
