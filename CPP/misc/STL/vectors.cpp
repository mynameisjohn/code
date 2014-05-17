#include <iostream>
#include <vector>

using namespace std;

int main(){
   vector <int> example;

   example.push_back(3);
   example.push_back(10);
   example.push_back(33);

   for (int i=0;i<example.size();i++)
      cout << example[i] <<", ";
   if (!example.empty()) example.clear();

   vector<int> iVec;
   iVec.push_back(10);
   example.push_back(10);
   if (iVec==example) example.push_back(20);

   for (int i=0;i<example.size();i++)
      cout << example[i] <<", ";

   return 0;
}
