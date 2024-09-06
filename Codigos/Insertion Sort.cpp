#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double; 
using vint = vector<int>;



void insertionSort(vint& arr, int n)
{
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;

        // Mueve los elementos mayores que 'key' una posición hacia adelante
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        // Inserta 'key' en la posición correcta
        arr[j + 1] = key;
    }
}

int main() {
    vint arr = {64, 23, 34, 45, 66, 78, 25, 12, 22, 11};

    int n = arr.size(); 
    insertionSort(arr, n);
     

    cout << "Vector ordenado: \n";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;

    return 0;
}
        
