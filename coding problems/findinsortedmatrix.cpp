#include<iostream>
using namespace std;

void searchingmatrix(int mat[4][4], int ele){
	int i=0, j=3;
	while(i<4 && j>=0){
		if(mat[i][j] == ele){
			cout<<"found at ("<<i<<" "<<j<<")"<<endl;
			return;
		}
		if(mat[i][j] > ele) j--;
		else i++;
	}

	cout<<"NOT FOUND"<<endl;
}

int main(){
	int mat[4][4] = { {10, 20, 30, 40},
		{15, 25, 35, 45},
		{27, 29, 37, 48},
		{32, 33, 39, 50}};

	searchingmatrix(mat, 29);
	searchingmatrix(mat, 32);
	searchingmatrix(mat, 33);
	searchingmatrix(mat, 100);
	return 0;
}
