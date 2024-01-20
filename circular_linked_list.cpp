#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* ptr;
    Node(int val) {
        data = val;
        ptr = nullptr;
    }
};

class CircularLinkedList {
    Node* head;
    Node* tail;

public:
    CircularLinkedList() {
        head = nullptr;
        tail = nullptr;
    }

	int calculate_length(){	
		Node* current=head;
		int length=0;
	        do {									
	            current = current->ptr;
	            length++;
	        } 
			while(current != head);
			return length;
	}
	
	void display(){				//displaying list
    	if(!head){
        	cout << "List is empty" << endl;
    	}
    	else{
	        Node* current=head;
	        do {								//we will use do while because loop to ensure that at least
				cout << current->data << " ";	// one iteration is performed, cause intially current = head
	            current = current->ptr;
	        } 
			while(current != head);
	        cout << endl;
    	}
	}

	void append(int val){
		Node* temp=new Node(val);
		if(!head){
			head=temp;
			tail=temp;
			temp->ptr=temp;
		}
		else{
			tail->ptr=temp;  		// Connecting the current tail to the new node
	        temp->ptr=head;  		// Making the new node point to the head
	        tail=temp; 		     	// Updating the tail pointer to the new node
		}
	}
	
	void insert_pos(int val,int index){			//inserting val by index position
		Node* temp=new Node(val);
		if(index<=0){
			cout<<"Error!"<<endl;
		}
		else if(index==1 || !head){			//if index is 1
			head=temp;
			tail=temp;
			temp->ptr=temp;
		}
		else{
			Node* current=head;
			int count=1;
			while(current->ptr != head && count != index-1){
				current=current->ptr;
				count++;
			}
			if(current->ptr == head){
				cout<<"Out of bounds!"<<endl;
			}
			else{
				temp->ptr=current->ptr;
				current->ptr=temp;
			}
		}
	}
	
	void remove() {			//removing from the end
        if (!head) {
            cout << "List is empty." << endl;
        } 
        else if (head == tail) {		//if only one node in the list
	        delete head;
	        head = nullptr;
	        tail = nullptr;
    	}
		else {
            Node* current = head;
            while (current->ptr != tail) {
                current = current->ptr;
            }
           	current->ptr = head;
            delete tail; 
            tail=current;
        }
    }
    
    void delete_pos(int index) {
	    if (index <= 0 || !head) {
	        cout << "Error: Invalid index or empty list!" << endl;
	    } 
	    else if (index == 1) {			//if only one elemenet
            if (head->ptr == head) {
                delete head;
                head = nullptr;
            } 
			else {
                Node* temp = head;
                while (temp->ptr != head) {		//traversing to the last node so its ptr is pointing to head node
                    temp = temp->ptr;		
                }
                temp->ptr = head->ptr;			
                Node* oldHead = head;			//preserving the address of old head
           		head = head->ptr;				//moving head to point to next node
           		delete oldHead;
            }
        }
	    else {
	        Node* current = head;
	        Node* previous = head; 			
	        int count = 1;
	        while (current->ptr != head && count != index) {
	            previous = current;
	            current = current->ptr;
	            count++;
	        }
	        if (index > calculate_length()) {		//if index is out of bound
	            cout << "Error: Index out of bounds!" << endl;
	        }
	        else {				
	            previous->ptr = current->ptr;
	            delete current;
	        }
	    }
	}
	
	void insert_search_byValue(int val_to_search, int val_to_add){		//inserting value after a specific value
		Node* temp=new Node(val_to_add);
		if(!head){
			cout<<"Error! List is empty"<<endl;
			delete temp;
		}
		else{
			Node* current=head;
			while(current->ptr != head && current->data != val_to_search){
				current=current->ptr;
			}
			if(current->data != val_to_search){
				cout<<"Value not found!"<<endl;
			}
			else{
				temp->ptr=current->ptr;
				current->ptr=temp;
			}
		}
	}
	
	void delete_search_byValue(int val_to_delete){		//deleting by passing val to delete
		if(!head){
			cout<<"List is empty"<<endl;
		}
		else if (head->data == val_to_delete){		//deleting the element on first index
			delete_pos(1);
		}
		else{
			Node* current=head;
			int count=1;
			while(current->ptr != head && current->data != val_to_delete){
				current=current->ptr;
				count++;
			}
			if(current->data == val_to_delete){		//finding the index pos of the value and passing to delete_pos func
				delete_pos(count);
			}
			else{
				cout<<"Value not found!"<<endl;
			}
		}
	}
		
	void reverse() {
        if (head == nullptr) {
            cout << "List is empty." << endl;
        } 
		else {
            Node* current = head;
            Node* previous = NULL;
            Node* ptr = NULL;
            do {
                ptr = current->ptr;				//ptr pointing to next node
                current->ptr = previous;		//reversing the direction 
                previous = current;
                current = ptr;					//current pointing to next node
            } 
			while (current != head);
            head->ptr = previous;	//this line upd the head ptr to point to the new head of the reversed list
            head = previous;
        }
    }
};

int main(){
	CircularLinkedList list;
	
	cout<<"CIRCULAR LINKED LIST"<<endl;
	cout<<"-------------------"<<endl;
	
	cout<<endl<<endl<<"DISPLAYING ALL THE ELEMENTS IN THE LIST"<<endl;
	list.append(50);
	list.append(60);
	list.append(30);
	list.append(10);
	list.append(20);
	list.display();
	
	cout<<endl<<endl<<"AFTER INSERTING AN ELEMENT ON THE 3nd INDEX"<<endl;
	list.insert_pos(80,3);
	list.display();
	
	cout<<endl<<endl<<"AFTER REMOVING LAST ELEMENT FROM THE LIST"<<endl;
	list.remove();
	list.display();
	
	cout<<endl<<endl<<"AFTER DELETING AN ELEMENT ON THE 1nd INDEX"<<endl;
	list.delete_pos(1);
	list.display();
		
	cout<<endl<<endl<<"INSERTING 200 AFTER 80 VALUE"<<endl;
	list.insert_search_byValue(80,200);
	list.display();
		
	cout<<endl<<endl<<"AFTER DELETING AN ELEMENT THROUGH PASSING THE VALUE TO DELETE i.e 200"<<endl;
	list.delete_search_byValue(200);
	list.display();	
	
	cout<<endl<<endl<<"REVERSING THE LIST"<<endl;
	list.reverse();
	list.display();
	
	return 0;
}