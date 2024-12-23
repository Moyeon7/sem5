#include <iostream>
#define max 12
float Ct[max], TAT[max], Wt[max];
void cal(int n, float At[], float Bt[]){
    int bt = 0;
    // Completion time calculation
    for (int i = 0; i < n; i++){
        bt += Bt[i];
        Ct[i] = bt;
    }
    // Turn around time
    for (int i = 0; i < n; i++){
        int tat;
        tat = Ct[i] - At[i];
        TAT[i] = tat;
    }
    // Waiting time
    for (int i = 0; i < n; i++){
        int wt;
        wt = TAT[i] - Bt[i];
        Wt[i] = wt;
    }
}
void sort(int n, float At[], float Bt[], int P[]){
    int temp, check = 0, track = At[0];

    for (int k = 0; k < n - 1; k++){    //check if any 2 or more processes have the same arrival time if not then put check=1
        if (At[k + 1] != At[k])
            check = 1;
        track = At[k];
    }

    //sort the processes based on burst time when they have the same arrival time
    for (int i = 0; i < n; i++){
        for (int j = i + 1; j < n; j++){
            if (Bt[i] > Bt[j] && check == 0){   //same arrival time; sort by burst time
                temp = At[i];
                At[i] = At[j];
                At[j] = temp;

                temp = Bt[i];
                Bt[i] = Bt[j];
                Bt[j] = temp;

                temp = P[i];
                P[i] = P[j];
                P[j] = temp;
            }
            else if (At[i] > At[j]){
                temp = At[i];
                At[i] = At[j];
                At[j] = temp;

                temp = Bt[i];
                Bt[i] = Bt[j];
                Bt[j] = temp;

                temp = P[i];
                P[i] = P[j];
                P[j] = temp;
            }
        }
    }

    printf("\n");
}
int main(){
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    float At[n], Bt[n], count = 0, sum = 0;
    float avgtat, avgwt;
    int P[n];

    for (int i = 0; i < n; i++)
        P[i] = i + 1;

    printf("Enter the arrival time: ");
    for (int i = 0; i < n; i++)
        scanf("%f", &At[i]);

    printf("Enter the brust time: ");
    for (int i = 0; i < n; i++)
        scanf("%f", &Bt[i]);

    sort(n, At, Bt, P);

    cal(n, At, Bt);

    printf("\nProcess No.\tAt\tBt\tCt\tTAT\tWt");
    for (int i = 0; i < n; i++){
        printf("\nP%d\t\t", P[i]);
        printf("%2.2f\t%2.2f\t%2.2f\t%2.2f\t%2.2f", At[i], Bt[i], Ct[i], TAT[i], Wt[i]);
    }

    printf("\n\nGantt Chart\n");
    for (int i = 0; i < n; i++){
        printf("| P%2d ", P[i]);
    }
    printf("|\n%d", (int)At[0]);
    for (int i = 0; i < n; i++){
        printf("   %3d", (int)Ct[i]);
    }

    printf("\n");

    for (int i = 0; i < n - 1; i++){
        if (At[i] != At[i + 1])
            count++;
    }
    printf("\n");
    // avg turn around time
    for (int i = 0; i < n; i++)
        sum += TAT[i];
    avgtat = sum / n;
    sum = 0;
    // avg waitinf time
    for (int i = 0; i < n; i++)
        sum += Wt[i];
    avgwt = sum / n;
    printf("\nAvg TAT: %2.2f", avgtat);
    printf("\nAvg Wt: %2.2f\n", avgwt);

    if (count != 0)
        printf("\nDoesn't give an optimal solution\n");
    return 0;
}

/*
4
0 2 4 6
9 3 6 12
*/
