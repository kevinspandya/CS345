#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef vector< vector<int> > vvi;

void printarr(vi &A,int ,int );
void goforsort(vi &A);
void general_pass(vi &A,int n_run,int M);
void general_pass1(vi &A,int n_run,int M);
void pass0(vi &A);
void add_B(vi &A,vi &B,int starting_index,int block_no,int );
void run_analyzer(vi &A,int n_run,int M,int run_no);
int N,W,k,p;
int main(int argc,char *argv []){
	W = atoi(argv[1]);
	k = atoi(argv[2]);
	p = atoi(argv[3]);
	ifstream fileptr;
	fileptr.open(argv[4]);
	string line;
	getline(fileptr,line);
	N = atoi(line.c_str());
	vi A(N);
	int i =0;
	while(getline(fileptr,line)){
		A[i++]= atoi(line.c_str());
	}
	//cout << N<<' ' << A.size();
	goforsort(A);
	//printarr(A,0,N)
;	return 0;
}
void goforsort(vi &A){
	pass0(A);
	int n_run = k*W;//No of records in a run
	int run = ceil(float(N)/n_run);
	int M = ceil((float(W)/p) - 1.0);
	int pass = ceil(log(run)/log(M));
	printf("%d %d %d %d\n",run,M,pass,n_run);
	for(int i =0 ; i < pass ; i++){
		cout << "Pass " << i+1 << endl;
		general_pass1(A, n_run, M);
		n_run*=M;
	}
}

void general_pass1(vi &A,int n_run,int M){
	int no_run_req = ceil(float(N)/(n_run*M));
	for(int i = 0 ; i < no_run_req ; i++){
		cout << "Run " << i+1 << ": ";
		run_analyzer(A,n_run,M,i);
		printarr(A,i*n_run*M,n_run*M);
	}
}

void run_analyzer(vi &A,int n_run,int M,int run_no){
	vvi B(M);	
	vi index(M,0);
	for(int i = 0; i <M; i++){
		int starting_index = run_no*n_run*M + i*n_run;
		if(starting_index>=A.size()){
			index[i] = -1;
		}
		else	
		{
			add_B(A,B[i],starting_index,index[i],n_run);
			//printf("Starting index %d\n",starting_index);
		}
	}
	/*printf("Contents of B are: \n");
	for(int i = 0 ; i < M ; i++){
		for(int j =0 ; j < B[i].size(); j++)	cout << B[i][j] <<' ';
			cout << endl;
	}*/
	vi aux;	//Auxiliary array
	while(aux.size()<n_run*M){
		if(run_no*n_run*M +aux.size()>=A.size())	break;
		for(int i = 0 ; i < M ; i++){
			int starting_index = run_no*n_run*M + i*n_run;
			if(B[i].empty()){
				add_B(A,B[i],starting_index,++index[i],n_run);
				/*printf("Starting index %d %d %d ",starting_index,i,index[i]);
				for(int j = 0 ; j < B[i].size(); j++)	cout << B[i][j] <<' ';
				cout << endl;*/
			}
		}
		int min_i = 0,minvalue = INT_MAX;
		for(int i = 0 ; i < M ; i++){
			if(!B[i].empty()){
				if(B[i][0]<minvalue){
					minvalue = B[i][0];
					min_i = i;
				}
			}
		}
		/*for (std::vector<int>::iterator i = aux.begin(); i != aux.end(); ++i){
			cout << *i <<' ';
		}*/
		//cout << endl;
		aux.push_back(minvalue);
		B[min_i].erase(B[min_i].begin());
	}
	/*for (int i = 0; i <aux.size(); ++i)
	{
		A[run_no*n_run*M+i] = aux[i];
	}*/
	copy(aux.begin(),aux.end(), A.begin()+ run_no*n_run*M);
}

void add_B(vi &A,vi &B,int starting_index,int block_no,int n_run){
	int smallest_index = starting_index+block_no*p*k;
	for(int i = smallest_index; i < smallest_index +p*k;i++){
		if(i>=starting_index+n_run || i >= A.size())	break;
		B.push_back(A[i]);
	}
}
// Starting index of each run may be given by n_run*M*run_no
/*void run_analyzer(vi &A,int n_run,int M,int run_no){
	int starting_index = run_no*n_run*M;
	vvi index(M,vi (2,1));
	vi aux(n_run*M);
	vvi B(M,vi (p*k,INT_MIN) );
	for(int i = 0 ; i < M ; i++){
		index[i][0] = i*n_run;
		copy(A.begin()+min(N,starting_index+i*p*k),A.begin()+min(N,starting_index+((i+1)*p*k)),B[i]);

	}
	while(1){
		bool flag = true;
		for(int i = 0 ; i < M ; i++){
			if(index[i]==p*k)
		}
	}

}*/
void general_pass(vi &A,int n_run,int M){
	int r = 0;
	for(int i = 0 ; i< A.size() ; i+=n_run*M){
		sort(A.begin()+i,A.begin()+min(i+n_run*M,N));
		cout<< "run " << ++r << ": ";
		printarr(A,i,n_run*M);
	}
}

void pass0(vi &A){
cout << "Pass 0" << endl;
	int r = 0;
	for(int i = 0 ; i< A.size() ; i+=W*k){
		sort(A.begin()+i,A.begin()+min(i+W*k,N));
		cout<< "run " << ++r << ": ";
		printarr(A,i,W*k);
	}
}
void printarr(vi &A,int i,int j){
	for (int t = i; t < i+j&& t < N; ++t)
	{
		cout<<A[t] << ' ';
	}
	cout << endl;
}