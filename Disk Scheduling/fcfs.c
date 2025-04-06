#include<stdio.h>
#include<stdlib.h>

void diskMove(int pos[],int head, int n){
    int seekTime=0;

    printf("head Movements: %d ",head);
    for(int i=0;i<n;i++) {
        printf("-> %d",pos[i]);
        seekTime+=abs(head-pos[i]);
        head=pos[i];
    }
    printf("\n");

    printf("total seek Time: %d\n",seekTime);
}


void main(){
    int n;
    printf("Enter the number of requests: ");
    scanf("%d",&n);
    int pos[n];
    printf("Enter the requests: ");
    for(int i=0;i<n;i++) scanf("%d",&pos[i]);
    int head;
    printf("Enter the initial head position: ");
    scanf("%d",&head);
    diskMove(pos,head,n);
}