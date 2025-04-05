#include<stdio.h>


/*
Banker's Algorithm:
1. Let Work and Finish be vectors of length 'm' and 'n' respectively.
    Initialize: Work = Available
    Finish[i] = false for i=1,2,3,...,n

2. Find an i such that both:
    a) Finish[i] = false
    b) Need[i] <= Work
    If no such i exists, go to step 4

3. Work = Work + Allocation[i]
    Finish[i] = true
    Go to step 2

4. If Finish[i] = true for all i,
    then system is in safe state
*/

void banker(
    int avail[],
    int p[][10],
    int max[][10],
    int n,
    int m
){
    int need[10][10];

    int work[m];
    for(int i=0;i<m;i++) work[i]=avail[i];
    //calculate need
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            need[i][j]=max[i][j]-p[i][j];

    
    //safe sequence
    int seqence[n];
    int count=0;
    int finish[n];
    for(int i = 0; i < n; i++) finish[i] = 0;

    while(count<n){
        int found=0;
        for(int i=0;i<n;i++){
            if(!finish[i]){
                int j;
                for(j=0;j<m;j++)
                    if(need[i][j]>work[j]) break;
                
                if(j==m){
                    for(int k=0;k<m;k++) work[k]+=p[i][k];
                    seqence[count++]=i;
                    finish[i]=1;
                    found=1;
                }
            }
        }

        if(!found){
            printf("System noot safeeee\n");
            return;
        }
    }

    printf("system is safe\nSafe Sequnce: ");
    for(int i=0;i<n;i++){
        printf("P%d ",seqence[i]);
    }
}

void main(){
    int n,m;
    printf("Enter the number of processes: ");
    scanf("%d",&n);
    printf("Enter the number of resources: ");
    scanf("%d",&m);

    int avail[m];
    printf("Enter the available resources: ");
    for(int i=0;i<m;i++) scanf("%d",&avail[i]);

    int p[n][10],r[n][10],max[n][10];
    printf("Enter the allocation matrix:\n");
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            scanf("%d",&p[i][j]);
    
    printf("Enter the max matrix:\n");
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            scanf("%d",&max[i][j]);


    banker(avail,p,max,n,m);
}