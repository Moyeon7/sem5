#include <iostream>
#include <vector>
#include <climits>
#include <iomanip>
using namespace std;
struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
    int prior;
};
int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;
    vector<Process> proc(n);
    vector<bool> isCompleted(n, false);
    vector<int> Gantt(50);              
    vector<int> GanttTime(50);         
    vector<int> line(50);            
    vector<int> tr(50);                
    int totalCompletion = 0;
    float totalTAT = 0, totalWT = 0;
    cout << "Arrival Time: ";
    for (int i = 0; i < n; i++) {
        cin >> proc[i].arrivalTime;
    }
    cout << "Burst Time: ";
    for (int i = 0; i < n; i++) {
        cin >> proc[i].burstTime;
    }
    cout << "Priority: ";
    for (int i = 0; i < n; i++) {
        cin >> proc[i].prior;
    }
    for (int i = 0; i < n; i++) {
        proc[i].id = i + 1;
        proc[i].remainingTime = proc[i].burstTime;
    }
    int currentTime = 0;
    int completed = 0;
    int g = 0, b = 1, t = 0;
    while (completed != n) {
        int minRemainingTime = INT_MAX;
        int index = -1;
        for (int i = 0; i < n; i++) {
            // Check for the current time which processes have arrived and select the one with the highest priority
            if (proc[i].arrivalTime <= currentTime && !isCompleted[i] && proc[i].prior < minRemainingTime) {
                minRemainingTime = proc[i].prior;
                index = i;
            }
        }
        if (index == -1) {
            currentTime++;
        } else {
            tr[t++] = proc[index].id;
            Gantt[g] = proc[index].id;
            GanttTime[g++] = currentTime; 
            proc[index].remainingTime--;  
            currentTime++;
            if (proc[index].remainingTime == 0) { // Process completed
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
    int index = 0;
    for (int i = 0; i < 50; i++) {
        if ((tr[index] == tr[index - 1])) {
            line[b - 1] += 1;
        } else {
            line[b] += 1;
            b++;
        }
        index++;
    }
    cout << "\nProcess No.\tAt\tBt\tCt\tTAT\tWt\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << proc[i].id << "\t\t" << proc[i].arrivalTime << "\t" << proc[i].burstTime << "\t" << proc[i].completionTime
             << "\t" << proc[i].turnaroundTime << "\t" << proc[i].waitingTime << endl;
    }
    int track = 0;
    // Gantt Chart
    cout << endl << "Gantt Chart:\n| ";
    for (int i = 0; i < g; i++) {
        if (Gantt[i] == Gantt[i + 1]) {
            continue;
        } else {
            cout << "P" << Gantt[i] << " | ";
            track++;
        }
    }
    int start = GanttTime[0];
    cout << endl << start ; 
    for (int i = 1; i < g; i++) {
        if (Gantt[i] != Gantt[i - 1]) {
            cout << setw(5) << GanttTime[i];
        }
    }
    cout << setw(5) << currentTime << endl; 
    cout << "\nAverage Turnaround Time: " << totalTAT / n << endl;
    cout << "Average Waiting Time: " << totalWT / n << endl;
    return 0;
}
