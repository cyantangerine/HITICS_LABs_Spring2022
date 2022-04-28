#include <stdio.h> 

int main(){
	double f1=1,f2=1,tmp;
	int i=0;
	for(i = 1;i<101;i++){
		printf("%3d %.0lf %.0lf %.8lf\n",i,f1,f2,f1/f2);
		tmp = f1+f2;
		f1 = f2;
		f2 = tmp;
	}
	
	return 0;
} 
