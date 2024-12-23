#include <iostream>
#include <vector>
#include <iomanip>
#include <queue>
#include <algorithm>
using namespace std;
struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
};
bool compareArrivalTime(Process a, Process b) {
    return a.arrivalTime < b.arrivalTime;
}
int main() {
    int n, quantum;
    cout << "Enter the number of processes: ";
    cin >> n;
    vector<Process> proc(n);
    vector<int> Gantt(50);
    vector<int> GanttTime(50);
    float totalTAT = 0, totalWT = 0;
    cout << "Arrival Time: ";
    for (int i = 0; i < n; i++) {
        cin >> proc[i].arrivalTime;
        proc[i].id = i + 1; 
    }
    cout << "Burst Time: ";
    for (int i = 0; i < n; i++) {
        cin >> proc[i].burstTime;
        proc[i].remainingTime = proc[i].burstTime;
    }
    sort(proc.begin(), proc.end(), compareArrivalTime);
    cout << "Enter the time quantum: ";
    cin >> quantum;
    int currentTime = 0, g = 0, completed = 0;
    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (proc[i].arrivalTime <= currentTime) {
            q.push(i);
        }
    }
    while (completed != n) {
        if (q.empty()) {
            currentTime++;
            for (int i = 0; i < n; i++) {
                if (proc[i].arrivalTime <= currentTime && proc[i].remainingTime > 0) {
                    q.push(i);
                }
            }
            continue;
        }
        int index = q.front();
        q.pop();
        Gantt[g] = proc[index].id;
        GanttTime[g++] = currentTime;
        if (proc[index].remainingTime <= quantum) {
            currentTime += proc[index].remainingTime;
            proc[index].remainingTime = 0;
            proc[index].completionTime = currentTime;
            proc[index].turnaroundTime = proc[index].completionTime - proc[index].arrivalTime;
            proc[index].waitingTime = proc[index].turnaroundTime - proc[index].burstTime;

            totalTAT += proc[index].turnaroundTime;
            totalWT += proc[index].waitingTime;
            completed++;
        } else {
            proc[index].remainingTime -= quantum;
            currentTime += quantum;
        }
        // Check if any new processes have arrived by the current time and add them to the queue
        for (int i = 0; i < n; i++) {
            if (proc[i].arrivalTime <= currentTime && proc[i].remainingTime > 0 && i != index) {
                bool alreadyInQueue = false;
                queue<int> tempQueue = q;
                while (!tempQueue.empty()) {
                    if (tempQueue.front() == i) {
                        alreadyInQueue = true;
                        break;
                    }
                    tempQueue.pop();
                }
                if (!alreadyInQueue) {
                    q.push(i);
                }
            }
        }
        // Re-addig current process if it has remaining time
        if (proc[index].remainingTime > 0) {
            q.push(index);
        }
        cout << "\nProcess No.\tAt\tBt\tCt\tTAT\tWt\n";
        for (int i = 0; i < n; i++) {
            cout << "P" << proc[i].id << "\t\t" << proc[i].arrivalTime << "\t" << proc[i].burstTime << "\t" << proc[i].completionTime
                << "\t" << proc[i].turnaroundTime << "\t" << proc[i].waitingTime << endl;
        }
        // Gantt Chart
        cout << endl;
        cout << "| ";
        for (int i = 0; i < g; i++) {
            if (Gantt[i] == Gantt[i + 1]) {
                continue;
            } else {
                cout << "P" << Gantt[i] << " | ";
            }
        }
        cout << endl << GanttTime[0];
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
}
