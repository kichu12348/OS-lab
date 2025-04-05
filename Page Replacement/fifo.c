#include <stdio.h>

void algo(int p[], int n, int f)
{
    int frames[f];
    int faults = 0,
        hits = 0,
        front = 0;

    for(int i=0;i<f;i++) frames[i]=-1;

    for(int j=0;j<n;j++){
        int found=0;
        for(int i=0;i<f;i++){
            if(frames[i]==p[j]){
                found=1;
                hits++;
                break;
            }
        }
        if(found==0){
            frames[front]=p[j];
            front=(front+1)%f;
            faults++;
        }
    }

    printf("Total number of hits: %d and faults: %d",hits,faults);
}


void main()
{
    int n, f;
    printf("Enter the number of pages: ");
    scanf("%d", &n);
    printf("Enter the number of frames: ");
    scanf("%d", &f);
    int p[n];
    printf("Enter the pages: ");
    for(int i=0;i<n;i++){
        scanf("%d", &p[i]);
    }
    algo(p, n, f);
}