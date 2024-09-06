#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double; 
using vint = vector<int>;
using matrix = vector<vector<int>>;


// Multiplicar Matrices Tradicional
void multiplicarMatrices(const matrix& A, const matrix& B, matrix& C) {
    int filasA = A.size();
    int columA = A[0].size();
    int columB = B[0].size();

    for (int i = 0; i < filasA; ++i) {
        for (int j = 0; j < columB; ++j) {
            for (int k = 0; k < columA; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Multiplicar Matrices Optimizado
void multiplicarMatricesOptimizado(const matrix& A, const matrix& B, matrix& C) {
    int filasA = A.size();
    int columA = A[0].size();
    int columB = B[0].size();

    matrix BT(columB, vint(columA, 0));
    for (int i = 0; i < columA; ++i) {
        for (int j = 0; j < columB; ++j) {
            BT[j][i] = B[i][j];
        }
    }

    for (int i = 0; i < filasA; ++i) {
        for (int j = 0; j < columB; ++j) {
            for (int k = 0; k < columA; ++k) {
                C[i][j] += A[i][k] * BT[j][k];
            }
        }
    }
}

// Strassen
// Función para sumar dos matrices
void sumMatrices(matrix &A, matrix &B, matrix &C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

// Función para restar dos matrices
void subtractMatrices(matrix &A, matrix &B, matrix &C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}

// Multiplicación de matrices tradicional para tamaños pequeños
void traditionalMultiplication(matrix &A, matrix &B, matrix &C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
}

// Implementación del algoritmo de Strassen optimizado
void strassen(matrix &A, matrix &B, matrix &C, int n) {
    if (n <= 64) {
        traditionalMultiplication(A, B, C, n);
        return;
    }

    int newSize = n / 2;

    static matrix AResult(newSize, vint(newSize)), BResult(newSize, vint(newSize));
    static matrix M1(newSize, vint(newSize)), M2(newSize, vint(newSize));
    static matrix M3(newSize, vint(newSize)), M4(newSize, vint(newSize));
    static matrix M5(newSize, vint(newSize)), M6(newSize, vint(newSize));
    static matrix M7(newSize, vint(newSize));

    // Dividir matrices A y B en submatrices
    matrix A11(newSize, vint(newSize)), A12(newSize, vint(newSize));
    matrix A21(newSize, vint(newSize)), A22(newSize, vint(newSize));
    matrix B11(newSize, vint(newSize)), B12(newSize, vint(newSize));
    matrix B21(newSize, vint(newSize)), B22(newSize, vint(newSize));

    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }

    // M1 = (A11 + A22) * (B11 + B22)
    sumMatrices(A11, A22, AResult, newSize);
    sumMatrices(B11, B22, BResult, newSize);
    strassen(AResult, BResult, M1, newSize);

    // M2 = (A21 + A22) * B11
    sumMatrices(A21, A22, AResult, newSize);
    strassen(AResult, B11, M2, newSize);

    // M3 = A11 * (B12 - B22)
    subtractMatrices(B12, B22, BResult, newSize);
    strassen(A11, BResult, M3, newSize);

    // M4 = A22 * (B21 - B11)
    subtractMatrices(B21, B11, BResult, newSize);
    strassen(A22, BResult, M4, newSize);

    // M5 = (A11 + A12) * B22
    sumMatrices(A11, A12, AResult, newSize);
    strassen(AResult, B22, M5, newSize);

    // M6 = (A21 - A11) * (B11 + B12)
    subtractMatrices(A21, A11, AResult, newSize);
    sumMatrices(B11, B12, BResult, newSize);
    strassen(AResult, BResult, M6, newSize);

    // M7 = (A12 - A22) * (B21 + B22)
    subtractMatrices(A12, A22, AResult, newSize);
    sumMatrices(B21, B22, BResult, newSize);
    strassen(AResult, BResult, M7, newSize);

    // Combinar los resultados en la matriz C directamente
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            // C11 = M1 + M4 - M5 + M7
            C[i][j] = M1[i][j] + M4[i][j] - M5[i][j] + M7[i][j];

            // C12 = M3 + M5
            C[i][j + newSize] = M3[i][j] + M5[i][j];

            // C21 = M2 + M4
            C[i + newSize][j] = M2[i][j] + M4[i][j];

            // C22 = M1 - M2 + M3 + M6
            C[i + newSize][j + newSize] = M1[i][j] - M2[i][j] + M3[i][j] + M6[i][j];
        }
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
    // Leer matrices A y B desde archivos generados previamente
    ifstream archivoA("sparse_matrizA1024.txt");
    ifstream archivoB("sparse_matrizB1024.txt");

    matrix A, B;
    int numero;

    if (archivoA.is_open() && archivoB.is_open()) {
        // Leer matriz A
        string linea;
        while (getline(archivoA, linea)) {
            istringstream iss(linea);
            vint fila;
            while (iss >> numero) {
                fila.push_back(numero);
            }
            A.push_back(fila);
        }
        archivoA.close();

        // Leer matriz B
        while (getline(archivoB, linea)) {
            istringstream iss(linea);
            vint fila;
            while (iss >> numero) {
                fila.push_back(numero);
            }
            B.push_back(fila);
        }
        archivoB.close();
    } else {
        cerr << "No se pudo abrir uno de los archivos" << endl;
        return 1;
    }

    // Asegurarse de que las matrices sean compatibles para la multiplicación
    if (A[0].size() != B.size()) {
        cerr << "Las matrices no son compatibles para la multiplicación" << endl;
        return 1;
    }

    int n = A.size();  // Asumimos que es una matriz cuadrada
    matrix C(n, vint(n, 0));

    vector<pair<string, double>> tiempos;

    for (int i = 0; i < 3; i++) {
        C.assign(n, vint(n, 0));  // Reiniciar matriz C a ceros antes de cada prueba

        if (i == 0) {
            auto start = chrono::high_resolution_clock::now();
            multiplicarMatrices(A, B, C);
            tiempos.push_back({"Multiplicacion Tradicional", chrono::duration<double, milli>(chrono::high_resolution_clock::now() - start).count()});
        } else if (i == 1) {
            auto start = chrono::high_resolution_clock::now();
            multiplicarMatricesOptimizado(A, B, C);
            tiempos.push_back({"Multiplicacion Optimizada", chrono::duration<double, milli>(chrono::high_resolution_clock::now() - start).count()});
        } else if (i == 2) {
        // Verificar si las matrices son cuadradas antes de ejecutar Strassen
        if (A.size() != A[0].size() || B.size() != B[0].size() || A.size() != B.size()) {
            continue;
        }
        auto start = chrono::high_resolution_clock::now();
        strassen(A, B, C, n);
        tiempos.push_back({"Strassen", chrono::duration<double, milli>(chrono::high_resolution_clock::now() - start).count()});
    }
    }

    // Guardar resultados en CSV
    saveToCSV(tiempos, "1024x1024Dispersa.csv");

    // Imprimir los tiempos de ejecución
    cout << fixed << setprecision(2);
    for (const auto& tiempo : tiempos) {
        cout << "Tiempo de ejecucion de " << tiempo.first << ": " << tiempo.second << " milisegundos" << endl;
    }

    return 0;
}
