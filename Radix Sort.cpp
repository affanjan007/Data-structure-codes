#include<iostream>
using namespace std;

int getmax(int arr[],int n){
	int max=arr[0];
	for(int i=1; i<n; i++){
		if(max<arr[i]){
			max=arr[i];
		}
	}
	return max;
}

void countsort(int arr[], int n, int exp){
	const int base=10;
	int output[n];
	int count[base] = {0};
	
	for(int i=0; i<n; i++){
		count[(arr[i] / exp) % base]++;
	}
	for(int i=1; i<base; i++){
		count[i] = count[i] + count[i-1];
	}
	for(int i=n-1; i>=0; i--){
		output[count[(arr[i] / exp) % base] - 1] = arr[i];
	}
	for(int i=0; i<n; i++){
		arr[i] = output[i];
	}
}

void radixsort(int arr[],int n){
	int max = getmax(arr,n);
	for(int exp=1; max/exp>0; exp=exp*10){
		countsort(arr,n,exp);
	}
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++){
    	cout << arr[i] << " ";
	}
        
}

int main(){
	int arr[]={16,51,29,93,30};
	int n=sizeof(arr)/sizeof(arr[0]);
	
	cout<<"Before Sorting"<<endl;
	printArray(arr, n);
	radixsort(arr,n);
	cout<<endl<<"After Sorting"<<endl;
	printArray(arr, n);
}