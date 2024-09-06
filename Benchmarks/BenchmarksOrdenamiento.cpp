#include <bits/stdc++.h>
using namespace std;
using ll = long long int;
using ld = long double; 
using vint = vector<int>;
using vvint = vector<vector<int>>;

// Insertion Sort
void insertionSort(vint& arr, int n)
{
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}


// Merge Sort
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

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

// Merge Sort
void mergeSort(vector<int>& arr, int left, int right) {
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}


// Quick Sort
int partition(vector<int>& arr, int low, int high)
{
    int pivot = arr[high]; 
    int i = (low - 1); 

    for (int j = low; j <= high - 1; j++) 
    {
        if (arr[j] <= pivot) {
            i++; 
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

int partition_r(vector<int>& arr, int low, int high)
{
    srand(time(NULL));
    int random = low + rand() % (high - low);
    swap(arr[random], arr[high]);
    return partition(arr, low, high);
}

void quickSort(vector<int>& arr, int low, int high)
{
    if (low < high) {
        int pi = partition_r(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}


void saveToCSV(const vector<pair<string, double>>& tiempos, const string& filename) {
    ofstream file(filename);
    file << "Algoritmos,Tiempo(ms)" << endl;
    for (const auto& tiempo : tiempos) {
        file << tiempo.first << "," << fixed << setprecision(2) << tiempo.second << endl;
    }
    file.close();
    cout << "Archivo CSV guardado correctamente." << endl;
}

int main() {
    ifstream archivo("lista_ascendente4.txt");
    vint arr;
    int numero;

    if (archivo.is_open()) {
        while (archivo >> numero) {
            arr.push_back(numero);
        }
        archivo.close();
    } else {
        cerr << "No se pudo abrir el archivo" << endl;
        return 1;
    }

    vector<pair<string, double>> tiempos;
    for (int i = 0; i < 4; i++) {
        vint aux = arr;

        if (i == 0) {
            auto start = chrono::high_resolution_clock::now();
            insertionSort(aux, aux.size());
            tiempos.push_back({"InsertionSort", chrono::duration<double, milli>(chrono::high_resolution_clock::now() - start).count()});
        } else if (i == 1) {
            auto start = chrono::high_resolution_clock::now();
            mergeSort(aux, 0, aux.size() - 1);
            tiempos.push_back({"MergeSort", chrono::duration<double, milli>(chrono::high_resolution_clock::now() - start).count()});
        } else if (i == 2) {
            auto start = chrono::high_resolution_clock::now();
            quickSort(aux, 0, aux.size() - 1);
            tiempos.push_back({"QuickSort", chrono::duration<double, milli>(chrono::high_resolution_clock::now() - start).count()});
        } else if (i == 3) {
            auto start = chrono::high_resolution_clock::now();
            sort(aux.begin(), aux.end());
            tiempos.push_back({"Sort", chrono::duration<double, milli>(chrono::high_resolution_clock::now() - start).count()});
        }
    }

    saveToCSV(tiempos, "lista_ascendente4.csv");

    // Imprimir los tiempos de ejecución
    cout << fixed << setprecision(2);
    for (const auto& tiempo : tiempos) {
        cout << "Tiempo de ejecucion de " << tiempo.first << ": " << tiempo.second << " milisegundos" << endl;
    }

    return 0;
}
