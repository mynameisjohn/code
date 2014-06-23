int testFunc(){
	int x = 43;
	int y = 29;

	int * a = new int[30];

	delete[] a;

	return 32;
}

int main(){
	int x = 4;
	int y = 2;
	int z = testFunc();
	return 1;
}
