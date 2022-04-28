#include <stdio.h> 

int main(){
	printf("uint\t%lu\n",sizeof(unsigned));
	printf("char\t%lu\n",sizeof(char));
	printf("short\t%lu\n",sizeof(short));
	printf("int\t%lu\n",sizeof(int));
	printf("long\t%lu\n",sizeof(long)); 	
    printf("longl\t%lu\n",sizeof(long long));
    printf("float\t%lu\n",sizeof(float));
	printf("double\t%lu\n",sizeof(double));
	printf("ldouble\t%lu\n",sizeof(long double));
	printf("pointer\t%lu\n",sizeof(void*));
	return 0;
} 
