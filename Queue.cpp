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

class Queue{
	public:
		int size=0;
		Node *head;
		Node *tail;
		Queue(){
			head=NULL;
			tail=NULL;
		}

	void display() {
		if(!head){
			cout<<"Queue is empty!"<<endl;
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

	void enqueue(int val){			//push
		size++;
		Node *temp=new Node(val);
		if(!head){
			head=temp;
			tail=temp;
		}
		else{
			tail->ptr=temp;
			tail=temp;
		}
	}
	
	void dequeue(){					//pop from head
		if(!head){
			cout<<"Queue is already empty!"<<endl;
		}
		else{
			size--;
			Node *oldhead=head;
			head=head->ptr;
			delete oldhead;
		}
	}
	
	int peek(){						//return top most elemenet
		if(!head){
			cout<<"Queue is empty!"<<endl;
			return 0;
		}
		else{
			return head->data;
		}
	}

	int queueSize(){
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
	        cout<<"Queue is empty!"<<endl;
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
		        cout<<val<<" is not found in the queue"<<endl;
		    }
		}
	}
	
	void ClearQueue(){
		while(!isEmpty()){
			dequeue();
		}
		cout<<"Queue is deleted!"<<endl;
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
		Node* previous=NULL;
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
	
	Node *concatenate(Node *myqueue2, Node *myqueue3){
		if(!myqueue2){
			return myqueue3;
		}
		else if(!myqueue3){
			return myqueue2;
		}
		else{
			Node *current=myqueue2;
			while(current->ptr){
				current=current->ptr;
			}
			current->ptr=myqueue3;
			return current;
		}
	}
};


int main(){
	Queue  myqueue;
	
	myqueue.enqueue(9);
	myqueue.enqueue(4);
	myqueue.enqueue(7);
	myqueue.enqueue(3);
	myqueue.enqueue(6);
	myqueue.display();
	
	myqueue.dequeue();
	myqueue.display();
	
	cout<<"Top most elemenet: "<<myqueue.peek()<<endl;
	
	if(myqueue.isEmpty() == 0){
		cout<<"Is Queue empty: No"<<endl;
	}
	if(myqueue.isEmpty() == 1){
		cout<<"Is Queue empty: Yes"<<endl;
	}

	cout<<"Queue size: "<<myqueue.queueSize()<<endl;
	
	myqueue.search(7);
	
	cout<<"Maximum element in the queue: "<<myqueue.getMax()<<endl;
	cout<<"Minimum element in the queue: "<<myqueue.getMin()<<endl;
	
	cout<<endl<<"After sorting the queue in ascending order"<<endl;
	myqueue.sortAscending();
	cout<<endl<<"After reversing the queue"<<endl;
	myqueue.reverse();

	
	Queue myqueue2;
	Queue myqueue3;
	
	myqueue2.enqueue(11);
	myqueue2.enqueue(2);
	myqueue2.enqueue(10);
	
	myqueue3.enqueue(14);
	myqueue3.enqueue(15);
	myqueue3.enqueue(8);
	cout<<endl;
	
	cout<<"Queue 2"<<endl;
	myqueue2.display();
	cout<<endl<<"Queue 3"<<endl;
	myqueue3.display();
	
	Node *concatenated_List = myqueue2.concatenate(myqueue2.head,myqueue3.head);
	cout<<endl<<"After concatenating Queue2 and Queue3"<<endl;
	myqueue2.display();
	
	cout<<endl<<"After deleting concatenated Queue"<<endl;
	myqueue2.ClearQueue();
	
	return 0;
}
