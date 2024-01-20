#include <iostream>
using namespace std;

class Node{
	public:
		int data;
		Node* rptr;
		Node* lptr;
		Node(int val){
			data=val;
			rptr=nullptr; 
			lptr=nullptr;
		}
};

class DoubleLinkedList{
	Node* head;
	Node* tail;
	public:
		DoubleLinkedList(){
			head = nullptr;
			tail = nullptr;
		}

	int calculate_length(){	
		Node* current=head;
		int length=0;
	        do {									
	            current = current->rptr;
	            length++;
	        } 
			while(current != head);
			return length;
	}
	
	void display(){				//display elements in the list
		Node* current=head;
		while(current){
			cout<<current->data<<" ";
			current=current->rptr;
		}
		cout<<endl;
	}
	
	void append(int val){			//inserting at the end
		Node* temp=new Node(val);
		if(!head){				    //if list is initially empty
			head=temp;
			tail=temp;
		}
		else { 					// inserting at the end
		    tail->rptr = temp;
		    temp->lptr = tail;
		    tail = temp;
		}
	}
	
	void insert_pos(int val,int index){			//inserting by index value
		Node* temp=new Node(val);
			if(!head){
				head=temp;
				tail=temp;
			}
			else if(index==1){			//if inserting at the head pos
				temp->rptr=head;
				head->lptr=temp;
				head=temp;
			}
			else{
				Node* current=head;
				int count=1;
				while(current && count != index-1){
					current=current->rptr;
					count++;
				}
				
				if(!current){					//if index pos is out of bound
					cout<<"Out of bounds!"<<endl;
				}
				else if(!current->rptr){		//inserting at the end
					tail->rptr=temp;
					temp->lptr=tail;
					tail=temp;
				}
				else						   	//inserting in between
					temp->rptr=current->rptr;
					temp->lptr=current;
					current->lptr->rptr=current;
					current->rptr=temp;
			}
	}
	
	void remove(){				//deleting an element from end
		if(!head){
			cout<<"Error!"<<endl;
		}
		else{
			Node* current=head;
			Node* previous=head;
			while(current->rptr){			//moving at the end of the list
				previous=current;
				current=current->rptr;
			}
			previous->rptr=tail->rptr;
			delete tail;
		}
	}
	
	void delete_pos(int index){			//deleting element by taking index as a parameter
		if(index<=0 || !head){
			cout<<"Error!"<<endl;
		}
		else if(index==1){				//if index to delete is 1
			if (head->rptr == head) {
                delete head;
                head = nullptr;
            } 
            else{
				head=head->rptr;
			}
		}
		else{
			Node* current=head;
			Node* previous=head;
			int count=1;
			while(current->rptr && count!=index){
				previous=current;
				current=current->rptr;
				count++;
			}
			if(!current){					//if index pos is out of bound
					cout<<"Out of bounds!"<<endl;
			}
			else{
				previous->rptr=current->rptr;
				delete current;
			}
		}
	}
	
	void insert_search_byValue(int val_to_search, int val_to_add){	  //inserting element after a specific value
	    Node* temp = new Node(val_to_add);
	    if (!head) {
	        cout << "List is empty" << endl;
	    }
	    else if(head->data == val_to_search){
	    	temp->rptr=head->rptr;
	    	temp->lptr=head;
	    	head->rptr->lptr=head;
	    	head->rptr=temp;
		}
	    else {
	        Node* current = head;
	        while (current->rptr && current->data != val_to_search) {
	            current = current->rptr;
	        }
	        if(current->data != val_to_search){				//if val not find
				cout<<"Value not found!"<<endl;
			}
			else if(!current->rptr){		//inserting at the end
				tail->rptr=temp;
				temp->lptr=tail;
				tail=temp;
			}
			else{						   	//inserting in between
				temp->rptr=current->rptr;
				temp->lptr=current;
				current->lptr->rptr=current;
				current->rptr=temp;
			}
		}
	}
	
	void delete_search_byValue(int val_to_delete){			//deleting an element by taking value as a parameter
		if (!head) {
	        cout << "Error!" << endl;
	    }
	    else if(head->data == val_to_delete){			//if val to delete is head
	    	delete_pos(1);
		}
		else{
			Node* current=head;
			int count=1;
			while(current->rptr && current->data!=val_to_delete){
				current=current->rptr;
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
	
	void sort_descending(){			//sorting the list in descending order
		bool swapped;
		Node* current;
		Node* lastSorted=NULL;
		do{
			swapped=false;
			current=head;
			while(current->rptr!=lastSorted){
				if(current->data < current->rptr->data){
					int temp=current->data;
					current->data=current->rptr->data;
					current->rptr->data=temp;
					swapped=true;
				}
				current=current->rptr;
			}
			lastSorted=current;
		}
		while(swapped);
	}
	
	void reverse() {				//reversing the list
	    if (head == nullptr) {
	        cout << "List is empty." << endl;
	    } 
		else {
	        Node* previous=nullptr;
			Node* current=head;
			Node* rptr=nullptr;
			while(current){
				rptr=current->rptr;
				current->rptr=previous;
				previous=current;
				current=rptr;
			}
	 
			while(previous){
				cout<<previous->data<<" ";
				previous=previous->rptr;
			}
			cout<<endl;	
		}
	}
};

int main(){
	DoubleLinkedList list;
		
	cout<<"DOUBLY LINKED LIST"<<endl;
	cout<<"-------------------"<<endl;
	
	cout<<endl<<endl<<"DISPLAYING ALL THE ELEMENTS IN THE LIST"<<endl;
	list.append(20);
	list.append(30);
	list.append(10);
	list.append(50);
	list.append(40);
	list.display();
	
	cout<<endl<<endl<<"AFTER INSERTING AN ELEMENT ON THE 3nd INDEX"<<endl;
	list.insert_pos(100,3);
	list.display();
	
	cout<<endl<<endl<<"AFTER DELETING AN ELEMENT ON THE 1nd INDEX"<<endl;
	list.delete_pos(1);
	list.display();
	
	cout<<endl<<endl<<"INSERTING 300 AFTER 30 VALUE"<<endl;
	list.insert_search_byValue(30,300);
	list.display();
		
	cout<<endl<<endl<<"AFTER REMOVING LAST ELEMENT FROM THE LIST"<<endl;
	list.remove();
	list.display();

	cout<<endl<<endl<<"AFTER DELETING AN ELEMENT THROUGH PASSING THE VALUE TO DELETE i.e 30"<<endl;
	list.delete_search_byValue(30);
	list.display();
	
	cout<<endl<<endl<<"SORTING THE LIST IN DESCENDING ORDER"<<endl;
	list.sort_descending();
	list.display();

	cout<<endl<<endl<<"AFTER REVERSING THE LIST"<<endl;
	list.reverse();

	return 0;
}