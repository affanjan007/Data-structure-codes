#include <iostream>
using namespace std;

class Node{
	public:
		int data;
		Node *ptr;
		Node(int d){
			data=d;
			ptr=NULL;
		}
};

class Stack{
	public:
		int size=0;
		Node *head;
		Stack(){
			head=NULL;
		}

	void display() {
		if(!head){
			cout<<"Stack is empty!"<<endl;
		}
	    Node *current=head;
	    while(current) {
	        cout<<current->data;
	        if (current->ptr) {
	            cout<<" -> ";
	        }
	        current=current->ptr;
	    }
	    cout<<endl;
	}

	void push(int val){
		size++;
		Node *temp=new Node(val);
		if(!head){
			head=temp;
		}
		else{
			temp->ptr=head;
			head=temp;
		}
	}
	
	void pop(){
		if(!head){
			cout<<"Stack is already empty!"<<endl;
		}
		else{
			size--;
			Node *oldhead=head;
			head=head->ptr;
			delete oldhead;
		}
	}
	
	int top(){
		if(!head){
			cout<<"Stack is empty!"<<endl;
			return 0;
		}
		else{
			return head->data;
		}
	}

	int stacksize(){
		return size;
	}
	
	bool isEmpty(){
		if(size==0){
			return true;
		}
		else{
			return false;
		}
	}
	
	void search(int val) {
	    if(!head) {
	        cout<<"Stack is empty!"<<endl;
	    }
		else{
		    Node *temp=head;
		    bool found=false;  
		    while(temp){
		        if (temp->data == val) {
		            found = true;
		            break; 
		        }
		        temp=temp->ptr;
			}
		    if(found) {
		        cout<<val<<" is found"<<endl;
		    } 
			else{
		        cout<<val<<" is not found in the stack"<<endl;
		    }
		}
	}
	
	void ClearStack(){
		while(!isEmpty()){
			pop();
		}
		cout<<"Stack is deleted!"<<endl;
	}
	
	int getMax(){
		int max=-1;
		Node *temp=head;
		while(temp){ 
		 	if(temp->data > max){
		 		max=temp->data;
			}
			temp=temp->ptr;
		}
		return max;
	}
	
	int getMin(){
		int min=999;
		Node *temp=head;
		while(temp){ 
		 	if(temp->data < min){
		 		min=temp->data;
			}
			temp=temp->ptr;
		}
		return min;
	}
	
	void sortAscending(){
		Node *current;
		Node *lastSorted=NULL;
		Node *previous=NULL;
		bool swapped;
		do{
			current=head;
			swapped=false;
			while(current->ptr != lastSorted){
				if(current->data > current->ptr->data){
					int temp=current->data;
	                current->data=current->ptr->data;
	                current->ptr->data=temp;
	                swapped = true;
				}
				previous=current;
         	    current=current->ptr;
			}
			lastSorted=current;
		} 
		while(swapped);
		display();
	}
	
	void reverse(){
		Node *current=head;
		Node *previous=NULL;
		Node *ptr=NULL;
		while(current){
			ptr=current->ptr;
			current->ptr=previous;
			previous=current;
			current=ptr;
		}
		while(previous){
			cout<<previous->data;
			if (previous->ptr) {
	            cout<<" -> ";
	        }
			previous=previous->ptr;
		}
		cout<<endl;
	}
	
	Node *concatenate(Node *mystack2, Node *mystack3){
		if(!mystack2){
			return mystack3;
		}
		else if(!mystack3){
			return mystack2;
		}
		else{
			Node *current=mystack2;
			while(current->ptr){
				current=current->ptr;
			}
			current->ptr=mystack3;
			return current;
		}
	}
};

int main(){
	Stack  mystack;
	
	mystack.push(9);
	mystack.push(4);
	mystack.push(7);
	mystack.push(3);
	mystack.push(6);
	mystack.display();
	
	mystack.pop();
	mystack.display();
	cout<<"Stack size: "<<mystack.stacksize()<<endl;
	
	if(mystack.isEmpty() == 0){
		cout<<"Is Stack empty: No"<<endl;
	}
	if(mystack.isEmpty() == 1){
		cout<<"Is Stack empty: Yes"<<endl;
	}
	
	mystack.search(4);
	
	cout<<"Maximum element in the stack: "<<mystack.getMax()<<endl;
	cout<<"Minimum element in the stack: "<<mystack.getMin()<<endl;
	
	cout<<endl<<"After sorting the stack in ascending order"<<endl;
	mystack.sortAscending();
	cout<<endl<<"After reversing the stack"<<endl;
	mystack.reverse();
	
	
	Stack mystack2;
	Stack mystack3;
	
	mystack2.push(11);
	mystack2.push(2);
	mystack2.push(10);
	
	mystack3.push(14);
	mystack3.push(15);
	mystack3.push(8);
	cout<<endl;
	
	cout<<"Stack 2"<<endl;
	mystack2.display();
	cout<<endl<<"Stack 3"<<endl;
	mystack3.display();
	
	Node *concatenated_List = mystack2.concatenate(mystack2.head,mystack3.head);
	cout<<endl<<"After concatenating Stack2 and Stack3"<<endl;
	mystack2.display();
	
	cout<<endl<<"After deleting concatenated stack"<<endl;
	mystack2.ClearStack();
		
	return 0;
}