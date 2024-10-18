#include <iostream>
#include <vector>
using namespace std;
int maxx[50][50], alloc[50][50], avail[50], f[50], ans[50], need[50][50], sa[50][50], oa[50][50];
int n, m, test = 0, req[50], pro, another=0;
void entry();
void ss();
void everything();
void neww();
void old();
int check();
void display();
int main() {
    int choice = 1; 
    entry();  
    while(choice != 0) {
        cout<<"\n--------------------------------------------------------------------------------"<<endl;
        cout << "\nIs there a process who is making a request? (0-no / 1-yes): ";
        cin >> choice;
        cout<<"\n--------------------------------------------------------------------------------"<<endl;
        cout<<endl;
        if(choice == 1) {
            neww(); 
        } else if (choice != 0) {
            cout << "Invalid input, please enter 0 (no) or 1 (yes)." << endl;
        }
    }
    return 0;
}
int check() {
    int flag=0;
    for(int i = 0; i < m; i++) {
        if(req[i] > need[pro][i]) {
            flag=1;cout<<"The resources requested are more than needed resources"<<endl;
        return 0;
        }else if(req[i] > sa[0][i]){
            flag=2;cout<<"The resources requested are more than available resources"<<endl;
        return 0;
        }
    }
    return 1;
}
int checkZero(){
    for(int i=0; i<m; i++){
        if(avail[i]!=0){
            return 1;
        }
    }
    return 0;
}
void neww(){
    // storing avail
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            oa[i][j]=sa[i][j];
        }
    }
    cout<<"Enter the process number who have made new request: ";
    cin>>pro;
    cout<<"Enter the requests: ";
    for(int i=0; i<m; i++){
        cin>>req[i];
    }
    if(check()==0){
        return;
    }
    cout<<"\nPERMISSION GRANTED"<<endl;
    cout<<"\nMaking changes..";
    for(int j=0; j<m; j++){
        sa[0][j] -= req[j];
        avail[j]= sa[0][j]; 
    }
    for(int j=0; j<m; j++){
        alloc[pro][j]+=req[j];
    }
    for(int j=0; j<m; j++){
        need[pro][j]-=req[j];
    }
    cout << "\nNeed matrix: " << endl;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cout << need[i][j] << " ";
        }
        cout << endl;
    }
    cout << "\nAllocation matrix: " << endl;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cout << alloc[i][j] << " ";
        }
        cout << endl;
    }
    cout << "\nAvailable resources: " << endl;
    for(int j = 0; j<m; j++){
        cout<<sa[0][j]<<" ";
    }
    cout<<endl;
    another=1;
    everything();
}
void entry() {
    cout << "Enter the number of processes: ";
    cin >> n;
    cout << "Enter the number of resource types: ";
    cin >> m;
    cout << "Enter available resources: ";
    for(int j = 0; j < m; j++) {
        cin >> avail[j];
    }
    cout << "\nEnter allocation matrix: " << endl;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> alloc[i][j];
        }
    }
    cout << "\nEnter maximum resource matrix: " << endl;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> maxx[i][j];
        }
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            need[i][j] = maxx[i][j] - alloc[i][j];
        }
    }
    cout<<"\n--------------------------------------------------------------------------------"<<endl;
    everything();  
}
void display(){
        cout << "\nNeed matrix: " << endl;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                cout << need[i][j] << " ";
            }
            cout << endl;
        }
        cout << "\nAllocation matrix: " << endl;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                cout << alloc[i][j] << " ";
            }
            cout << endl;
        }
        cout << "\nAvailable resources: " << endl;
        for(int j = 0; j<m; j++){
            cout<<sa[0][j]<<" ";
        }
        cout<<endl;
}
void old() {
    // Restore the previous availability state
    for(int i = 0; i < n; i++) {
        for(int j = 0; j<m; j++){
            sa[i][j] = oa[i][j];
        }
    }
    for(int j = 0; j < m; j++) {
        alloc[pro][j] -= req[j];
        need[pro][j] += req[j];
    }
}
void ss() {
    int flag = 1;
    for(int i = 0; i < n; i++) {
        if(f[i] == 0) {
            flag = 0;
            cout << "\nThe given sequence is not safe." << endl;
            cout<<"\n--------------------------------------------------------------------------------"<<endl;
            cout<<"\nPrevious Need, Allocation & Available: ";
            old();  // Restore state if unsafe
            display();
            return;
        }
    }
    if(flag == 1) {
        if(another==1){
            cout<<"\nNew Need, Allocation & Available";
        }
        display();
        cout << "\nSafe Sequence: ";
        for(int i = 0; i < n - 1; i++) {
            cout << "P" << ans[i] << " -> ";
        }
        cout << "P" << ans[n - 1] << endl;
        // cout<<"--------------------------------------------------------------------------------"<<endl;
    }
}
void everything() {
    int ind = 0, saa=0;
    for(int i = 0; i < n; i++) {
        f[i] = 0;  // Initialize the finish flag for all processes
    }
    for(int k = 0; k < n; k++) {
        for(int i = 0; i < n; i++) {
            if(f[i] == 0) {  // Check if the process is not finished
                bool can_allocate = true;
                for(int j = 0; j < m; j++) {
                    if(need[i][j] > avail[j]) {  // Check if process needs more than available
                        can_allocate = false;
                        break;
                    }
                }
                if(can_allocate) {
                    ans[ind++] = i;  // Add process to the safe sequence
                    for(int i = 0; i < m; i++) {
                        sa[saa][i] = avail[i];
                    }
                    saa++;
                    // Allocate resources to the process and update availability
                    for(int j = 0; j < m; j++) {
                        avail[j] += alloc[i][j];
                    }
                    for(int i = 0; i < m; i++) {
                        sa[saa][i] = avail[i];
                    }
                    f[i] = 1;  // Mark process as finished
                }
            }
        }
    }
    ss();  
}




/*
5
3
3 3 2
0 1 0
2 0 0
3 0 2
2 1 1
0 0 2
7 5 3 
3 2 2
9 0 2
2 2 2
4 3 3
*/

/*
5
4
1 6 3 0
0 0 1 2
1 0 0 0
1 3 4 5 
0 6 3 2
0 0 1 4
0 0 1 2
1 7 5 0
2 3 5 6
0 6 5 2
0 6 5 6
*/