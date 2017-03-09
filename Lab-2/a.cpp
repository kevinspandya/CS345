#include "meta.h"
vector< pair<int,vector<int> *> > dir;
int main(int argc,char *argv []){
	//global_depth = (int)argv[1];
	//BUCKET_SIZE = (int)argv[2];
	//cout << "Hello World"<<global_depth<<BUCKET_SIZE<< endl;	
	//cout << argv[1]<< endl;
	//dir = *new vector< pair<int,vector<int> *> > (pow(2,global_depth),(make_pair(global_depth,add_new_bucket())));
	for(int k=0;k<pow(2,global_depth);k++)
		dir.push_back(make_pair(global_depth,add_new_bucket()));
	cout << dir.size()<<' '<< hash_function(5);
	//double_directory();
	status();
	while(1){
		int temp,val;
		cout << "Type your option: " ;
		cin >> temp;
		switch(temp){
		case(1):
			cin >> val;
			insert(val);
			status();
			break;
		case(2):
			cin >> val;
			cout << search(val)<< endl;	
			break;
		case(3):
			cin >> val;
			lazy_delete(val);
			status();
			break;
		case(4):
			cin >> val;
			bucket_delete(val);
			status();
			break;
		case(5):
			cin >> val;
			directory_delete(val);
			status();
			break;
		}
		if(temp>5)	break;
	}
	return 0;
}
void lazy_delete(int key){
	vi *temp = dir[hash_function(key)].second;
	if(find((*temp).begin(),(*temp).end(),key)!=(*temp).end()){
        (*temp).erase(find((*temp).begin(),(*temp).end(),key));
  		cout << "Deleted Correctly." << endl;
  	}
  	else cout<< "Can't delete" << endl;
}
void bucket_delete(int key){
	int local_depth = dir[hash_function(key)].first;
	int bucket_no = hash_function(key)%((int)pow(2,local_depth));
	lazy_delete(key);
	if((*(dir[bucket_no].second)).size()<1){
		int mir_bucket_no = (1<<(local_depth-1))^bucket_no;
		printf("Empty Bucket %d\n",mir_bucket_no);
		if(dir[mir_bucket_no].first == dir[bucket_no].first && dir[bucket_no].first!= 1){
			int diff = pow(2,local_depth);
			for(int i = bucket_no;i<pow(2,global_depth);i+=diff){
				dir[i].first--;
				dir[i].second = dir[mir_bucket_no].second;
			}
			for(int i = mir_bucket_no;i<pow(2,global_depth);i+=diff)	dir[i].first--;
		}
	}
}
void directory_delete(int key)
{
	bucket_delete(key);
	while(global_depth>1){
		int i = 0,j = pow(2,global_depth-1);
		for(;j<pow(2,global_depth);i++,j++){
			if(dir[i].second!=dir[j].second)	break;
		}
		if(j==pow(2,global_depth)){
			dir.resize(pow(2,global_depth-1));
			global_depth--;
		}
		else	break;
	}
}
void insert(int key){
	int bucket_no = hash_function(key);
	vi* bucket_ptr= dir[bucket_no].second;
	if((*bucket_ptr).size()==BUCKET_SIZE){
		printf("Size exceeded\n");
		int local_depth = dir[bucket_no].first;	//Calculating the local depth
		int bucket_no1 = bucket_no%((int)pow(2,local_depth));
		if(local_depth<global_depth){
			printf("Hi I'm here %d %d\n",bucket_no1,local_depth);
			// Updating the overflowed and sibling parameters
			// Using an additional bucket for simplicity.
			bucket_split(bucket_no1,bucket_ptr,local_depth);	
			insert(key);
		}
		else{
			cout << "Don't miss me" << endl;
			//Do the Directory splitting
			double_directory();
			insert(key);
		}
		//Handle Split
	}
	else{
		(*bucket_ptr).push_back(key);
		printf("%d added\n",key);
	}
}

void bucket_split( int bucket_no , vi* bucket_ptr,int local_depth){
		int mir_bucket_no = pow(2,local_depth)+bucket_no;
		dir[mir_bucket_no].first++;
		dir[bucket_no].first++;
		dir[mir_bucket_no].second = add_new_bucket();
		dir[bucket_no].second = add_new_bucket();

		for(int i = 0 ; i < BUCKET_SIZE ; i++){
			int val = (*bucket_ptr)[i];
			int t = (val >> local_depth)%2;
			if(t==0)	(*dir[bucket_no].second).push_back(val);
			else	(*dir[mir_bucket_no].second).push_back(val);
		}
		int diff = pow(2,local_depth+1);
		for(int i = mir_bucket_no + diff;i<pow(2,global_depth);i+=diff){
			dir[i].first++;
			dir[i].second = dir[mir_bucket_no].second;
		}
		for(int i = bucket_no + diff;i<pow(2,global_depth);i+=diff){
			dir[i].first++;
			dir[i].second = dir[bucket_no].second;
		}
		//swap(bucket_ptr,dir[bucket_no].second);
		//delete (bucket_ptr);
}

vector<int>* add_new_bucket(){	
	return(new vector<int>);
}

int hash_function(int a){
	return a % (1 << global_depth);
}

void double_directory(){
	int dir_size = dir.size();
	for(int i = 0 ; i< dir_size ; i++){
		dir.push_back(make_pair(dir[i].first,dir[i].second));
	}
	global_depth++;
}

void status(){
	cout<<"Global Depth : "<<global_depth<<endl;
	for(int i=0;i<dir.size();i++)
	{
		cout<<"Bucket NO : "<<i<<" Local Depth : "<<dir[i].first<< " NO Of Ele : "<<(*dir[i].second).size()<<endl;
		for(int j=0;j<(*dir[i].second).size();j++)
			cout<<(*dir[i].second)[j]<<"  ";
		cout<<endl<<endl;
	}
}

bool search(int key){
	vi temp = *(dir[hash_function(key)].second);
	return(find(temp.begin(),temp.end(),key)!=temp.end());
}