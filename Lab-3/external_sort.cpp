#include <cmath>
#include <string>
#include <vector>
#include <bits/stdc++.h>
#include <stdio.h>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <fstream>
using namespace std;

bool mergeempty(vector<int>* merge,int base)
{
	bool r=true;
	for(int i=0;i<base;i++)
	{
		if(merge[i].size()!=0)
		{
		r=false;
		break;
		}
	}
	return r;
}




int* createpass0(int* A,int p,int k,int b,int N)
{
	int i;
	for(i=0;i<N;)
	{
		if(i+p*k-1 < N)
		{
		sort(A+i,A+i+p*k);
		i=i+p*k;
		}
		else
		{
		sort(A+i,A+N);
		i=N;
		}
	}
		
	return A;
	
}
int* externalsort(int* A,int p,int k,int b,int passid,int run_size,int N,int count)
{
	int diff=run_size;
	int base=(p-b)/b;
	if(run_size>=N)
		{
			for(int i=0;i<N;i++)
			//printf("%d ",A[i]);
			cout<<A[i]<<" ";
			return A;
		}
	if(passid==0)
			{
			A=createpass0(A,p,k,b,N);
			int i,count=0;
		
			//printf("passid %d  \n",passid);
			cout<<"passid "<<passid<<endl;
			for(i=0;i<N;++i)
				{
				cout<<A[i]<<"  ";
				count++;
				if(count%(p*k)==0)
				cout<<"||";	
				
				}

				count=(int)ceil(((double)N)/(p*k)); //no. of runs
				run_size=p*k;
			cout<<endl<<"No.of runs= "<<count<<endl;
			return externalsort(A,p,k,b,1,run_size,N,count);	
			}
	else
	{
		
		int B[N];
		int index=0;
		int *endptr[count];
		int *startptr[count];
		for(int i=0;i<count;i++)
		{
			startptr[i]=&A[i*run_size];
			if((i+1)*run_size>=N)
			endptr[i]=&A[N-1];			//to update diff,count
			else
			endptr[i]=&A[(i+1)*run_size-1];
		}	
		int flag=0;//denotes that at present the merging isn't completed
		int present_runs=(int)ceil(((double)count)/base);
	
		vector <int> merge[base];
		vector <int> buffer;
		//while(!allmerge(startptr,endptr,count)) //when pass will end loop terminates
		//{
			for(int i=0;i<present_runs;i++)	//for different runs in prv stages
			{
						
				if(i!=present_runs-1)
				{
					int m=i*base*run_size;		//denotes run from which we start
					for(int j=m;j<m+base*run_size;)		//taking out b pages from base runs
					{
							
							for(int t=0;t<b*k;t++)
							{	if(startptr[j/run_size]<=endptr[j/run_size])		//fill mergebuffer
								{
								if(merge[(j-m)/run_size].size()<k*b)
								{				
								merge[(j-m)/run_size].push_back(*(startptr[j/run_size]));
								startptr[j/run_size]=1+startptr[j/run_size];
								}
								}	
								
							}
						j+=run_size;
					}	
				
					while(!mergeempty(merge,base))
					{
						if(buffer.size()==b*k)
						{
							//write in array
							vector <int> :: iterator l;
							for(l=buffer.begin();l!=buffer.end();++l)
							{
								B[index]=*l;
								index++;
							}
							
								buffer.erase(buffer.begin(),buffer.end());
								
							
						}
						int min=100000,minindex;
						
						for(k=0;k<base;k++)
						{
							if(merge[k].size())	
								if(min>*(merge[k].begin()))
								{
									min=*(merge[k].begin());
									minindex=k;	
								}

						}
							buffer.push_back(min);
							merge[minindex].erase(merge[minindex].begin());
							
							if(startptr[i*base+minindex]<=endptr[i*base+minindex])
							{
								merge[minindex].push_back(*(startptr[i*base+minindex]));
								startptr[i*base+minindex]+=1;
							}		
					}	
			
		
				
				}
				else
				{
					int m=i*base*run_size;		//denotes run from which we start runs at a time
					int extra=count%base;
					int sz;
					if(extra==0)
					{
						sz=base;
					}
					else
						sz=extra;


					for(int j=m;j<m+sz*run_size;)		//taking out b pages from base runs
					{
							
							for(int t=0;t<b*k;t++)
							{	if(startptr[j/run_size]<=endptr[j/run_size])		//fill mergebuffer
								{
								if(merge[(j-m)/run_size].size()<k*b)
								{				
								merge[(j-m)/run_size].push_back(*(startptr[j/run_size]));
								startptr[j/run_size]=1+startptr[j/run_size];
								}
								}	
								else
									break;
							}
						j+=run_size;
					}	
				
					while(!mergeempty(merge,sz))
					{
						if(buffer.size()==b*k)
						{	vector <int> :: iterator l;
							for(l=buffer.begin();l!=buffer.end();++l)
							{
								B[index]=*l;
								index++;
							}
							
								buffer.erase(buffer.begin(),buffer.end());
								
							
							
						}
						int min=100000,minindex;
						
						for(k=0;k<sz;k++)		//sz is for runs in prev pass
						{
							if(merge[k].size())	
								if(min>*(merge[k].begin()))
								{
									min=*(merge[k].begin());
									minindex=k;	
								}

						}
							buffer.push_back(min);
							merge[minindex].erase(merge[minindex].begin());
							
							if(startptr[i*base+minindex]<=endptr[i*base+minindex])
							{
								merge[minindex].push_back(*(startptr[i*base+minindex]));
								startptr[i*base+minindex]+=1;
							}	
					}	
				
		
				}
				
				
			}
		
		//}	//the pass has ended
		if(buffer.size()!=0)
		{
							vector <int> :: iterator l;
							for(l=buffer.begin();l!=buffer.end();++l)
							{
								B[index]=*l;
								index++;
							}
							
								buffer.erase(buffer.begin(),buffer.end());
								
							
		}
		run_size=run_size*base;
		
		count=present_runs;
		//printf("\n\n || passid %d\n",passid);
		cout<<endl<<endl<<"||"<<"passid "<<passid<<endl;
			passid++;
			for(int i=0;i<N;i++)
			{
			//printf("%d ",B[i]);
			cout<<B[i]<<" ";
			if((i+1)%run_size==0)
			//printf("||");
			cout<<"||";
			}
			//printf("\n");
			cout<<endl<<"No.of runs= "<<count<<endl;
			cout<<endl;
			for(int i=0;i<N;i++)
				{
					A[i]=B[i];
				}
			return externalsort(A,p,k,b,passid,run_size,N,count);
	}
}

int main (int argc ,char** argv)
{
	/*if(argc!=6)
	{
		printf("Invalid arguments\n");
		return 0;
	}*/
	char input_file[100];
	char output_file[100];
	int p=atoi(argv[2]);
	int k=atoi(argv[3]);
	int b=atoi(argv[4]);
	
	//create vector A by reading file

	int *A,N;

	ifstream infile;
	infile.open(argv[1]);	
	cin>>N;
	string line;
	getline(infile,line);
	N=atoi(line.c_str());
	A=new int [N];
	int i=0;
	while(getline(infile,line)){
		A[i++]= atoi(line.c_str());
	}	//reading from file
	infile.close();

	
	return 0;
}
