#ifndef NODE_H
#define NODE_H

template <typename T>
class Node {
public:
    T data;
    Node<T>* next;

    Node() : data(T()), next(nullptr) {}
    Node(const T& newData) : data(newData), next(nullptr) {}
    ~Node() = default;
};

#endif
