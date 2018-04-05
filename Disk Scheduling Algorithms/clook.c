#include <stdio.h>
#include <stdlib.h>
#define loop(i,n) for(i=0;i<n;++i)
#define inp(x) scanf("%d", &x)

#define N 100


int i,j,temp;

int n, trackCount, dir;
int req[N];
int sum, pos;

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
	int n, trackCount, dir;
	int req[N];

	printf("Enter number of tracks : ");
	inp(trackCount);

	printf("Enter initial head movement (0: CW, 1: CCW) : ");
	inp(dir);

	printf("Enter number of reqs : ");
	inp(n);

	printf("Enter current track position : ");
	inp(req[0]);

	printf("\nEnter the reqs\n");
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
	if(dir == 0)
	{
		for(i=pos-1; i>=0; i--)
			printf("%d ==> %d\n", req[i+1], req[i]);

		if(pos<n-1)
			printf("%d ==> %d\n", req[0], req[n-1]);
		for(i=n-2; i>pos; i--)
			printf("%d ==> %d\n", req[i+1], req[i]);

		sum = req[pos] - req[0];
		if(pos<n-1)
			sum += req[n-1] - req[pos+1];
	}
	else
	{
		for(i=pos+1; i<n; i++)
			printf("%d ==> %d\n", req[i-1], req[i]);

		if(pos>0)
			printf("%d ==> %d\n", req[n-1], req[0]);
		for(i=1; i<pos; i++)
			printf("%d ==> %d\n", req[i-1], req[i]);

		sum = req[n-1] - req[pos];
		if(pos>0)
			sum += req[pos-1] - req[0];
	}
	printf("Total R/W Head Movement : %d\n\n", sum);
}
