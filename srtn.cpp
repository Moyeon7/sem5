#include <iostream>
#include <vector>
#include <iomanip>
#include <climits>
using namespace std;
struct Process
{
    int id;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
};
int main()
{
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;
    vector<Process> proc(n);
    vector<bool> isCompleted(n, false);
    vector<int> Gantt(50);
    vector<int> GanttTime(50);
    int totalCompletion = 0;
    float totalTAT = 0, totalWT = 0;
    cout << "Arrival Time: ";
    for (int i = 0; i < n; i++)
    {
        cin >> proc[i].arrivalTime;
    }
    cout << "Burst Time: ";
    for (int i = 0; i < n; i++)
    {
        cin >> proc[i].burstTime;
    }
    for (int i = 0; i < n; i++)
    {
        proc[i].id = i + 1;
        proc[i].remainingTime = proc[i].burstTime;
    }
    int currentTime = 0;
    int completed = 0;
    int g = 0;
    while (completed != n)
    {
        int minRemainingTime = INT_MAX;
        int index = -1;
        for (int i = 0; i < n; i++)
        {
            // Check for the current time which processes have arrived and whether it is completed or not
            if (proc[i].arrivalTime <= currentTime && !isCompleted[i] && proc[i].remainingTime < minRemainingTime)
            {
                minRemainingTime = proc[i].remainingTime;
                index = i;
            }
        }
        if (index == -1)
        {
            currentTime++;
        }
        else
        {
            Gantt[g] = proc[index].id;
            GanttTime[g++] = currentTime;
            proc[index].remainingTime--;
            currentTime++;
            if (proc[index].remainingTime == 0)
            {
                proc[index].completionTime = currentTime;
                proc[index].turnaroundTime = proc[index].completionTime - proc[index].arrivalTime;
                proc[index].waitingTime = proc[index].turnaroundTime - proc[index].burstTime;

                totalTAT += proc[index].turnaroundTime;
                totalWT += proc[index].waitingTime;

                isCompleted[index] = true;
                completed++;
            }
        }
    }
    cout << "\nProcess No.\tAt\tBt\tCt\tTAT\tWt\n";
    for (int i = 0; i < n; i++)
    {
        cout << "P" << proc[i].id << "\t\t" << proc[i].arrivalTime << "\t" << proc[i].burstTime << "\t" << proc[i].completionTime
             << "\t" << proc[i].turnaroundTime << "\t" << proc[i].waitingTime << endl;
    }
    // Gantt Chart
    cout << endl;
    cout << "| ";
    for (int i = 0; i < g; i++)
    {
        if (Gantt[i] == Gantt[i + 1])
        {
            continue;
        }
        else
        {
            cout << "P" << Gantt[i] << " | ";
        }
    }
    cout << endl
         << GanttTime[0];
    for (int i = 1; i < g; i++)
    {
        if (Gantt[i] != Gantt[i - 1])
        {
            cout << setw(5) << GanttTime[i];
        }
    }
    cout << setw(5) << currentTime << endl;
    cout << "\nAverage Turnaround Time: " << totalTAT / n << endl;
    cout << "Average Waiting Time: " << totalWT / n << endl;
    return 0;
}
