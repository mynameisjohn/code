#include <stdio.h>
#include <omp.h>

int main(){
	printf("%d\n",omp_get_max_threads());
	int i,a=0;
	//#pragma omp parallel for private(i) reduction (+:a)
	for (i=0;i<10000;i++)
		a+=i;
	printf("%d\n",a);
	return 0;
}
