#include <iostream>
#define n 7

using namespace std;

int matrix[n][n];

void show(int matrix[][n]){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++)
            cout<<matrix[i][j]<<" ";
        cout<<endl;
    }
    cout<<endl;
}

void c(int matrix[][n]){
    for(int i=0; i<n; i++)
        matrix[i][(i+1)%n] = 1;
}

void cm(int matrix[][n], int m){
    bool ok;
    int sum;
    for(int i=0; i<n; i++){
        ok2 = true;
        for(int k=1; k<m; k++){
            ok = false;
            sum = 0; 
            for(int j=0; j<m; j++){
                if(matrix[(i+j)%n][(i+j+k)%n] == 1){
                    ok = true;
                    sum += k-1;
                    break;
                }
            }
            if(ok == true)
                matrix[i][(i+m+sum)%n] = 1;
        }

    }
}

int main(){
    
    c(matrix);
    show(matrix);
    cm(matrix, 2);
    show(matrix);
    cm(matrix, 3);
    show(matrix);

    return 0;
}