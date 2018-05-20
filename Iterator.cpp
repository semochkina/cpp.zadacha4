#include "HashObject.cpp"

// двухнаправленный связанный список
struct Node {
    int hashCode;
    Hash *hash;
    Node *next, *prev;

    Node() {
        next = prev = this;
    }
};

// итератор
class Iterator {
    Node *beginNode;
    Node *currNode;

public:
    Iterator(Node *bufferNode) : beginNode(bufferNode) {
        start();
    }

    // начать работу
    void start() {
        currNode = beginNode->next;
    }

    // получить текущий элемент
    Node *current() {
        return currNode;
    }

    // сдвинуть итератор на следующий элемент
    void next() {
        if (currNode != beginNode) currNode = currNode->next;
    }

    // проверка все ли проитерировано
    bool finish() {
        return currNode == beginNode;
    }
};