#include <iostream>
#include <cmath>
using namespace std;

class QuadraticProbing  {
private:
    static const int tableSize = 10;
    int hashTable[tableSize];

public:
    QuadraticProbing () {
        for (int i = 0; i < tableSize; ++i) {
            hashTable[i] = -1; 
        }
    }

    int hash(int key) {
        return key % tableSize;
    }

    void insert(int value) {
        int index = hash(value);
        int i = 1;
  	      while (hashTable[index] != -1) {
            index = (index + i * i) % tableSize;
            ++i;
        }

        hashTable[index] = value;
    }

    void display() {
        for (int i = 0; i < tableSize; ++i) {
            cout << "Bucket " << i << ": " << hashTable[i] << endl;
        }
    }
    
    bool search(int val){
    	int index = hash(val);
        int i = 1;
        while (hashTable[index] != -1) {
        	if(hashTable[index] == val){
        		cout << val << " found at index " << index << endl;
                return true;
			}
            index = (index + i * i) % tableSize;
            ++i;
        }
        cout << val << " not found in the hash table." << endl;
        return false;
	}
	
	void remove(int val) {
		int index = hash(val);
        int i = 1;
        while (hashTable[index] != -1) {
        	if(hashTable[index] == val){
        		hashTable[index] = -1;
        		cout << val << " removed from index " << index << endl;
                return;
			}
            index = (index + i * i) % tableSize;
            ++i;
        }
        cout << val << " not found in the hash table. Nothing to remove." << endl;
	}
};

int main() {
    QuadraticProbing hash;
    hash.insert(89);
    hash.insert(18);
    hash.insert(49);
    hash.insert(58);
    hash.insert(79);
    hash.insert(27);
    hash.display();
    
    hash.search(49);
    hash.search(9);
    
    hash.remove(17);
    hash.remove(79);

    hash.display();
    
    return 0;
}