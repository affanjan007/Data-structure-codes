#include <iostream>
#include <algorithm>
using namespace std;

class Node {
public:
    int key;
    Node* left;
    Node* right;
    int height;

    Node(int data){
    	key = data;
    	left = NULL;
    	right = NULL;
    	height = 1;
	} 
};

class AVL {
private:
    Node* root;

    int getHeight(Node* node) {
	    if (node != NULL) {
	        return node->height;
	    } 
		else {
	        return 0;
	    	}
	}

    int getBalance(Node* node) {
        if (!node) {
            return 0;
        }
        return getHeight(node->left) - getHeight(node->right);
    }

    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

        return x;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

        return y;
    }

    Node* rebalance(Node* node) {
        int balance = getBalance(node);

        // Left-Left case (LL)
        if (balance > 1 && node->key > node->left->key) {
            return rightRotate(node);
        }

        // Right-Right case (RR)
        if (balance < -1 && node->key < node->right->key) {
            return leftRotate(node);
        }

        // Left-Right case (LR)
        if (balance > 1 && node->key < node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right-Left case (RL)
        if (balance < -1 && node->key > node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }

    Node* insert(Node* node, int key) {
        if (!node) {
            return new Node(key);
        }
        if (key < node->key) {
            node->left = insert(node->left, key);
        } 
		else if (key > node->key) {
            node->right = insert(node->right, key);
        }
		else {
            // Duplicate keys not allowed
            return node;
        }
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        return rebalance(node);
    }

    Node* findMin(Node* node) {
        while (node->left) {
            node = node->left;
        }
        return node;
    }
    
    Node* remove(Node* node, int key){
		if(!node){
			return node;
		}
		else if(key < node->key){
			node->left=remove(node->left, key);
		}
		else if(key > node->key){
			node->right=remove(node->right,key);
		}
		else{
			if(!node->left && !node->right){
				delete node;
				return NULL;
			}
			else if(!node->left && node->right){
				Node* temp=node;
				node=node->right;
				delete temp;
			}
			else if(node->left && !node->right){
				Node* temp=node;
				node=node->left;
				delete temp;
			}
			else{
				Node* temp = findMin(node->right);
				node->key=temp->key;
				node->right=remove(node->right, temp->key);
			}
		}
		node->height= 1 +  max(getHeight(node->left), getHeight(node->right));
		return rebalance(node);
	}

    bool search(Node* node, int key) {
        if (!node) {
            return false;
        }

        if (key == node->key) {
            return true;
        }

        if (key < node->key) {
            return search(node->left, key);
        }

        return search(node->right, key);
    }

    void inorderTraversal(Node* node) {
        if (node) {
            inorderTraversal(node->left);
            cout << node->key << " ";
            inorderTraversal(node->right);
        }
    }

public:
    AVL() : root(nullptr) {}

    void insert(int key) {
        root = insert(root, key);
    }

    int getHeight() {
        return getHeight(root);
    }

    void remove(int key) {
        root = remove(root, key);
    }

    bool search(int key) {
        return search(root, key);
    }

    void displayInorder() {
        inorderTraversal(root);
        cout << endl;
    }

    int getBalance() {
        return getBalance(root);
    }
};

int main() {
    AVL avl;

    avl.insert(1);
    avl.insert(2);
    avl.insert(8);
    avl.insert(7);
    avl.insert(3);
    avl.insert(4);
    avl.insert(9);
    avl.insert(5);
    avl.insert(6);

    cout << "Inorder Traversal: ";
    avl.displayInorder();

    cout << "Tree Height: " << avl.getHeight() << endl;

    int keyToFind = 3;
    if (avl.search(keyToFind)) {
        cout << keyToFind << " found in the tree." << endl;
    } 
	else {
        cout << keyToFind << " not found in the tree." << endl;
    }

    int keyToRemove = 2;
    avl.remove(keyToRemove);
    cout << "Inorder Traversal after removing " << keyToRemove << ": ";
    avl.displayInorder();

    cout << "Tree Balance Factor: " << avl.getBalance() << endl;

    return 0;
}