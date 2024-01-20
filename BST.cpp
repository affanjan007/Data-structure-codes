#include <iostream>
using namespace std;

class Node{
    public:
    int data;
    Node *left;
	Node *right;

    Node(int x){
        data=x;
        left=NULL;
        right=NULL;
    }
};

class BinaryTree{
    public:
    Node *root;
    BinaryTree(){
        root=NULL;
    }

    void insert(Node *&root_ptr, int val){
	    Node *temp=new Node(val);
	    if(root_ptr == NULL) {
	        root_ptr=new Node(val);
	    } 
		else{
	        if(val < root_ptr->data) {
	            insert(root_ptr->left, val);
	        } 
			else if(val > root_ptr->data) {
	            insert(root_ptr->right, val);
	        }
		}
	}

    void pre_order_traversal(Node *root_ptr){		//root -> left ->right
		if(root_ptr != NULL){
			cout<<root_ptr->data<<" ";
			pre_order_traversal(root_ptr->left);
			pre_order_traversal(root_ptr->right);
		}
	}
	
	void in_order_traversal(Node *root_ptr){		//left -> root -> right
		if(root_ptr != NULL){
			in_order_traversal(root_ptr->left);
			cout<<root_ptr->data<<" ";
			in_order_traversal(root_ptr->right);
		}
	}
	
	void post_order_traversal(Node *root_ptr){		//left -> right -> root
		if(root_ptr != NULL){
			post_order_traversal(root_ptr->left);
			post_order_traversal(root_ptr->right);
			cout<<root_ptr->data<<" ";
		}
	}

	int tree_height(Node* root_ptr, int height){
		if(root_ptr == NULL){
			return height;
		}
		else{
			if(root_ptr->left != NULL){
				return tree_height(root_ptr->left, height+1);
			}
			else if(root_ptr->right != NULL){
				return tree_height(root_ptr->right, height+1);
			}
		}
		return height;
	}
	
	bool search(Node* root_ptr, int val){
		if(root_ptr == NULL){
			return false;
		}
		else if(root_ptr->data == val){
			return true;
		}
		else if(root_ptr->data > val && root_ptr->left != NULL){
			return search(root_ptr->left, val);
		}
		else if(root_ptr->data < val && root_ptr->right != NULL) { 
			return search(root_ptr->right, val);
		}
		return false;
	}
	
	int getSize(Node* root_ptr) {
	    if (!root_ptr) {
	        return 0;
	    }
	    return 1 + getSize(root_ptr->left) + getSize(root_ptr->right);
	}
	
	void delete_node(Node *&root_ptr, int val){
		if(root_ptr == NULL){
			return;
		}
		else if(root_ptr->data > val){
			delete_node(root_ptr->left, val);
		}
		else if(root_ptr->data < val){
			delete_node(root_ptr->right, val);
		}
		else{
			if(root_ptr->left == NULL && root_ptr->right == NULL){
				delete root_ptr;
				root_ptr=NULL;
			}
			else if(root_ptr->left == NULL){
				Node *temp=root_ptr;
				root_ptr=root_ptr->right;
				delete temp;	
			}
			else if(root_ptr->right == NULL){
				Node *temp=root_ptr;
				root_ptr=root_ptr->left;
				delete temp;	
			}
			else{
				Node *temp=find_in_order_succesor(root_ptr->right);
                root_ptr->data=temp->data;
                delete_node(root_ptr->right,temp->data);
			}
		}	
	}
	
	Node* find_in_order_succesor(Node *ptr){
        while(ptr->left != NULL){
            ptr=ptr->left;
        }
        return ptr;
    }
};

int main(){
	BinaryTree mytree;
    
	mytree.insert(mytree.root, 15);			//					15
    mytree.insert(mytree.root, 10);			//				  /    \	
    mytree.insert(mytree.root, 20);			//			     10    20
    mytree.insert(mytree.root, 18);			//			     /      /
    mytree.insert(mytree.root, 13);			//			   13     18
  
 
	cout<<"Pre-Order: ";
	mytree.pre_order_traversal(mytree.root);
	cout<<endl;
	cout<<"In-Order: ";
	mytree.in_order_traversal(mytree.root);
	cout<<endl;
	cout<<"Post-Order: ";
	mytree.post_order_traversal(mytree.root);
	cout<<endl;
	
	int size=mytree.getSize(mytree.root);
    cout<<"Size of the BST is: "<<size+1<<endl;
    
	cout<<"Tree Height: "<<mytree.tree_height(mytree.root, 1)<<endl;
	
	if(mytree.search(mytree.root, 20)){
		cout<<"Found!"<<endl;	
	}
	else{
		cout<<"Not Found!"<<endl;
	}
	
	cout<<endl<<"Tree after deletion"<<endl<<endl;
	mytree.delete_node(mytree.root, 15);
	
	cout<<"Pre-Order: ";
	mytree.pre_order_traversal(mytree.root);
	cout<<endl;
	cout<<"In-Order: ";
	mytree.in_order_traversal(mytree.root);
	cout<<endl;
	cout<<"Post-Order: ";
	mytree.post_order_traversal(mytree.root);
	cout<<endl;
	
	return 0;
}
