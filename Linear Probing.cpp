#include <iostream>
#include <cmath>
using namespace std;

class LinearProbing {
private:
    static const int tableSize = 10;
    int hashTable[tableSize];

public:
    LinearProbing() {
        for (int i = 0; i < tableSize; ++i) {
            hashTable[i] = -1; 
        }
    }

    int hash(int key) {
        return key % tableSize;
    }

    void insert(int value) {
        int index = hash(value);

        while (hashTable[index] != -1) {
            index = (index + 1) % tableSize;
        }

        hashTable[index] = value;
    }

    void display() {
        for (int i = 0; i < tableSize; ++i) {
            cout << "Bucket " << i << ": " << hashTable[i] << endl;
        }
    }

    bool search(int value) {
        int index = hash(value);

        while (hashTable[index] != -1) {
            if (hashTable[index] == value) {
                cout << value << " found at index " << index << endl;
                return true;
            }
            index = (index + 1) % tableSize;
        }
        cout << value << " not found in the hash table." << endl;
        return false;
    }

    void remove(int value) {
        int index = hash(value);

        while (hashTable[index] != -1) {
            if (hashTable[index] == value) {
                hashTable[index] = -1;
                cout << value << " removed from index " << index << endl;
                return;
            }
            index = (index + 1) % tableSize;
        }
        cout << value << " not found in the hash table. Nothing to remove." << endl;
    }
};

int main() {
    LinearProbing hash;
    hash.insert(1);
    hash.insert(5);
    hash.insert(11);
    hash.insert(7);
    hash.insert(12);
    hash.insert(17);
    hash.insert(6);
    hash.insert(25);
    
    
    hash.display();

    hash.search(11);
    hash.search(8);

    hash.remove(7);
    hash.remove(8);

    hash.display();

    return 0;
}
