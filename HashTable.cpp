#include <iostream>
#include "Iterator.cpp"

class HashTable {
    Node bufferNode;
    Iterator *iter;

protected:
    void putNode(Node *curr, int hashCode, Hash *hash) {
        Node *newNode = new Node;
        newNode->hashCode = hashCode;
        newNode->hash = hash;
        newNode->prev = curr->prev;
        newNode->next = curr;

        curr->prev->next = newNode;
        curr->prev = newNode;
    }

    // добавить
    virtual void put(Hash *hash) {
        int hashCode = hash->hashCode();
        // ищем место куда вставлять
        iter->start();
        while (!iter->finish()) {
            if (iter->current()->hashCode == hashCode) {
                // элемент уже есть
                return;
            }
            if (iter->current()->hashCode > hashCode) {
                // нашли элемент с большим ключем
                break;
            }
            iter->next();
        }
        putNode(iter->current(), hashCode, hash);
    }

    bool findIterator(Iterator *iterator, Hash *hash) {
        int hashCode = hash->hashCode();
        iterator->start();
        while (!iterator->finish()) {
            if (iterator->current()->hashCode == hashCode) {
                return true;
            }
            iterator->next();
        }
        return false;
    }

    bool removeIterator(Iterator *iterator, Hash *hash) {
        if (!findIterator(iterator, hash)) {
            return false;
        }
        Node *curr = iterator->current();
        iterator->next();

        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;

        delete curr;
        return true;
    }

public:
    HashTable() {
        bufferNode.prev = bufferNode.next = &bufferNode;
        iter = new Iterator(&bufferNode);
    }

    ~HashTable() {
        clear();
        delete iter;
    }

    // добавить элемент
    void add(Hash *hash) {
        put(hash);
    }

    // удалить текущий элемент (true - удалили, false - нет)
    virtual bool remove(Hash *hash) {
        return removeIterator(iter, hash);
    }

    // искать элемент: true - нашли (Iterator указывает на данный элемент), false - нет (Iterator в конце списка)
    virtual bool find(Hash *hash) {
        return findIterator(iter, hash);
    }

    // очистить список
    virtual void clear() {
        if (!isEmpty()) {
            for (Node *node = bufferNode.next; node != &bufferNode;) {
                Node *node2 = node;
                node = node->next;
                delete node2;
            }
            bufferNode.prev = bufferNode.next = &bufferNode;
            iter->start();
        }
    }

    // проверить список на пустоту
    bool isEmpty() {
        return bufferNode.next == bufferNode.prev;
    }

    // получить итератор на первый елемент списка
    virtual Iterator *iterator() {
        return iter;
    }

    virtual void print(std::ostream &os) {
        os << " elements";
        for (Node *node = bufferNode.next; node != &bufferNode; node = node->next)
            os << "; (" << *node->hash << ")";
    }

    friend std::ostream &operator<<(std::ostream &os, HashTable &element) {
        element.print(os);
        return os;
    }
};
