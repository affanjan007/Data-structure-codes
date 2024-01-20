#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* next;

    Node(int value) : data(value), next(NULL) {}
};

class MinHeap {
private:
    Node* root;

    Node* insert(Node* root, int value) {
	    Node* newNode = new Node(value);
	    if (root == NULL) {
	        return newNode;
	    }
	    if (value < root->data) {
	        newNode->next = root;
	        return newNode;
	    }
	    Node* current = root;
	    Node* parent = NULL;
	
	    while (current != NULL && value >= current->data) {
	        parent = current;
	        current = current->next;
	    }
	    parent->next = newNode;
	    newNode->next = current;
	    return root;
	}	

    void levelOrderTraversal(Node* root) {
        Node* current = root;
        while (current != NULL) {
            cout << current->data << " ";
            current = current->next;
        }
    }
    
    int extractMin(Node*& root) {
        if (root == NULL) {
            cout << "Heap is empty, cannot extract minimum";
            return -1; 
        }
        int minValue = root->data;
        Node* temp = root;
        root = root->next;
        delete temp;
        return minValue;
    }
    
    void remove(Node*& root, int val){
    	if (root == NULL) {
            cout << "Heap is empty";
        }
        Node *current = root;
    	Node *parent = NULL;
    
		while(current!=NULL && current->data!= val){
			parent = current;
        	current = current->next;
		}
		if (current != NULL && current->data == val) {
	        if (parent == NULL) {
	            root = current->next;
	        } 
			else {
	            parent->next = current->next;
	        }
	        delete current;
   		} 
		else {
        	cout << "Element not found in the heap";
    	}
	}

public:
    MinHeap() : root(NULL) {}

    void insert(int value) {
        root = insert(root, value);
    }

    void printLevelOrder() {
        levelOrderTraversal(root);
    }
    
    int removeAndPrint() {
    	int min = extractMin(root);
    	return min;
    }
    
    void del(int val){
    	remove(root, val);
	}
    
};

int main() {
	MinHeap heap;
	
	heap.insert(16);
	heap.insert(1);
	heap.insert(5);
	heap.insert(18);
	heap.insert(13);
	heap.insert(20);
	heap.insert(10);
	heap.insert(4);
	
	heap.printLevelOrder();
	cout<<endl;
	cout<<"Removed element: "<<heap.removeAndPrint()<<endl;
	heap.printLevelOrder();
	
	cout<<endl;
	cout<<"After removing 13 ";
	cout<<endl;
	heap.del(13);
	heap.printLevelOrder();
	
	return 0;
}
