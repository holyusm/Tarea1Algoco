#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double; 
using vint = vector<int>;
using vvint = vector<vector<int>>;

void multiplicarMatricesOptimizado(const vvint& A, const vvint& B, vvint& C) {
    int filasA = A.size();
    int columA = A[0].size();
    int columB = B[0].size();

    // Transposición de la matriz B
    vvint BT(columB, vint(columA, 0));
    for (int i = 0; i < columA; ++i) {
        for (int j = 0; j < columB; ++j) {
            BT[j][i] = B[i][j];
        }
    }

    // Multiplicación utilizando la matriz transpuesta
    for (int i = 0; i < filasA; ++i) {
        for (int j = 0; j < columB; ++j) {
            for (int k = 0; k < columA; ++k) {
                C[i][j] += A[i][k] * BT[j][k];
            }
        }
    }
}

int main() {
    vvint A = {
        {2, 4},
        {1, 3},
        {5, 7}};

    vvint B = {
        {3, 5, 6},
        {4, 8, 9}};

    vvint C(3, vint(3, 0)); 

    multiplicarMatricesOptimizado(A, B, C);

    for (const auto& row : C) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }

    return 0;
}