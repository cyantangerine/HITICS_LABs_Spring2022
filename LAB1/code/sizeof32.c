#include <stdio.h> 

int main(){
	printf("uint\t%u\n",sizeof(unsigned));
	printf("char\t%u\n",sizeof(char));
	printf("short\t%u\n",sizeof(short));
	printf("int\t%u\n",sizeof(int));
	printf("long\t%u\n",sizeof(long)); 	
    printf("longl\t%u\n",sizeof(long long));
    printf("float\t%u\n",sizeof(float));
	printf("double\t%u\n",sizeof(double));
	printf("ldouble\t%u\n",sizeof(long double));
	printf("pointer\t%u\n",sizeof(void*));
	return 0;
} 
