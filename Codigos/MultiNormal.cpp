#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double; 
using vint = vector<int>;
using vvint = vector<vector<int>>;

void multiplicarMatrices(const vvint& A, const vvint& B, vvint& C) {
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

int main() {
    vvint A = {
        {2, 4},
        {1, 3},
        {5, 7}};

    vvint B = {
        {3, 5, 6},
        {4, 8, 9}};

    vvint C(3, vint(3, 0)); 

    multiplicarMatrices(A, B, C);

    for (const auto& row : C) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }

    return 0;
}