#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define loop(i,n) for(i=0;i<n;++i)
#define inp(x) scanf("%d", &x)
#define INF 1e9
// #define DEBUG true
#define DEBUG false


void println(){
    printf("==========================================================================================\n");
}
//====================================================================
/*
CPU => Logical Address [Page No.|Page Offset]

Page No. => Refers Page Table => Frame No.

[Frame No. | Page Offset] => Physical Address
*/

bool check(int pageTable[], int siz, int maxValue, int j)
{
	int i,k;	
	// for(int i=0; i<siz; i++)
	// 	if(pageTable[i] < -1 || pageTable[i]>=maxValue)
	// 		return false;

	if(pageTable[j] < -1 || pageTable[j]>=maxValue)
			return false;
	//Duplicates
	loop(i,siz)
		if(pageTable[i] != -1){
			for(k=i+1; k<siz; k++)
				if(pageTable[k] == pageTable[i])
					return false;
		}

	return true;
}

int main(){
	system("clear");
	int pageSize, mmSize, va, pa, vaSize, i, c, pn;
	println();
	printf("Page Table Address Conversion\n");
	println();

	printf("Enter Sizes in bits \n");

	printf("Main Memory : ");
	inp(mmSize);

	printf("Page : ");
	inp(pageSize);

	printf("Virtual Address : ");
	inp(vaSize);
	
	int pageTableCount = vaSize/pageSize;
	int frameCount = mmSize/pageSize;
	int pageTable[pageTableCount];

	println();
	printf("Enter Page Table (-1 if does not exist) \n");
	loop(i, pageTableCount){
		printf("Page %d | Frame : ", i);
		inp(pageTable[i]);		
		while(!check(pageTable, i+1, frameCount, i)){
			printf("Invalid Input.\n");
			printf("Page %d | Frame : ", i);
			inp(pageTable[i]);
		}
	}

	while(true){
		println();
		printf("Enter Virtual Address (Logical Address) : ");
		inp(va);
		pn = va/pageSize;
		if(pn >= pageTableCount){
			printf("Invalid Address\n");
		}
		else if(pageTable[pn] == -1)
			printf("Page Fault\n");
		else{
			pa = va % pageSize + pageTable[pn]*pageSize;			
			printf("Physical Address : %d\n", pa);
		}
		printf("Enter 0 to exit | Others to continue : ");
		inp(c);
		if(c==0)
			return 0;

	}
	return 0;
}
/*
 500  100  1000
-1 0 3 1 -1 4 -1 -1 2  -1
 1002
 
 Invalid Address
*/
