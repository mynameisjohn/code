#include <vector>
#include <list>
#include <iostream>

#define N 4

using namespace std;

typedef struct bach{
   int id, next;
   vector<int> prefs;
} bach;

int main(){
   list<bach *> freeMen;
   bach men[N], women[N];

   //this notation is somewhat confusing
   //here man 0 prefers, in order,
   //woman 0, woman 2, woman 1, woman 3
   //prefs values indicate rank
   men[0].id=0;               women[0].id=0;
   men[0].prefs.push_back(0); women[0].prefs.push_back(2);
   men[0].prefs.push_back(2); women[0].prefs.push_back(1);
   men[0].prefs.push_back(1); women[0].prefs.push_back(3);
   men[0].prefs.push_back(3); women[0].prefs.push_back(0);

   men[1].id=1;               women[1].id=1;
   men[1].prefs.push_back(2); women[1].prefs.push_back(3);
   men[1].prefs.push_back(1); women[1].prefs.push_back(2);
   men[1].prefs.push_back(3); women[1].prefs.push_back(1);
   men[1].prefs.push_back(0); women[1].prefs.push_back(0);

   men[2].id=2;               women[2].id=2;
   men[2].prefs.push_back(3); women[2].prefs.push_back(0);
   men[2].prefs.push_back(1); women[2].prefs.push_back(3);
   men[2].prefs.push_back(0); women[2].prefs.push_back(1);
   men[2].prefs.push_back(2); women[2].prefs.push_back(2);

   men[3].id=3;               women[3].id=3;
   men[3].prefs.push_back(2); women[3].prefs.push_back(2);
   men[3].prefs.push_back(1); women[3].prefs.push_back(0);
   men[3].prefs.push_back(0); women[3].prefs.push_back(1);
   men[3].prefs.push_back(3); women[3].prefs.push_back(3);

   for (int i=0;i<N;i++){
      freeMen.push_front(&men[i]);
      men[i].next=0;
      women[i].next=-1;
   }

   //my take on the gale shapley algorithm
   //maybe went overboard with the pointers (and metaphors)

   //while there are still single guys
   while (!freeMen.empty()){  
      //take the next single guy 
      bach * h = freeMen.front();
      //take his favorite gal
      bach * s = &women[(h->prefs[h->next++])];
      if (s->next>=0){//if she's taken
         //see who she's with
         bach * g = &men[s->next];
         //if she likes our single man more
         if (s->prefs[g->id]<s->prefs[h->id]){
	    //she dumps the old guy for him
	    s->next=h->id;
	    freeMen.pop_front();
	    //and the old guy is single
	    freeMen.push_back(g);
	 }
      }
      else{//if she isn't taken
	 s->next=h->id;
	 //they get together, and he's no longer single
	 freeMen.pop_front();
      }
   }

   for (int i=0;i<N;i++){
      cout << "woman " << i << " is with man " << women[i].next << endl;
      if (men[women[i].next].prefs[0]==women[i].id)
	 cout << "Man " << women[i].next << " got his first choice!" << endl;
   }

   return 1;
}
