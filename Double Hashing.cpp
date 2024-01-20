#include <iostream>
#include <cmath>
using namespace std;

class DoubleHashing {
private:
    static const int tableSize = 10;
    int hashTable[tableSize];

public:
    DoubleHashing() {
        for (int i = 0; i < tableSize; ++i) {
            hashTable[i] = -1; 
        }
    }

    int hash(int key) {
        return key % tableSize;
    }

    int hash2(int key) {
        // Choose a second hash function, for example, a prime number less than tableSize
        return 7 - (key % 7);
    }

    void insert(int value) {
        int index = hash(value);
        int step = hash2(value);
        while (hashTable[index] != -1) {
            index = (index + step) % tableSize;
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
        int step = hash2(value);
        while (hashTable[index] != -1) {
            if (hashTable[index] == value) {
                cout << value << " found at index " << index << endl;
                return true;
            }
            index = (index + step) % tableSize;
        }
        cout << value << " not found in the hash table." << endl;
        return false;
    }

    void remove(int value) {
        int index = hash(value);
        int step = hash2(value);
        while (hashTable[index] != -1) {
            if (hashTable[index] == value) {
                hashTable[index] = -1;
                cout << value << " removed from index " << index << endl;
                return;
            }
            index = (index + step) % tableSize;
        }
        cout << value << " not found in the hash table. Nothing to remove." << endl;
    }
};

int main() {
    DoubleHashing hash;
    hash.insert(89);
    hash.insert(18);
    hash.insert(49);
    hash.insert(58);
    hash.insert(79);
    hash.insert(27);
    hash.display();
    
    hash.search(49);
    
    hash.remove(18);
    hash.remove(79);

    hash.display();

    return 0;
}
