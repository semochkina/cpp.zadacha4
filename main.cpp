#include "LinkedHashTable.cpp"

using namespace std;

void check(HashTable *ht) {
	cout << "isEmpty() - " << ht->isEmpty() << endl;
	HashObject ho1(5, 55);
	ht->add(&ho1);
	HashObject ho2(1, 11);
	ht->add(&ho2);
	HashObject ho3(3, 33);
	ht->add(&ho3);

	cout << "hashTable - " << *ht << endl;

	HashObject ho4(2, 22);
	ht->add(&ho4);
	cout << "add 2 - hashTable - " << *ht << endl;

	ht->remove(&ho2);
	cout << "remove - hashTable - " << *ht << endl;

	cout << "isEmpty() - " << ht->isEmpty() << endl;

	cout << "Iterator value ";
	Iterator *iterator = ht->iterator();
	iterator->start();
	while (!iterator->finish()) {
		Hash *hash = iterator->current()->hash;
		cout << ", (" << *hash << ")";
		iterator->next();
	}
}

int main() {
	cout << "HashTable\n";
	HashTable hashTable;
	check(&hashTable);

	cout << "\n\nLinkedHashTable\n";
	LinkedHashTable linkedHashTable;
	check(&linkedHashTable);

	cin.get();
	return 0;
}