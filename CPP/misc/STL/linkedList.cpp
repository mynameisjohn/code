#include <iostream>
#include <list>

using namespace std;

int main(){
   list<int> iList;

   for (int i=0;i<10;i++) iList.push_back(i);

   iList.pop_back();
   iList.pop_front();

   list<int>::iterator iListIter;
   iListIter=iList.begin();//-4;
   iListIter++;iListIter++;
   iList.insert(iListIter,69);

   for (iListIter=iList.begin();iListIter!=iList.end();iListIter++)
      cout << *iListIter << endl;

   iList.sort();

   for (iListIter=iList.begin();iListIter!=iList.end();iListIter++)
      cout << *iListIter << endl;

   return 0; 
}
