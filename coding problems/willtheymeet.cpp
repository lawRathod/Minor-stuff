#include<iostream>
using namespace std;

bool willtheymeet(int x1, int x2, int v1, int v2){
	int f=x1,l=x2,fv=v1,lv=v2;
	if(x1>x2){
		f=x2;
		fv = v2;
		l = x1;
		lv = v1;
	}

	if(fv > lv && f!=l){
		return true;
	}

	return false;

}

int main(){
	int n = 2;
	int arr[][4] = {{5,4,8,7}, {6,4,6,8}};

	for(int i=0;i<n;i++){
		bool ans = willtheymeet(arr[i][0],arr[i][1],arr[i][2],arr[i][3]);
		cout<<ans<<endl;
	}

	return 0;
}
