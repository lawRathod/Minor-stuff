#include <iostream>
using namespace std;

//using moores voting algo

int candidateElement(int arr[], int n){
	int count = 0;
	int ele = arr[0];

	for(int i=1;i<n;i++){
		if(arr[i] == ele){
			count++;
		} else {
			count = 0;
			ele = arr[i];
		}
	}

	return ele;
}

int majorityElement(int arr[], int n){
	int can = candidateElement(arr, n);
	int c = 0;
	for(int i=0;i<n;i++){
		if(arr[i] == can) {
			c++;
		}
	}

	if(c > n/2) return can;

	return -1;
}

int main(){
	int arr[] = {3, 3, 4, 2, 4, 4, 2, 4, 4};
	int brr[] = {3, 3, 4, 2, 4, 4, 2, 4};

	cout<<majorityElement(arr, 9)<<endl;
	cout<<majorityElement(brr, 8)<<endl;

	return 0;
}
