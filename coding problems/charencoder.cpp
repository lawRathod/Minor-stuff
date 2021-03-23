#include<iostream>
using namespace std;

int main(){
    int t;
    cin>>t;
    while(t--){
	string p;
	int q;
	cin>>q>>p;
	int let;
	for(int i=0;i<q/4;i++){
	    let = 0;
	    let += 8*(p[(i*4)+0]-'0');
	    let += 4*(p[(i*4)+1]-'0');
	    let += 2*(p[(i*4)+2]-'0');
	    let += 1*(p[(i*4)+3]-'0');
	    cout<<(char)(let+'a');
	}
	cout<<endl;

    }

    return 0;
}
