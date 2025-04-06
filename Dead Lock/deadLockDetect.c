#include<stdio.h>



/*

*/

void detection(
    int avail[],
    int p[][10],
    int req[][10],
    int n,
    int m
){
    int work[m];
    for(int i=0;i<m;i++) work[i]=avail[i];
    
    int count=0;
    int finish[n];
    for(int i=0;i<n;i++) finish[i]=0;

    while(count <n){
        int found=0;
        for(int i=0;i<n;i++){
            int j;
            for(j=0;j<m;j++) 
                if(req[i][j]>work[j]) break;

            if(j==m){
                for(int k=0;k<m;k++) work[k]+=p[i][k];
                finish[i]=1;
                found=1;
            }
        }

        if(!found) return;
    }

    int deadlock=0;
    printf("Processes in deadlock: ");
    for(int i=0;i<n;i++){
        if(!finish[i]){
            deadlock=1;
            printf("P%d ",i);
        }
    }
    printf("\n");
    if(deadlock){
        printf("System is not safe deadlock detected\n");
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

    int p[n][10],req[n][10];
    printf("Enter the allocation matrix:\n");
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            scanf("%d",&p[i][j]);

    printf("Enter the request matrix:\n");
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            scanf("%d",&req[i][j]);

    detection(avail,p,req,n,m);
}