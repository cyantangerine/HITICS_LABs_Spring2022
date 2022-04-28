#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define IMGTYPE long
#define WIDTH 1920
#define HEIGHT 1080

int main(){
	clock_t time1,time2;
	int len = WIDTH;
	int i=0,j=0;
	IMGTYPE image[WIDTH];
	srand((unsigned) time(NULL));
	FILE* f = fopen(".\\IMAGE.64BMP","wb");
	time1 = clock();
	for(j=0;j<HEIGHT;j++){
		for(i=0;i<WIDTH;i++){
			image[i] = WIDTH*j+i;//(IMGTYPE)rand();//(((IMGTYPE)rand())<<32)+ 
		}
		fwrite(image,sizeof(IMGTYPE),WIDTH,f);
	}
	time2 = clock();
	fclose(f);
	FILE* flog = fopen(".\\log.txt","a+");
	fprintf(flog,"WRITE\t START:%lld\t END:%lld\n",time1,time2);
    fclose(flog);
	flog = fopen(".\\log_WR.txt","a+");
	fprintf(flog,"%lld\n",time2-time1);
    fclose(flog);
	return 0;
} 
