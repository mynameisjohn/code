#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>

#define N 4
#define all(V) V.begin(), V.end()
#define tr(V,it) for (iVecIt it = V.begin(); it != V.end(); it++)

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<int>::iterator iVecIt;

vvi W;
vi V;

void dfs(int i){
   if (!V[i]){
      V[i]=true;
      for_each(all(W[i]),dfs);
   }
}

bool bfs(){
   int start=0;
   V=vi(N,false);
   queue<int> Q;
   Q.push(start);
   V[start]=true;
   while (!Q.empty()){
      int i = Q.front();
      Q.pop();
      tr(W[i],it){//this traversal visits all of W[i]'s adjacent nodes
	 if (!V[*it]){
	    V[*it]=true;
	    Q.push(*it);
	 }
      }
   }
   return (find(all(V),0)==V.end());
}

bool check_connectivity_dfs(){
   int start=0;
   V=vi(N,false);
   dfs(start);
   return (find(all(V),0)==V.end());
}

int main(){
   W.resize(N);
   W[0]=vi(1); W[0][0]=1;//			   [1]   //connected graph W
   W[1]=vi(3); W[1][0]=0; W[1][1]=2; W[1][2]=3;//  //
   W[2]=vi(1); W[2][0]=1;//			  [2]
   W[3]=vi(1); W[3][0]=1;			 // \\
				        	[3]  [4]
   
   cout << check_connectivity_dfs() << endl; 
   cout << bfs() << endl; 
 
   return 1;
}
