#include <iostream>
#define max 12

float Ct[max], TAT[max], Wt[max];

void calculateTimes(int n, float At[], float Bt[])
{
    // Completion time
    for (int i = 0; i < n; i++)
    {
        if (i == 0)
        {
            Ct[i] = At[i] + Bt[i];
        }
        else
        {
            if (At[i] > Ct[i - 1])
            {
                Ct[i] = At[i] + Bt[i];
            }
            else
            {
                Ct[i] = Ct[i - 1] + Bt[i];
            }
        }
    }

    // Turnaround time
    for (int i = 0; i < n; i++)
    {
        TAT[i] = Ct[i] - At[i];
    }

    // Waiting time
    for (int i = 0; i < n; i++)
    {
        Wt[i] = TAT[i] - Bt[i];
    }
}

void sortProcesses(int n, float At[], float Bt[], int P[], int Pt[])
{
    int temp;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (At[i] > At[j] || (At[i] == At[j] && Pt[i] > Pt[j]))
            {
                // Swap arrival time
                temp = At[i];
                At[i] = At[j];
                At[j] = temp;

                // Swap burst time
                temp = Bt[i];
                Bt[i] = Bt[j];
                Bt[j] = temp;

                // Swap priority
                temp = Pt[i];
                Pt[i] = Pt[j];
                Pt[j] = temp;

                // Swap process number
                temp = P[i];
                P[i] = P[j];
                P[j] = temp;
            }
        }
    }
}

int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    float At[n], Bt[n], avgtat, avgwt;
    int P[n], Pt[n];

    for (int i = 0; i < n; i++)
        P[i] = i + 1;

    printf("Enter the arrival times: ");
    for (int i = 0; i < n; i++)
        scanf("%f", &At[i]);

    printf("Enter the burst times: ");
    for (int i = 0; i < n; i++)
        scanf("%f", &Bt[i]);

    printf("Enter the priorities: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &Pt[i]);

    sortProcesses(n, At, Bt, P, Pt);

    calculateTimes(n, At, Bt);

    printf("\nProcess No.\tAt\tBt\tPt\tCt\tTAT\tWt\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t\t", P[i]);
        printf("%2.2f\t%2.2f\t%d\t%2.2f\t%2.2f\t%2.2f\n", At[i], Bt[i], Pt[i], Ct[i], TAT[i], Wt[i]);
    }

    printf("\nGantt Chart\n");
    for (int i = 0; i < n; i++)
    {
        printf("| P%d ", P[i]);
    }
    printf("|\n%.0f", At[0]);
    for (int i = 0; i < n; i++)
    {
        printf("    %.0f", Ct[i]);
    }

    float sum = 0;
    for (int i = 0; i < n; i++)
        sum += TAT[i];
    avgtat = sum / n;

    sum = 0;
    for (int i = 0; i < n; i++)
        sum += Wt[i];
    avgwt = sum / n;

    printf("\n\nAvg TAT: %2.2f", avgtat);
    printf("\nAvg WT: %2.2f\n", avgwt);

    return 0;
}
