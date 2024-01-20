#include <iostream>
using namespace std;

void merge(int arr[], int left, int mid, int right){
	int n1 = mid - left + 1;
	int n2 = right - mid;
	
	int leftarray[n1];
	int rightarray[n2];
	
	for(int i=0 ; i<n1 ; i++){
		leftarray[i] = arr[left + i];
	}
	for(int i=0 ; i<n2 ; i++){
		rightarray[i] = arr[mid + i + 1];
	}
	
	int i=0 , j=0 , k=left;
	while(i<n1 && j<n2){
		if(leftarray[i] <= rightarray[j]){
			arr[k] = leftarray[i];
			i++;
		}
		else{
			arr[k] = rightarray[j];
			j++;
		}
		k++;
	}
	
	while(i<n1){
		arr[k] = leftarray[i];
		i++;
		k++;
	}
	while(j<n2){
		arr[k] = rightarray[j];
		j++;
		k++;
	}
}

void mergesort(int arr[], int left, int right){
	if(left < right){
		int mid = left + (right - left) / 2;
		
		mergesort(arr,left,mid);
		mergesort(arr,mid+1,right);
		
		merge(arr,left,mid,right);
	}
}

void print(int arr[], int n){
	for(int i=0 ; i<n ; i++){
		cout<<arr[i]<<" ";
	}
	cout<<endl;
}

int main(){
	int arr[]={5,10,9,6,2,1,0,3};
	int n = sizeof(arr) / sizeof(arr[0]);
	cout<<"Original Array "<< endl;
	print(arr,n);
	
	mergesort(arr,0,n-1);
	
	cout<<"Sorted Array "<< endl;
	print(arr,n);
	
	return 0;
}