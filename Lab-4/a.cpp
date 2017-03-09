#include <bits/stdc++.h>
using namespace std;
int main(int argc,char *argv [])
{
	int tr=2;
	int obj=2;
	//ifstream fileptr;
	//fileptr.open(argv[1]);
	FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char * pch;
   fp = fopen("f.txt", "r");

   map<string,int> ind;
   vector< vector<int> > hisr(tr,vector<int>(obj,-1));
   vector< vector<int> > hisw(tr,vector<int>(obj,-1));
   vector< vector<int> > a(tr,vector<int>(tr,-1));

   int count=0;	
   while ((read = getline(&line, &len, fp)) != -1) {
        //printf("Retrieved line of length %zu :\n", read);
        //printf("%s", line);
   		pch = strtok (line," ,.-");
   		int tr_no=atoi(pch);
   		pch = strtok (NULL, " ");
   		char act=pch[0];
   		pch = strtok (NULL, " ,.-");
   		string s=pch;
   		if(ind.find(s)==ind.end())
   			ind.insert(make_pair(s,count++));
   		cout<<tr_no<<" "<<act<<" "<<ind[s]<<endl;
   		int cur_obj=ind[s];
   		if(act=='r')
   			hisr[tr_no][cur_obj]=1;
   		if(act=='w')
   			hisw[tr_no][cur_obj]=1;
   		for(int i=0;i<tr;i++)
   			if(i!=tr_no && a[i][tr_no]==-1)
   			{
   				if(act=='r'&&hisw[i][cur_obj]==1 || hisw[i][cur_obj]==1 )
   					a[i][tr_no]=1;
   			}
    }
    /*for(int i=0;i<tr;i++)
   		{
   			for(int j=0;j<obj;j++)
    			cout<<i<<" "<<j<<"-->"<<hisr[i][j]<<hisw[i][j];
    		cout<<endl;
    	}
    cout<<endl;
    for(int i=0;i<tr;i++)
    	{
    		for(int j=0;j<tr;j++)
    			cout<<a[i][j]<<" ";
    		cout<<endl;
    	}*/
   free(line);
   return 0;
}