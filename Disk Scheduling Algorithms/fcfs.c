#include <stdio.h>
#include <stdlib.h>
#define N 100
#define loop(i,n) for(i=0;i<n;++i)
#define inp(x) scanf("%d", &x)

int i,n;
int req[N];
int sum = 0;
int temp;
int main()
{
	system("clear");
	printf("Req Count : ");
	scanf("%d", &n);

	printf("Current track position : ");
	scanf("%d", &req[0]);

	printf("Enter the Reqs\n");
	for(i=1; i<=n; i++)
		inp(req[i]);
      
	printf("R/W Head movements\n");
	for(i=1; i<n+1; i++)
	{
        temp = abs(req[i] - req[i-1]);
		printf("%d\t ===> \t%d \t: \t%d\n", req[i-1], req[i], temp);
		sum += temp;
	}

	printf("\nR/W Total Head Movement : %d\n\n", sum);
}
