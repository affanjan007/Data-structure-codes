#include <iostream>
using namespace std;

void comb_sort(int array[], int n){
	for(int gap=n/1.3 ; gap>0 ; gap/=1.3){
		for(int i=0 ; i<n-gap ; i++){
			if(array[i] > array[i+gap]){
				swap(array[i],array[i+gap]);	
			}
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
	int array[]={7,8,4,5,3,2,1,6,12,10};
	int n=sizeof(array) / sizeof(array[0]);
	
	cout<<"Unsorted Array!"<<endl;
	print(array, n);
	
	comb_sort(array, n);
	
	cout<<endl<<"Sorted Array!"<<endl;
	print(array, n);

	return 0;
}