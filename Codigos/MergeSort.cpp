#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double; 
using vint = vector<int>;


void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Crea arrays temporales para dividir la lista en dos mitades
    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // Une las mitades ordenadas en un solo array
    int i = 0, j = 0;
    int k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i++];
        } else {
            arr[k] = R[j++];
        }
        k++;
    }
    while (i < n1) 
        arr[k++] = L[i++];
    while (j < n2) 
        arr[k++] = R[j++];
}

void mergeSort(vector<int>& arr, int left, int right) {
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;  // Divide la lista en dos mitades
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right); // Combina las mitades ordenadas
}


int main() {
    vint arr = {64, 25, 88, 23, 34, 45, 66, 78, 25, 12, 22, 11};

    mergeSort(arr, 0, arr.size() - 1);
    int tamanio = arr.size();  

    cout << "Vector ordenado: \n";
    for (int i = 0; i < tamanio; i++)
        cout << arr[i] << " ";
    cout << endl;

    return 0;
}
        
