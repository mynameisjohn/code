#include <iostream>
#include <string.h>
#include <map>

using namespace std;

int main(){
   map <string, char> grade_list;

   grade_list["Carjulio"]='F';
   grade_list["FIONA"]='A';
   grade_list["john"]='B';
   grade_list["FIONA"]='B';

   cout << grade_list["FIONA"] << endl;

   grade_list.erase("Carjulio");

   cout << "class got " << grade_list.size() << " dudes" << endl;

   if (grade_list.find("Tim") == grade_list.end())
      cout << "ain't got no tim" << endl;

   map<string, char>::iterator gIter;

   cout << grade_list.begin()->first << ", ";
   cout << grade_list.begin()->second << endl;

   return 0;
}
