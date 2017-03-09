#include <bits/stdc++.h>

using namespace std;
typedef vector<int> vi;
int global_depth = 1;
int BUCKET_SIZE = 2;

vector<int>* add_new_bucket();
int hash_function(int a);
void insert(int key);
void double_directory();
void bucket_split( int bucket_no , vi* bucket_ptr,int );
void status();
bool search(int key);
void lazy_delete(int );
void bucket_delete(int key);
void directory_delete(int key);