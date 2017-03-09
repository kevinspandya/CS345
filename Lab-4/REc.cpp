//DFS Algo
#include <bits/stdc++.h>

using namespace std;
typedef vector< vector<int> > vvi;
typedef vector<int> vi;
bool isCyclicUtil(int v, vector<bool> &visited, vector<bool> &recStack, vvi &A);
bool isCyclic(vvi &A);
void topologicalSort(vvi &A,vi &ans);
void topologicalSortUtil(int v, vector<bool> &visited, stack<int> &Stack,vvi &A);
void insert(vvi &A,char *argv []);

void insert_func(vvi &A);
int V = 4;

int main(int argc,char *argv [])
{
	V = atoi(argv[1]);
	vvi A(V,vector<int>(V,0));
	insert(A,argv);
	cout << "Lean on" << endl;
	vi ans;
	//insert_func(A);
	if(isCyclic(A))		cout << "Not Conflict Serializable" << endl;
	else{
		cout << "Let Me Love You" << endl;
		topologicalSort(A,ans);
	}
   return 0;
}
void insert(vvi &A,char *argv []){
	int tr = V;
	FILE *fp;
    int obj=atoi(argv[2]);
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char * pch;
    fp = fopen(argv[3], "r");

   map<string,int> ind;
   vector< vector<int> > hisr(tr,vector<int>(obj,-1));
   vector< vector<int> > hisw(tr,vector<int>(obj,-1));
   int count=0;	
   while ((read = getline(&line, &len, fp)) != -1 && read >3) {
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
   		for(int i=0;i<tr;i++){
   			if(i!=tr_no ){

   			if((act=='r'&& hisw[i][cur_obj]==1) || (act=='w'&&(hisw[i][cur_obj]==1 || hisr[i][cur_obj]==1)) ){
   					cout << i << "i ";
   					A[i][tr_no]=1;
   				}
   			}
   		}
    }
    for(int i=0;i<tr;i++)
   		{
   			for(int j=0;j<obj;j++)
    			cout<<i<<" "<<j<<"-->"<<hisr[i][j]<<hisw[i][j];
    		cout<<endl;
    	}
    cout<<endl;
    for(int i=0;i<tr;i++)
    	{
    		for(int j=0;j<tr;j++)
    			cout<<A[i][j]<<" ";
    		cout<<endl;
    	}
    free(line);
}


/*int main(){
	vvi A(V, vector<int>(V,0));
	vi ans;
	insert_func(A);
	vi dfs_output;
	if(isCyclic(A))		cout << "Not Conflict Serializable" << endl;
	else{
		cout << "Let Me Love You" << endl;
		topologicalSort(A,ans);
	}
	return 0;
}*/
void insert_func(vvi &A){
	A[0][1] = 1;
	A[0][3] = 1;
	A[3][2] = 1;
}

// A recursive function used by topologicalSort
void topologicalSortUtil(int v, vector<bool> &visited, stack<int> &Stack,vvi &A)
{
    // Mark the current node as visited.
    visited[v] = true;

    // Recur for all the vertices adjacent to this vertex
    for(int i = 0 ; i < V ; i++){
        if (A[v][i]==1 && !visited[i])
            topologicalSortUtil(i, visited, Stack,A);
    }
    // Push current vertex to stack which stores result
    Stack.push(v);
}
 
// The function to do Topological Sort. It uses recursive 
// topologicalSortUtil()
void topologicalSort(vvi &A,vi &ans)
{
    stack<int> Stack;
    vector<bool> visited(V,false);

    // Call the recursive helper function to store Topological
    // Sort starting from all vertices one by one
    for (int i = 0; i < V; i++)
      if (visited[i] == false)
        topologicalSortUtil(i, visited, Stack,A);
    // Print contents of stack
    while (Stack.empty() == false)
    {
        cout << Stack.top() << " ";
        Stack.pop();
    }
}

bool isCyclicUtil(int v, vector<bool> &visited, vector<bool> &recStack, vvi &A){
    if(visited[v] == false)
    {
        // Mark the current node as visited and part of recursion stack
        visited[v] = true;
        recStack[v] = true;

        // Recur for all the vertices adjacent to this vertex
        for(int i = 0; i <V; ++i)
        {
        	if(A[v][i] == 1){
            	if ( !visited[i] && isCyclicUtil(i, visited, recStack,A))
                	return true;
            	else if (recStack[i])
                	return true;
        	}
        }
 
    }
    recStack[v] = false;  // remove the vertex from recursion stack
    return false;
}
 
// Returns true if the graph contains a cycle, else false.
// This function is a variation of DFS() in http://www.geeksforgeeks.org/archives/18212
bool isCyclic(vvi &A)
{
    // Mark all the vertices as not visited and not part of recursion
    // stack
    vector<bool> visited(V,false);
    vector<bool> recStack(V,false);
    // Call the recursive helper function to detect cycle in different
    // DFS trees
    for(int i = 0; i < V; i++)
        if (isCyclicUtil(i, visited, recStack,A))
            return true;
    return false;
}