#include <stdio.h>
#include <stdlib.h>
#define N 100
#define loop(i,n) for(i=0;i<n;++i)
#define inp(x) scanf("%d", &x)

int sum, pos, temp;
int n, trackCount, lr;
int req[N];
int i,j;

void sort(int a[], int n)
{
	for(i=0; i<n-1; i++)
		for(j=i+1; j<n; j++)
			if(a[i] > a[j]){
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
}
int main()
{
	system("clear");
	printf("Track Count : ");	inp(trackCount);
	printf("Start Head movement (0: left, 1: right) : ");   inp(lr);
	printf("Req Count : ");     inp(n);
	printf("Current track position : ");	inp(req[0]);

	printf("Enter the reqs\n");	
    for(i=1; i<=n; i++)		
        inp(req[i]);

	n++;
	int firstreq = req[0];
	sort(req, n);

	for(i=0; i<n; i++)
		if(req[i] == firstreq){
			pos = i;
			break;
		}

	printf("R/W Head movement\n");
	if(lr == 0){
        

		for(i=pos-1; i>=0; i--)
			printf("%d ==> %d\n", req[i+1], req[i]);
		if(req[0] != 0);
			printf("%d ==> 0\n", req[0]);
		
		if(pos<n-1)
			printf("0 ==> %d\n", req[pos+1]);
		for(i=pos+2; i<n; i++)
			printf("%d ==> %d\n", req[i-1], req[i]);
		if(pos == n-1)
			printf("0 ==> %d\n", trackCount);
		else if(req[0] != 0)
			printf("%d ==> %d\n", req[n-1], trackCount);

		sum = trackCount + firstreq -1;
	}
	else
	{
		
		for(i=pos+1; i<n; i++)
			printf("%d -> %d\n", req[i-1], req[i]);
		if(req[n-1] != trackCount);
			printf("%d -> %d\n", req[n-1], trackCount -1);
		
		if(pos>0)
			printf("%d -> %d\n", trackCount -1, req[pos-1]);
		for(i=pos-2; i>=0; i--)
			printf("%d -> %d\n", req[i+1], req[i]);
		if(pos == 0)
			printf("%d -> 0\n", trackCount);
		else if(req[0] != 0)
			printf("%d -> 0\n", req[0]);

		sum = 2*trackCount -2 -firstreq;
	}
	printf("Total R/W Head Movement : %d\n\n", sum);
}
