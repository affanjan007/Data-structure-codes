#include <iostream>
#include <cmath>
using namespace std;

class Folding {
private:
    static const int tableSize = 10;
    int hashTable[tableSize];

public:
    Folding() {
        for (int i = 0; i < tableSize; ++i) {
            hashTable[i] = -1;
        }
    }

    int fold(int key) {
        int sum = 0;
        while (key > 0) {
            sum = sum + (key % 1000); 			
            key = key / 1000;
        }
        return sum % tableSize;
    }

    void insert(int value) {
        int index = fold(value);
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
        int index = fold(value);
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
        int index = fold(value);
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
    Folding hash;
    hash.insert(123456); 
    hash.insert(789012);
    hash.insert(345678);
    hash.insert(901234);
    hash.display();

	cout<<endl;
    hash.search(789012);
    hash.search(111111);
	cout<<endl;
	
    hash.remove(345678);
	cout<<endl;
    hash.display();

    return 0;
}
