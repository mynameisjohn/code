#include <iostream>
#include <vector>

using namespace std;

int main(){
   vector <int> example;
/*
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
*/
	int x = 3;
	example.push_back(x);
	cout << example[0] << endl;

	std::vector<int>::iterator it;
	it=example.begin();
	int * iPtr = &example[0];

	int * y = &(example[0]);
	*y=9;

	cout << &*iPtr << ", " << &*it << endl;
	cout << example.size() << endl;
	example.emplace_back();
	cout << example.size() << endl;
	
   return 0;
}
