#include <iostream>
using namespace std;
#define max 12
float Ct[max], TAT[max], Wt[max];

void cal(int n, float At[], float Bt[])
{
    int bt = 0;
    // Completion time calculation
    for (int i = 0; i < n; i++)
    {
        if (At[i] <= bt)
            bt += Bt[i];
        else
            bt = Bt[i] + At[i];
        Ct[i] = bt;
    }
    // Turn around time
    for (int i = 0; i < n; i++)
    {
        int tat;
        tat = Ct[i] - At[i];
        TAT[i] = tat;
    }
    // Waiting time
    for (int i = 0; i < n; i++)
    {
        int wt;
        wt = TAT[i] - Bt[i];
        Wt[i] = wt;
    }
}
void sort(int n, float At[], float Bt[], int P[])
{
    int temp;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (At[i] > At[j])
            {
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
}
int main()
{
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;
    int P[n];
    float At[n], Bt[n], sum = 0;
    float avgtat, avgwt;
    for (int i = 0; i < n; i++)
        P[i] = i + 1;
    cout << "Enter the arrival time: ";
    for (int i = 0; i < n; i++)
        cin >> At[i];
    cout << "Enter the brust time: ";
    for (int i = 0; i < n; i++)
        cin >> Bt[i];
    sort(n, At, Bt, P);
    cal(n, At, Bt);
    cout << "\nProcess No.\tAt\tBt\tCt\tTAT\tWt";
    for (int i = 0; i < n; i++)
    {
        cout << "\nP" << P[i] << "\t\t";
        cout << At[i] << "\t" << Bt[i] << "\t" << Ct[i] << "\t" << TAT[i] << "\t" << Wt[i];
    }
    cout << "\n\nGantt Chart\n";
    for (int i = 0; i < n; i++)
    {
        cout << "| P" << P[i];
    }
    cout << "|\n";
    cout << (int)At[0] << "   ";
    for (int i = 0; i < n; i++)
    {
        cout << (int)Ct[i] << "  ";
    }
    cout << "\n";
    // avg turn around time
    for (int i = 0; i < n; i++)
        sum += TAT[i];
    avgtat = sum / n;
    sum = 0;
    // avg waitinf time
    for (int i = 0; i < n; i++)
        sum += Wt[i];
    avgwt = sum / n;
    cout << "\nAvg TAT: " << avgtat;
    cout << "\nAvg Wt: " << avgwt;
    return 0;
}
