#include "HashTable.cpp"

class LinkedHashTable : public HashTable {
    Node bufferNode;
    Iterator *iter;

    // для хранения в порядке добавления
    Node bufferNode2;
    Iterator *iter2;

protected:
    // добавить
    void put(Hash *hash) override {
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
        putNode(&bufferNode2, hashCode, hash);
    }

public:
    LinkedHashTable() {
        bufferNode.prev = bufferNode.next = &bufferNode;
        iter = new Iterator(&bufferNode);
        bufferNode2.prev = bufferNode2.next = &bufferNode2;
        iter2 = new Iterator(&bufferNode2);
    }

    ~LinkedHashTable() {
        clear();
        delete iter;
        delete iter2;
    }

    // удалить текущий элемент (true - удалили, false - указатель достиг конца списка)
    bool remove(Hash *hash) override {
        return removeIterator(iter, hash) && removeIterator(iter2, hash);
    }

    // искать элемент: true - нашли (Iterator указывает на данный элемент), false - нет (Iterator в конце списка)
    bool find(Hash *hash) override {
        return findIterator(iter2, hash);
    }

    // очистить список
    void clear() override {
        if (!isEmpty()) {
            for (Node *node = bufferNode.next; node != &bufferNode;) {
                Node *node2 = node;
                node = node->next;
                delete node2;
            }
            bufferNode.prev = bufferNode.next = &bufferNode;
            iter->start();
            for (Node *node = bufferNode2.next; node != &bufferNode2;) {
                Node *node2 = node;
                node = node->next;
                delete node2;
            }
            bufferNode2.prev = bufferNode2.next = &bufferNode2;
            iter2->start();
        }
    }

    // проверить список на пустоту
    bool isEmpty() {
        return bufferNode.next == bufferNode.prev;
    }

    // получить итератор на первый елемент списка
    Iterator *iterator() override {
        return iter2;
    }

    void print(std::ostream &os) override {
        os << " elements";
        for (Node *node = bufferNode.next; node != &bufferNode; node = node->next)
            os << "; (" << *node->hash << ")";
        os << " links";
        for (Node *node = bufferNode2.next; node != &bufferNode2; node = node->next)
            os << "; (" << *node->hash << ")";
    }
};
