#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using vint = vector<int>;
using vvint = vector<vector<int>>;

// Función para generar una lista aleatoria
void generateRandomList(int size, int maxValue, const string& filename) {
    ofstream outfile(filename);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, maxValue);

    for (int i = 0; i < size; i++) {
        outfile << dis(gen) << " ";
    }
    outfile.close();
}

// Función para generar una lista ordenada
void generateSortedList(int size, int maxValue, const string& filename) {
    ofstream outfile(filename);

    int step = maxValue / size;
    for (int i = 0; i < size; i++) {
        outfile << i * step + 1 << " ";
    }
    outfile.close();
}

// Función para generar una lista en orden inverso
void generateReverseList(int size, int maxValue, const string& filename) {
    ofstream outfile(filename);

    int step = maxValue / size;
    for (int i = size; i > 0; i--) {
        outfile << i * step << " ";
    }
    outfile.close();
}

// Función para generar una lista casi ordenada
void generateNearlySortedList(int size, int maxValue, const string& filename) {
    ofstream outfile(filename);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, maxValue);

    int step = maxValue / size;
    for (int i = 0; i < size; i++) {
        if (i % 10 == 0) {
            outfile << dis(gen) << " ";  // Introduce un número aleatorio cada 10 elementos
        } else {
            outfile << i * step + 1 << " ";
        }
    }
    outfile.close();
}

// Función para generar una lista con repeticiones significativas
void generateHighFrequencyList(int size, int maxValue, const string& filename, int numUnique) {
    ofstream outfile(filename);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, numUnique);

    for (int i = 0; i < size; i++) {
        outfile << dis(gen) << " ";
    }
    outfile.close();
}

// Función para generar una lista con valores alternantes
void generateAlternatingHighLowList(int size, int maxValue, const string& filename) {
    ofstream outfile(filename);

    int highValue = maxValue;
    int lowValue = 1;

    for (int i = 0; i < size; i++) {
        if (i % 2 == 0) {
            outfile << highValue-- << " ";
        } else {
            outfile << lowValue++ << " ";
        }
    }
    outfile.close();
}

// Función para generar una matriz cuadrada aleatoria
void generateRandomMatrix(int size, const string& filename) {
    ofstream outfile(filename);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 100);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            outfile << dis(gen) << " ";
        }
        outfile << endl;
    }
    outfile.close();
}

// Función para generar una matriz rectangular aleatoria
void generateRectangularMatrix(int rows, int cols, const string& filename) {
    ofstream outfile(filename);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 100);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            outfile << dis(gen) << " ";
        }
        outfile << endl;
    }
    outfile.close();
}

// Función para generar una matriz esparsa
void generateSparseMatrix(int size, const string& filename, double sparsity = 0.9) {
    ofstream outfile(filename);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 100);
    uniform_real_distribution<> sparseDis(0.0, 1.0);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (sparseDis(gen) < sparsity) {
                outfile << 0 << " ";  // Alta probabilidad de ser cero
            } else {
                outfile << dis(gen) << " ";
            }
        }
        outfile << endl;
    }
    outfile.close();
}

void generateSparseRectangularMatrix(int rows, int cols, const string& filename, double sparsity = 0.9) {
    ofstream outfile(filename);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 100);
    uniform_real_distribution<> sparseDis(0.0, 1.0);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (sparseDis(gen) < sparsity) {
                outfile << 0 << " ";  // Alta probabilidad de ser cero
            } else {
                outfile << dis(gen) << " ";
            }
        }
        outfile << endl;
    }
    outfile.close();
}

int main() {
    //Generación de listas de ejemplo
    //generateRandomList(10000, 10000, "lista_desordenada4.txt");
    //generateSortedList(10000, 10000, "lista_ascendente4.txt");
    //generateReverseList(10000, 10000, "lista_descendente4.txt");
    //generateNearlySortedList(10000, 10000, "lista_casi_ordenada4.txt");
    //generateHighFrequencyList(10000, 10000, "lista_repeticiones4.txt", 10);
    //generateAlternatingHighLowList(10000, 10000, "lista_valores_alternantes4.txt");


    //Generación de matrices A y B para pruebas
    //generateRandomMatrix(1024, "matrizA1024.txt");  // Genera una matriz A de 100x100
    //generateRandomMatrix(1024, "matrizB1024.txt");  // Genera una matriz B de 100x100

    // Otras matrices que también podrías generar si necesitas diferentes tamaños o tipos
    //generateRectangularMatrix(100, 150, "matrizA_100x150.txt");  // Matriz A rectangular de 50x100
    //generateRectangularMatrix(150, 100, "matrizB_150x100.txt");  // Matriz B rectangular de 100x50


    generateSparseMatrix(1024, "sparse_matrizA1024.txt", 0.9);      // Matriz A esparsa de 100x100
    generateSparseMatrix(1024, "sparse_matrizB1024.txt", 0.9);      // Matriz B esparsa de 100x100

    //generateSparseRectangularMatrix(250, 500, "sparse_matrizA_250x500.txt", 0.9);  // Matriz A rectangular esparsa de 50x100
    //generateSparseRectangularMatrix(500, 250, "sparse_matrizB_500x250.txt", 0.9);  // Matriz B rectangular esparsa de 100x50


    return 0;
}
