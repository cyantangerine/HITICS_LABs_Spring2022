#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define IMGTYPE long
#define WIDTH 1920
#define HEIGHT 1080

static IMGTYPE image[HEIGHT][WIDTH];	

int main(){
	int len = WIDTH;
	clock_t time1,time2;
	int i=0,j=0,tmp;
	//IMGTYPE image[WIDTH];
	//srand((unsigned) time(NULL));
	FILE* f = fopen("IMAGE.64BMP","wb");
	time1 = clock();
	for(j=0;j<HEIGHT;j++){
		for(i=0;i<WIDTH;i+=4){
			tmp = j*WIDTH + i;
			image[j][i] = tmp;//(((IMGTYPE)rand())<<32)+(unsigned long long)rand();
			image[j][i+1] = tmp+1;//(((IMGTYPE)rand())<<32)+(unsigned long long)rand();
			image[j][i+2] = tmp+2;//(//((IMGTYPE)rand())<<32)+(unsigned long long)rand();
			image[j][i+3] = tmp+3;//(//((IMGTYPE)rand())<<32)+(unsigned long long)rand();
		}
	}
	fwrite(image,sizeof(IMGTYPE),HEIGHT*WIDTH,f);
	time2 = clock();
	fclose(f);
	FILE* flog = fopen("log.txt","a+");
	fprintf(flog,"WR_OPT\t START:%ld\t END:%ld\n",time1,time2);
    fclose(flog);
	flog = fopen("log_WROPT.txt","a+");
	fprintf(flog,"%ld\n",time2-time1);
    fclose(flog);
	return 0;
}
