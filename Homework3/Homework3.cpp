#include <iostream>
#include <ctime>
#include <cstdlib>

#define prag 10

using namespace std;

int alege_poz_pivot(int st, int dr){
    return (st+dr)/2;
}

int partition_Hoare(int* v, int st, int dr){
    int pivot = v[alege_poz_pivot(st,dr)];
    int i=st , j=dr;
    while (true){
        while (v[i]<pivot) i++;
        while (v[j]>pivot) j--;
        if (i>=j) return j;
        swap(v[i],v[j]);
        i++;
        j--;
    }
}

void insertionsort(int* v, int st, int dr){
    int pivot, j;
    for(int i=st+1; i <= dr; i++){
        pivot = v[i];
        j = i - 1;

        while (j >= 0 && v[j] > pivot){
            v[j + 1] = v[j];
            j = j - 1;
        }
        v[j + 1] = pivot;
    }
}

void quicksort(int* v, int st, int dr){
    if (dr-st+1 > prag){
        int poz_pivot = partition_Hoare(v,st,dr);
        quicksort(v,st,poz_pivot);
        quicksort(v,poz_pivot+1,dr);
    }
    else{
        insertionsort(v, st, dr);
    }
}

int main(){
    srand(time(nullptr));
    int n=130;
    int v[n];
    for (int i=0;i<n;i++)
        v[i]=rand()%50;

    for (int i=0;i<n;i++)
        cout<<v[i]<<" ";
    cout<<endl;

    quicksort(v,0,n-1);

    for (int i=0;i<n;i++)
        cout<<v[i]<<" ";

    return 0;
}