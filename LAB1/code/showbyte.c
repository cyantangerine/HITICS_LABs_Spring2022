#include <stdio.h>
const int linecount = 16;
char line[100] = {0};
void print(int count){
	int i;
	for(i=0;i<count;i++){
 		if(line[i]=='\t') printf(" \\t ");
 		else if(line[i]=='\r') printf(" \\r ");
		else if(line[i]=='\n') printf(" \\n ");
 		else if((int)line[i]<0||line[i]>127){
 			printf(" .  ");	
		}else{
			printf(" %c  ",line[i]);
		}
	}
	printf("\n");
	for(i=0;i<count;i++){
		if((int)line[i]<0 ||line[i]>127){
			unsigned u = (unsigned)line[i];
			u=u & 0X000000FF; 
 			printf(" %02x ",u);	
		}else{
			printf(" %02x ",line[i]);
		}
		line[i] = 0;
	}
	printf("\n");
}

int main(){
	FILE* f = fopen("./hello.c","r");
	
	char c = fgetc(f);
	int i = 0,count = 0;
 	while(c != EOF && c!=255){
 		line[count++] = c;
 		if(count==linecount){
 			print(count);
	 		count=0;
		 }
 		c = fgetc(f);
	}
	print(count);
	fclose(f);
	
	return 0;
} 
