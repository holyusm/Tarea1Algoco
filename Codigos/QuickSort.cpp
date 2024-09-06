#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double; 
using vint = vector<int>;

int partition(int arr[], int low, int high){
    int pivot = arr[high]; // Selecciona el pivote
    int i = (low - 1); 

    // Reorganiza elementos según el pivote
    for (int j = low; j <= high - 1; j++){
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]); // Coloca el pivote en su lugar
    return (i + 1);
}

int partition_r(int arr[], int low, int high){
    srand(time(NULL));
    int random = low + rand() % (high - low); // Pivote aleatorio
    swap(arr[random], arr[high]);
    return partition(arr, low, high);
}

void quickSort(int arr[], int low, int high){
    if (low < high){
        int pi = partition_r(arr, low, high); 
        quickSort(arr, low, pi - 1); 
        quickSort(arr, pi + 1, high); 
    }
}


int main() {
 // Acá se escribe el código
 return 0;
}
