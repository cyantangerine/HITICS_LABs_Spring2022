#include <stdio.h> 

int main(){
	float f;
	
	for(;;){
		printf("Input a float:");
		scanf("%f",&f);
		printf("This float is %f\n",f);
		if(f==0) break;
	}
	
	return 0;
} 
