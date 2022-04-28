#include <stdio.h> 
double next(int count,double f1,double f2){
	printf("%3d %.0lf %.0lf %.8lf\n",count,f1,f2,(double)f1/f2);
	if(count<100)next(count+1,f2,f2+f1);
}

int main(){
	next(0,1,1);
	return 0;
} 
