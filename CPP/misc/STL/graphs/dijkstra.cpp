#include <queue>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

#define N 4

#define all(V) V.begin(), V.end()
#define tr(V,it) for (iVecIt it = V.begin(); it != V.end(); it++)

typedef vector<int> vi;

typedef vector<vi> vvi;
typedef vector<pair<int,int> >::iterator iVecIt;

typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<vii> vvii;

int main(){
   vvii G;
   G.resize(N);
   G[0]=vii(2);
   G[0][0]=ii(1,10); G[0][1]=ii(2,1);
   G[1]=vii(2);
   G[1][0]=ii(0,10); G[1][1]=ii(2,10);
   G[2]=vii(3);
   G[2][0]=ii(0,1); G[2][1]=ii(1,10); G[2][2]=ii(3,1);
   G[3]=vii(1);
   G[3][0]=ii(2,1);


   vi D(N,987654321);
   priority_queue<ii,vector<ii>,greater<ii> > Q;

   D[0]=0;
   Q.push(ii(0,0));

   while (!Q.empty()){
      ii top = Q.top();
      Q.pop();

      int v = top.second, d=top.first;

      if (d<=D[v]){
	 tr(G[v],it){
	    int v2 = it->first, cost = it->second;
	    if (D[v2]>D[v]+cost){
	       D[v2]=D[v]+cost;
	       Q.push(ii(D[v2],v2));
	    }
	 }
      }
   }

   return 1;
}
