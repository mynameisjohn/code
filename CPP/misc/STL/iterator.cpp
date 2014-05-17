#include <iostream>
#include <vector>
using namespace std;

int main(){
   vector<int> iVec;
   for (int i=0;i<10;i++) iVec.push_back(i);

   for (int i=0;i<iVec.size();i++) cout <<iVec[i] << ", ";
   cout << endl;
   
   vector<int>::iterator iVecIter;

   for (iVecIter = iVec.begin(); iVecIter != iVec.end(); iVecIter++)
      cout << *iVecIter <<" ";
   cout << endl;
   
   iVec.erase(iVec.begin()+2,iVec.end()-3);

   for (iVecIter = iVec.begin(); iVecIter != iVec.end(); iVecIter++)
      cout << *iVecIter <<" ";
   cout << endl;

   return 1;
}
