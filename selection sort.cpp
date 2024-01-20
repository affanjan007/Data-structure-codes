#include <iostream>
using namespace std;

void selection_sort(int array[], int n){
	for(int i=0 ; i<n-1 ; i++){
		int min_index=i;
		for(int j=i+1 ; j<n ; j++){
			if(array[j] < array[min_index]){
				min_index = j;
			}	
		}
		
		if(min_index != i){
			swap(array[min_index],array[i]);
		}
	}
}

void print(int array[], int n){
	for(int i=0 ; i<n ; i++){
		cout<<array[i]<<" ";
	}
	cout<<endl;
}


int main(){
	int array[]={7,8,4,3,5,1,2};
	int n=sizeof(array) / sizeof(array[0]);
	
	cout<<"Unsorted Array!"<<endl;
	print(array, n);
	
	selection_sort(array, n);
	
	cout<<endl<<"Sorted Array!"<<endl;
	print(array, n);
	
	return 0;
}