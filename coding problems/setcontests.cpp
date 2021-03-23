#include<iostream>
using namespace std;


int main(){
    int t,temp, n, k, d, sum, i;
    cin>>t;
    while(t--){
	cin>>n>>k>>d;
	sum =0;
	for(i =0;i<n;i++){
	    cin>>temp;
	    sum += temp;
	}

	temp = sum / k;
	temp = (temp > d) ? d : temp;
	cout<<temp<<endl;
	    
    }
    return 0;
}
