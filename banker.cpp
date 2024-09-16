#include <iostream>
#include <vector>
using namespace std;
int main() {
    int n, m, k, i ,j;
    cout<<"Enter the number of processes: ";
    cin>>n;
    cout<<"Enter the number of instances: ";
    cin>>m;
    int max[n][m], alloc[n][m], avail[m];
    cout<<"Enter avail: ";
    for(int i=0; i<m; i++){
        cin>>avail[i];
    }
    cout<<"\nEnter allot: "<<endl;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            cin>>alloc[i][j];
        }
    }
    cout<<"\nEnter max: "<<endl;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            cin>>max[i][j];
        }
    }
    int f[n], ans[n], ind = 0;
    for (k = 0; k < n; k++) {
        f[k] = 0;
    }
    int need[n][m];
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++)
        need[i][j] = max[i][j] - alloc[i][j];
    }
    int y = 0;
    for (k = 0; k < n; k++) {
        for (i = 0; i < n; i++) {
        if (f[i] == 0) {

            int flag = 0;
            for (j = 0; j < m; j++) {
            if (need[i][j] > avail[j]){
                flag = 1;
                break;
            }
            }
            if (flag == 0) {
            ans[ind++] = i;
            for (y = 0; y < m; y++)
                avail[y] += alloc[i][y];
            f[i] = 1;
            }
        }
        }
    }
    int flag = 1;
    for(int i = 0;i<n;i++){
            if(f[i]==0){
            flag = 0;
            cout << "The given sequence is not safe";
            break;
        }
    }
    if(flag==1){
        cout<<"\nNeed: "<<endl;
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                cout<<need[i][j]<<" ";
            }
            cout<<endl;
        }
        cout<<"\nSAFE Sequence:";
        for (i = 0; i < n - 1; i++)
            cout << " P" << ans[i] << " ->";
        cout << " P" << ans[n - 1] <<endl;
    }
    return 0;
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