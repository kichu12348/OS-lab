#include <stdio.h>


/*
    verfiying the output 
    is a pain 💀💀💀💀
*/


typedef struct 
{
    int freq;
    int val;
    int at; //arival time
}Data;


void algo(Data p[], int n, int f)
{
    Data frames[f];
    int faults = 0,
        hits = 0,
        front = 0,
        time=0;

    for(int i=0;i<f;i++) {
        frames[i].freq=0;
        frames[i].val=-1;
        frames[i].at=-1;
    }

    for(int j=0;j<n;j++){
        int found=-1;
        for(int i=0;i<f;i++){
            if(frames[i].val==p[j].val){
                found=i;
                break;
            }
        }
        if(found!=-1){
            hits++;
            frames[found].freq++;
            frames[found].at=time;
        }
        else{
            faults++;
            if(front<f){
                frames[front]=p[j];
                frames[front].at=time;
                front++;
            }
            else{
                int idx=-1,
                    minF=999,
                    oldestTime=999;

                for(int k=0;k<f;k++) 
                    if(frames[k].freq < minF && frames[k].val!=-1) 
                        minF=frames[k].freq;

                for(int k=0;k<f;k++){
                    if(frames[k].freq==minF && frames[k].at<oldestTime){
                        idx=k;
                        oldestTime=frames[k].at;
                    }
                }    
            
                frames[idx]=p[j];
                frames[idx].freq=1;
                frames[idx].at=time;
            }
        }

        printf("Frames: ");
        for(int k=0;k<f;k++) printf("%d(%d) ",frames[k].val,frames[k].freq);
        printf("faults: %d\n",faults);
        time++;
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
    Data p[n];
    printf("Enter the pages: ");
    for(int i=0;i<n;i++){
        scanf("%d", &p[i].val);
        p[i].freq=1;
    }
    algo(p, n, f);
}