#include <bits/stdc++.h>
using namespace std;
using vint = vector<int>;
using Matrix = vector<vector<int>>;

// Función para sumar dos matrices
void sumMatrices(Matrix &A, Matrix &B, Matrix &C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

// Función para restar dos matrices
void subtractMatrices(Matrix &A, Matrix &B, Matrix &C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}

// Multiplicación tradicional para tamaños pequeños
void traditionalMultiplication(Matrix &A, Matrix &B, Matrix &C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
}

// Implementación de Strassen optimizada
void strassen(Matrix &A, Matrix &B, Matrix &C, int n) {
    if (n <= 16) { // Caso base: usa multiplicación tradicional
        traditionalMultiplication(A, B, C, n);
        return;
    }

    int newSize = n / 2;

    // Matrices intermedias para almacenar resultados parciales
    static Matrix AResult(newSize, vint(newSize)), BResult(newSize, vint(newSize));
    static Matrix M1(newSize, vint(newSize)), M2(newSize, vint(newSize));
    static Matrix M3(newSize, vint(newSize)), M4(newSize, vint(newSize));
    static Matrix M5(newSize, vint(newSize)), M6(newSize, vint(newSize));
    static Matrix M7(newSize, vint(newSize));

    // Divide las matrices A y B en submatrices
    Matrix A11(newSize, vint(newSize)), A12(newSize, vint(newSize));
    Matrix A21(newSize, vint(newSize)), A22(newSize, vint(newSize));
    Matrix B11(newSize, vint(newSize)), B12(newSize, vint(newSize));
    Matrix B21(newSize, vint(newSize)), B22(newSize, vint(newSize));

    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            // Submatrices de A
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];

            // Submatrices de B
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }

    // Calculo de los 7 productos intermedios
    sumMatrices(A11, A22, AResult, newSize);
    sumMatrices(B11, B22, BResult, newSize);
    strassen(AResult, BResult, M1, newSize);

    sumMatrices(A21, A22, AResult, newSize);
    strassen(AResult, B11, M2, newSize);

    subtractMatrices(B12, B22, BResult, newSize);
    strassen(A11, BResult, M3, newSize);

    subtractMatrices(B21, B11, BResult, newSize);
    strassen(A22, BResult, M4, newSize);

    sumMatrices(A11, A12, AResult, newSize);
    strassen(AResult, B22, M5, newSize);

    subtractMatrices(A21, A11, AResult, newSize);
    sumMatrices(B11, B12, BResult, newSize);
    strassen(AResult, BResult, M6, newSize);

    subtractMatrices(A12, A22, AResult, newSize);
    sumMatrices(B21, B22, BResult, newSize);
    strassen(AResult, BResult, M7, newSize);

    // Combina los resultados en la matriz C
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            C[i][j] = M1[i][j] + M4[i][j] - M5[i][j] + M7[i][j];  // C11
            C[i][j + newSize] = M3[i][j] + M5[i][j];              // C12
            C[i + newSize][j] = M2[i][j] + M4[i][j];              // C21
            C[i + newSize][j + newSize] = M1[i][j] - M2[i][j] + M3[i][j] + M6[i][j]; // C22
        }
    }
}



int main() {
    // Leer matrices A y B desde archivos generados previamente
    ifstream archivoA("matrizA.txt");
    ifstream archivoB("matrizB.txt");

    Matrix A, B;
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

    // Asegurarse de que las matrices sean cuadradas y de tamaño potencia de 2
    int n = A.size();  
    if (A[0].size() != n || B.size() != n || B[0].size() != n) {
        cerr << "Las matrices deben ser cuadradas y de tamaño potencia de 2 para Strassen" << endl;
        return 1;
    }

    // Inicializar la matriz C con ceros
    Matrix C(n, vint(n, 0));

    auto start = chrono::high_resolution_clock::now();
    
    // Llamada a la función strassen
    strassen(A, B, C, n);
    
    auto end = chrono::high_resolution_clock::now();

    cout << "Tiempo de ejecucion: "
         << chrono::duration<double, milli>(end - start).count()
         << " ms" << endl;

    return 0;
}
