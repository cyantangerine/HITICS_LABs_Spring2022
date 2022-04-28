#include <stdio.h>
typedef struct Table TB;
struct Table {
	int val;
	int id;
	TB *next;
};
int explode(){
	printf("bomb\n");
	exit(8);
	return 0;
}

int main(){
	TB T[6];
	int num[] = {0x3cb,0x25a,0x1c6,0x2ec,0x3b0,0x154};
	int i=0,j=0;
	for(i=0;i<6;i++){
		T[i].val = num[i];
		T[i].id = i;
		if(i<5)	T[i].next = &T[i+1];
		else T[i].next = NULL;
	}
	int a[6]={0};
	for(i=0;i<6;i++){
		scanf("%d",&a[i]);	
	}
	for(i=0;i<6;i++){
		if(a[i]>6) explode();
		for(j=i+1;j<6;j++){
		    if(a[i]==a[j]) explode(); 
	    }
	}
	TB *t,*nt[6]={0},*t1;

	for(i=0;i<6;i++){
		t = &T[0];
		for(j=0;j<a[i]-1;j++) t=t->next;
		nt[i] = t;
	}
	for(i=0;i<5;i++){
		t = nt[i];
		t1 = t->next;
		t->next = nt[i+1];
	}
	t = nt[5];
	t->next = NULL;
	t = nt[0];
	for(i=0;i<5;i++){
		if((t->val)<(t->next->val)) explode();
		t = t->next;
	}
	return 0;
}
