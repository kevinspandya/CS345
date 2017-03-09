#include <bits/stdc++.h>

using namespace std;

int main(){
	vector<int> A;
	while(1){
		int temp;
		cin >> temp;
		if(temp == -1)	break;
		else	A.push_back(temp);
	}
	printf("current Content of the Array is: ");
	for(int i = 0 ; i <  A.size(); i++)	cout<< A[i] << ' ';
	cout << endl;
	if(find(A.begin(),A.end(),5)!=A.end()){
		A.erase(find(A.begin(),A.end(),5));
	}
	for(int i = 0 ; i <  A.size(); i++)	cout<< A[i] << ' ';
	cout << endl;

	return 0;
}
