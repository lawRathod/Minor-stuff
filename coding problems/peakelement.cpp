#include<iostream>
using namespace std;

int findPeakElement(int arr[], int n){
	if(n==1) return arr[0];
	if(arr[0] >= arr[1]) return arr[0];
	if(arr[n-1] >= arr[n-2]) return arr[n-1];

	for(int i=1;i<n-1;i++){
		if(arr[i] >= arr[i-1] && arr[i] >= arr[i+1]){
			return arr[i];
		}
	}

	return -1;
	
}

int main(){
	int arr[] = {5, 10, 20, 15};
	int brr[] = {10, 13, 15, 2, 23, 90, 67};

	cout<<findPeakElement(arr, 4)<<endl;
	cout<<findPeakElement(brr, 6)<<endl;
	return 0;
}
