#include <iostream>
using namespace std;

class Node {
	public:
	int data;
	Node* ptr;
	Node(int val){
		data=val;
		ptr=nullptr;
	}
};

class LinkedList {
	Node* head;
	public:
	LinkedList(){
		head = nullptr;		//initially head is null
	}
	
	void display(){
		Node* current=head;
		while(current){			//until current ptr is not null
			cout<<current->data<<" ";
			current=current->ptr;
		}
		cout<<endl;
	}
	
	void insert(int val){			//add data at the end of the linkedlist
		Node* temp=new Node(val);
		if(!head) {
			head=temp;
		}
		else{
			Node* current=head;
			while(current->ptr){		//moving to end of list to add data
				current=current->ptr;
			}
			current->ptr=temp;		//current pointing to last node in the list
		}
	}
	
	void delete_position(int pos) {		   //delete data from a specific position
		if(pos<=0 && !head){			//if head is not null and pos is gretaer then 0
			cout<<"Error!"<<endl;
		}
		else if (pos==1){				//if position to delete is 1
			if (head->ptr == head) {	//if only one element, head will ne null
                delete head;
                head = nullptr;
            } 
            else{
            	head=head->ptr;
			}
		}
		else{
			Node* previous=head;
			Node* current=head;
			int count=1;
			while(current && count!=pos){
				previous=current;		//assgning current ptr to previous ptr
				current=current->ptr;	//current pointing to next node
				count++;
			}
			
			if(!current){				//if cuurent in null
			 	cout<<"Out of bound!"<<endl;
			 }
			 
			else{			//when we reach to pos to find, while loop will break and will go to else
			 	previous->ptr=current->ptr;			//making previous point to same node as of current
			 	delete current;						
			}
		}
	}
	
	void insert_position(int pos,int val){			//insert data at a specific position
		Node* temp=new Node(val);
		if(pos<=0){
			cout<<"Error"<<endl;
			delete temp;
		}
		else if(pos==1 || !head){		//if head is null or insert pos is 1
			temp->ptr=head;				// temp will point head
			head=temp;
		}
		else{
			Node* current=head;
			int count=1;
			while(current && count!=pos-1) {		//pos-1 so to add element on that position
				current=current->ptr;				//current pointing to next node
				count++;
			}
			
			if(!current){
			 	cout<<"Out of bound!"<<endl;
			 	delete temp;
			 }
			 
			else{					//when we reach to pos-1 to find, while loop will break and will go to else
			 	temp->ptr = current->ptr;		//making temp point to same node as of current
				current->ptr = temp;			//current ptr to point temp node
			}	
		}
	}
	
	void insert_search_byValue(int val_to_search, int val_to_add){		//insert data after a specific value
		Node* temp=new Node(val_to_add);
		if(!head){
			cout<<"Error! List is empty"<<endl;
			delete temp;
		}
		else{
			Node* current=head;
			while(current && current->data!=val_to_search){		//until we reach to the value
				current=current->ptr;							//current pointing to next node
			}
			if(!current){
				cout << "Error! Number not found"<<endl;
				delete temp;
				}
			else{			//after val is find, while will break and else will continue
				temp->ptr = current->ptr;		//making temp point to same node as of current
				current->ptr = temp;			//current ptr to point temp node
			}			
		}
	}
	
	void delete_search_byValue(int value_to_delete){
		if(!head){
			cout<<"List is empty!"<<endl;
		}
		else if(head->data==value_to_delete){		//if val to delete is on first index
			head=head->ptr;
		}
		else{
			Node* previous=head;
			Node* current=head;
			while(current && current->data!=value_to_delete){		//until we reach to the value
				previous = current;			//assgning current ptr to previous ptr
				current = current->ptr;		//current pointing to next node
			}
			
			if(!current){
				cout<<"Error! Number not found"<<endl;
			}
			else{
				previous->ptr=current->ptr;			//making previous point to same node as of current
				delete current;
			}
		}
	}
	
	void reverse(){			//revering the list
		if (head==NULL) {
		    cout<<"List is empty."<<endl;
		}
		else{
			Node* previous=nullptr;
			Node* current=head;
			Node* ptr=nullptr;
			while(current){
				ptr=current->ptr;
				current->ptr=previous;
				previous=current;
				current=ptr;
			}
			while(previous){
				cout<<previous->data<<" ";
				previous=previous->ptr;
			}
			cout<<endl;
		}
	}
	
	void sort_descending() {
		bool swapped;
	    Node* current;
	    Node* lastSorted = NULL;
     	do{
   	        swapped=false;
	        current=head;
	        while (current->ptr!=lastSorted) {
	            if (current->data < current->ptr->data) {
	                int temp=current->data;
	                current->data=current->ptr->data;
	                current->ptr->data=temp;
	                swapped = true;
	            }
	            current=current->ptr;
	        }
	        lastSorted = current;
        } 
		while (swapped);
		while(current){
			cout<<current->data<<" ";
			current=current->ptr;
		}
		cout<<endl;
    }
};


int main(){
	LinkedList single;
	
	cout<<"SINGLE LINKED LIST"<<endl;
	cout<<"-------------------"<<endl;
	
	cout<<endl<<endl<<"DISPLAYING ALL THE ELEMENTS IN THE LIST"<<endl;
	single.insert(1);	//inserting 3 elemenets
	single.insert(2);
	single.insert(3);
	single.display();	
	
	cout<<endl<<endl<<"SORTING THE LIST IN DESCENDING ORDER"<<endl;
	single.sort_descending();	//sorting in descending order
	
	cout<<endl<<endl<<"AFTER DELETING AN ELEMENT ON THE 2nd INDEX"<<endl;
	single.delete_position(2);	//deleting from 2nd index
	single.display();

	cout<<endl<<endl<<"AFTER INSERTING AN ELEMENT ON THE 2nd INDEX"<<endl;
	single.insert_position(2, 500);	//adding 100 on the 3rd index
	single.display();
	
	cout<<endl<<endl<<"INSERTING AN ELEMENT AFTER 500 VALUE"<<endl;
	single.insert_search_byValue(500, 50);		//adding 50 after 500

	single.display();
	
	cout<<endl<<endl<<"AFTER DELETING AN ELEMENT THROUGH PASSING THE VALUE TO DELETE i.e 500"<<endl;
	single.delete_search_byValue(500);		//deleting 500, deleting by passing the value to delete
	single.display();
	
	cout<<endl<<endl<<"REVERSING THE LIST"<<endl;
	single.reverse();		//reversing the list
}