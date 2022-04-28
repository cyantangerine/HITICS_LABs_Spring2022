#include <stdio.h>
#include <time.h>

#define IMGTYPE long 
#define WIDTH 1920
#define HEIGHT 1080

static IMGTYPE img[HEIGHT+2][WIDTH+2],line[2][WIDTH+2];

int main(){
	clock_t time1,time2;
	IMGTYPE last=0,curr=1;
	FILE* f = fopen("IMAGE.64BMP","rb");
	time1 = clock();
	for(int i=1;i<HEIGHT+1;i++){
	    fread(&img[i][1],sizeof(IMGTYPE),WIDTH,f);
	}
	fclose(f);
	for(int i=0;i<WIDTH+2;i++){
        line[last][i] = img[0][i] = img[1][i];
        img[HEIGHT+1][i]= img[HEIGHT][i];
	}

	for(int i=0;i<HEIGHT+2;i++){
        img[i][0] = img[i][1];
        img[i][WIDTH+1]= img[i][WIDTH];
	}

    for(int i=1;i<HEIGHT+1;i++){
        for(int j=1;j<WIDTH+1;j++){
            line[curr][j] = (img[i][j-1]+img[i][j+1]+img[i-1][j]+img[i+1][j])/4;
        }
        for(int j=1;j<WIDTH+1;j++){
            img[i-1][j] = line[last][j];
            line[last][j] = line[curr][j];
        }

	}
	f = fopen("IMAGE_Blur.64BMP","wb");
	for(int i=1;i<HEIGHT+1;i++){
        //for(int j=1;j<HEIGHT+1;j++){
            fwrite(&img[i][1],sizeof(IMGTYPE),WIDTH,f);
        //}
	}
	time2 = clock();
	fclose(f);
	FILE* flog = fopen("log.txt","a+");
	fprintf(flog,"BLUR \t START:%ld\t END:%ld\n",time1,time2);
    fclose(flog);
	flog = fopen("log_BL.txt","a+");
	fprintf(flog,"%ld\n",time2-time1);
    fclose(flog);
	return 0;
}
