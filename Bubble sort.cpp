#include <iostream>
using namespace std;

void bubble_sort(int array[], int n){
	bool flag=false;
	for(int i=0 ; i<n-1 ; i++){
		for(int j=0 ; j<n-i-1 ; j++){
			if(array[j] > array[j+1]){
				swap(array[j],array[j+1]);
				flag=true;
			}
		}
		if(flag != true)
			break;
	}
}

void print(int array[], int n){
	for(int i=0 ; i<n ; i++){
		cout<<array[i]<<" ";
	}
	cout<<endl;
}

int main(){
	int arrayA[]={7,8,4,3,5,1,2};
	int arrayB[]={3,4,5,6,7,8,9};
	int n=sizeof(arrayA) / sizeof(arrayA[0]);
	int m=sizeof(arrayB) / sizeof(arrayB[0]);
	
	cout<<"Unsorted Array A!"<<endl;
	print(arrayA, n);
	
	bubble_sort(arrayA, n);
	
	cout<<endl<<"Sorted Array A!"<<endl;
	print(arrayA, n);
	
//	bubble_sort(arrayB, m);
//	
//	cout<<endl<<"Sorted Array B!"<<endl;
//	print(arrayB, m);
//	
	return 0;
}