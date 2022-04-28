#include <stdio.h> 
#define LEN 0

int sum(int a[], unsigned len){
	int i,sum=0; 
	for(i=0;i<=len-1;i++) sum+=a[i];
	return sum;
}

int main(){
	int a[LEN]; //= {1,2,3,4,5};
	printf("%d",sum(a,LEN));
	return 0;
} 
