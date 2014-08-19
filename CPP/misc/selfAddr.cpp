#include "stdio.h"

class noOne{
	int x;
	public: 
		void doNothing(){
			printf("%d\n",(unsigned int)((&(*this))));
		}
};

int main(){
	noOne jones;
	jones.doNothing();

	return 1;
}
