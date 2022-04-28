#include <stdio.h>
#include <time.h>
#include <pthread.h>

#define THREADS 2
#define IMGTYPE long 
#define WIDTH 1920
#define HEIGHT 1080
#define HEIGHT_HALF 540

static IMGTYPE img[HEIGHT+2][WIDTH+2],line[2][2][WIDTH+2];
static int a1=1,a2=0;
void* calculate(void *arg){
	int id;
	id = *(int*)arg;
	int last=0,curr=1;
	int i1,i2,j1,j2,j3,WIDTH1 = WIDTH+1;
    int i= id==1?1:HEIGHT_HALF+1;
    int max = id==1?HEIGHT_HALF+1:HEIGHT+1;
	for(;i<max;i++){
        for(int j=1;j<WIDTH;j+=4){
            i1 = i-1;i2 = i+1;j1 = j+1;j2 = j+2;j3=j+3;
			line[id][curr][j] = (img[i][j-1]+img[i][j1]+img[i1][j]+img[i2][j])>>2;
            line[id][curr][j1] = (img[i][j]+img[i][j2]+img[i1][j1]+img[i2][j1])>>2;
            line[id][curr][j2] = (img[i][j1]+img[i][j3]+img[i1][j2]+img[i2][j2])>>2;
            line[id][curr][j3] = (img[i][j2]+img[i][j+4]+img[i1][j3]+img[i2][j3])>>2;			
			img[i1][j] = line[id][last][j];
			img[i1][j1] = line[id][last][j1];
			img[i1][j2] = line[id][last][j2];
			img[i1][j3] = line[id][last][j3];
        }
        curr = !curr;
        last = !last;
	}
	
	
}

int main(){
	clock_t time1,time2;
	int last=0,curr=1;
	FILE* f = fopen(".\\IMAGE.64BMP","rb");
	time1 = clock();
	int tmp; 
	for(int i=1;i<HEIGHT+1;i+=4){
	    fread(&img[i][1],sizeof(IMGTYPE),WIDTH,f);
	    fread(&img[i+1][1],sizeof(IMGTYPE),WIDTH,f);
	    fread(&img[i+2][1],sizeof(IMGTYPE),WIDTH,f);
	    fread(&img[i+3][1],sizeof(IMGTYPE),WIDTH,f);
	    img[i][0] = img[i][1];
        img[i][WIDTH+1]= img[i][WIDTH];
        tmp = i+1;
		img[tmp][0] = img[tmp][1];
        img[tmp][WIDTH+1]= img[tmp][WIDTH];
        tmp = i+2;
		img[tmp][0] = img[tmp][1];
        img[tmp][WIDTH+1]= img[tmp][WIDTH];
        tmp = i+3;
		img[tmp][0] = img[tmp][1];
        img[tmp][WIDTH+1]= img[tmp][WIDTH];
	}
	fclose(f);
	for(int i=0;i<WIDTH+2;i+=4){
        line[1][last][i] = line[0][last][i] = img[0][i] = img[1][i];
        img[HEIGHT+1][i]= img[HEIGHT][i];
        tmp = i+1;
        line[1][last][tmp]= line[0][last][tmp] = img[0][tmp] = img[1][tmp];
        img[HEIGHT+1][tmp]= img[HEIGHT][tmp];
		tmp = i+2;
		line[1][last][tmp]= line[0][last][tmp] = img[0][tmp] = img[1][tmp];
        img[HEIGHT+1][tmp]= img[HEIGHT][tmp];
        tmp = i+3;
		line[1][last][tmp]= line[0][last][tmp] = img[0][tmp] = img[1][tmp];
        img[HEIGHT+1][tmp]= img[HEIGHT][tmp];
	}
	
	pthread_t th1,th2;

	if(pthread_create(&th1,NULL,calculate,(void*)&a1)!=0) exit(1);
	if(pthread_create(&th1,NULL,calculate,(void*)&a2)!=0) exit(2);
	pthread_join(th1,NULL);
	pthread_join(th2,NULL);
	
	
 	
	f = fopen(".\\IMAGE_Blur.64BMP","wb");
	for(int i=1;i<HEIGHT+1;i+=4){
	    fwrite(&img[i][1],sizeof(IMGTYPE),WIDTH,f);
	    fwrite(&img[i+1][1],sizeof(IMGTYPE),WIDTH,f);
	    fwrite(&img[i+2][1],sizeof(IMGTYPE),WIDTH,f);
	    fwrite(&img[i+3][1],sizeof(IMGTYPE),WIDTH,f);
	}
	time2 = clock();
	fclose(f);
	FILE* flog = fopen(".\\log.txt","a+");
	fprintf(flog,"BL_OPT\t START:%lld\t END:%lld\n",time1,time2);
    fclose(flog);
	flog = fopen(".\\log_BLOPT.txt","a+");
	fprintf(flog,"%lld\n",time2-time1);
    fclose(flog);
	return 0;
}
