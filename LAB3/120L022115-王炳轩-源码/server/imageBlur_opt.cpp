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
        line[last][i] = img[0][i] = img[1][i];
        img[HEIGHT+1][i]= img[HEIGHT][i];
        tmp = i+1;
        line[last][tmp] = img[0][tmp] = img[1][tmp];
        img[HEIGHT+1][tmp]= img[HEIGHT][tmp];
		tmp = i+2;
		line[last][tmp] = img[0][tmp] = img[1][tmp];
        img[HEIGHT+1][tmp]= img[HEIGHT][tmp];
        tmp = i+3;
		line[last][tmp] = img[0][tmp] = img[1][tmp];
        img[HEIGHT+1][tmp]= img[HEIGHT][tmp];
	}
	
 	int i1,i2,j1,j2,j3;
    for(int i=1;i<HEIGHT+1;i++){
        for(int j=1;j<WIDTH+1;j+=4){
            i1 = i-1;i2 = i+1;j1 = j+1;j2 = j+2;j3=j+3;
			line[curr][j] = ((img[i][j-1]+img[i][j1])+(img[i1][j]+img[i2][j]))>>2;
            line[curr][j1] = ((img[i][j]+img[i][j2])+(img[i1][j1]+img[i2][j1]))>>2;
            line[curr][j2] = ((img[i][j1]+img[i][j3])+(img[i1][j2]+img[i2][j2]))>>2;
            line[curr][j3] = ((img[i][j2]+img[i][j+4])+(img[i1][j3]+img[i2][j3]))>>2;			
			img[i1][j] = line[last][j];
			img[i1][j1] = line[last][j1];
			img[i1][j2] = line[last][j2];
			img[i1][j3] = line[last][j3];
        }
        curr = !curr;
        last = !last;
	}
	f = fopen("IMAGE_Blur.64BMP","wb");
	for(int i=1;i<HEIGHT+1;i+=4){
	    fwrite(&img[i][1],sizeof(IMGTYPE),WIDTH,f);
	    fwrite(&img[i+1][1],sizeof(IMGTYPE),WIDTH,f);
	    fwrite(&img[i+2][1],sizeof(IMGTYPE),WIDTH,f);
	    fwrite(&img[i+3][1],sizeof(IMGTYPE),WIDTH,f);
	}
	time2 = clock();
	fclose(f);
	FILE* flog = fopen("log.txt","a+");
	fprintf(flog,"BL_OPT\t START:%ld\t END:%ld\n",time1,time2);
    fclose(flog);
	flog = fopen("log_BLOPT.txt","a+");
	fprintf(flog,"%ld\n",time2-time1);
    fclose(flog);
	return 0;
}
