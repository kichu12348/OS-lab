#include<stdio.h>
#include<stdlib.h>


int bubbleSort(int arr[],int n,int head){
   for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            if(arr[j]>arr[j+1]){
                int temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
        }
    }
    for(int i=0;i<n;i++)
        if(arr[i]==head) 
                return i;

    return -1;
}

void scan(
    int pos[],
    int head,
    int n,
    int dir,
    int hIdx,
    int ts
){
    int total_seek_time=0;

    printf("head Movements: %d ",head);
    if(dir){
        for(int i=hIdx+1;i<n;i++){
            printf("-> %d",pos[i]);
            total_seek_time+=abs(head-pos[i]);
            head=pos[i];
        }
        printf("-> %d",ts);
        total_seek_time+=abs(head-ts);
        head=ts;
        for(int i=hIdx-1;i>=0;i--){
            printf("-> %d",pos[i]);
            total_seek_time+=abs(head-pos[i]);
            head=pos[i];
        }
    }
    else{
        for(int i=hIdx-1;i>=0;i--){
            printf("-> %d",pos[i]);
            total_seek_time+=abs(head-pos[i]);
            head=pos[i];
        }
        printf("-> %d",0);
        total_seek_time+=abs(head-0);
        head=0;
        for(int i=hIdx+1;i<n;i++){
            printf("-> %d",pos[i]);
            total_seek_time+=abs(head-pos[i]);
            head=pos[i];
        }
    }
    printf("\ntotal head movements: %d\n",total_seek_time);
    printf("Average head Movements: %f\n",(float)total_seek_time/n);
    
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
    int ts;
    printf("Enter the total size of disk: ");
    scanf("%d",&ts);
    
    int hIdx=bubbleSort(pos,n,head);
    
    int dir;
    printf("Enter the direction (1 for up, 0 for down): ");
    scanf("%d",&dir);

    scan(pos,head,n,dir,hIdx,ts);
}
