#include <stdio.h>

void algo(int p[], int n, int f)
{
    int frames[f];
    int faults = 0,
        hits = 0,
        front = 0;

    for(int i=0;i<f;i++) frames[i]=-1;

    for(int j=0;j<n;j++){
        int found=-1;
        for(int i=0;i<f;i++){
            if(frames[i]==p[j]){
                found=i;
                break;
            }
        }
        if(found!=-1){
           hits++;
           int temp=frames[found];
           for(int k=found;k>0;k--) frames[k]=frames[k-1];
           frames[0]=temp;
        }
        else{
            faults++;
            for(int k=f-1;k>0;k--) frames[k]=frames[k-1];
            frames[0]=p[j];
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