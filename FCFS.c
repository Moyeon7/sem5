#include<stdio.h>
#define max 12
int Ct[max], TAT[max], Wt[max];


void cal(int n, int At[n], int Bt[n]){
    int bt=0;
    // Completion time calculation
    for(int i=0; i<n; i++){
        if(At[i]<=bt)
            bt+=Bt[i];
        else
            bt=Bt[i]+At[i];
        Ct[i]=bt;
    }
    // Turn around time
    for(int i=0; i<n; i++){
        int tat;
        tat=Ct[i]-At[i];
        TAT[i]=tat;
    }
    // Waiting time
    for(int i=0; i<n; i++){
        int wt;
        wt=TAT[i]-Bt[i];
        Wt[i]=wt;
    }
}

int main(){
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int At[n], Bt[n];

    printf("Enter the arrival time: ");
    for(int i=0; i<n; i++)
        scanf("%d", &At[i]); 

    printf("Enter the brust time: ");
    for(int i=0; i<n; i++)
        scanf("%d", &Bt[i]); 

    cal(n, At, Bt);
    
    printf("\nProcess No.\tAt\tBt\tCt\tTAT\tWt");
    for(int i=0; i<n; i++){
        printf("\nP%d\t\t", i+1);
        printf("%d\t%d\t%d\t%d\t%d", At[i], Bt[i], Ct[i], TAT[i], Wt[i]);
    }

    printf("\n\nGantt Chart\n");
    for(int i=0; i<n; i++){
        printf("| P%2d ", i);
    }
    printf("|\n");
    for(int i=0; i<n; i++){
        printf("|  %2d ", Ct[i]);
    }
    printf("|\n");
    return 0;
}

/*
4
0 1 5 6
2 2 3 4
*/