#include <bits/stdc++.h>
void foo();
using namespace std;
	ofstream fileptr;
int main(int argc, char *argv[]){
	fileptr.open(argv[1]);
	foo();
	fileptr.close();
	return 0;
}
void foo(){
	string line;
	int n = 41;
	fileptr << n << endl;	
	for(int i = 0 ; i < n ; i++){
		fileptr << rand()%100 << endl;
	}
}