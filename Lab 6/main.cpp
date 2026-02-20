#include <iostream>
#include <iomanip>
#include <limits>
#include "lib.h"

using namespace std;

// Part 1
void fillA(int *A, int r, int c)
{
    for (int i = 0; i < r; ++i)
        for (int j = 0; j < c; ++j)
        {
            int I = i + 1, J = j + 1;
            // Part 1 requirement: by index
            A[i * c + j] = (I > J ? I : J);
        }
}

// Part 2
void calcC(const int *A, const int *B, int *C, int r, int c)
{
    int n = r * c;
    for (int k = 0; k < n; ++k)
    {
        *(C + k) = *(A + k) - *(B + k);
    }
}

int main()
{
    const int MIN_SIZE = 1, MAX_SIZE = 400;
    const int MIN_VAL = -100000, MAX_VAL = 100000;

    cout << "=== Part 1 ===\n";
    int r = readInt("Enter rows for matrix A: ", MIN_SIZE, MAX_SIZE);
    int c = readInt("Enter columns for matrix A: ", MIN_SIZE, MAX_SIZE);

    int *A = new int[r * c];
    fillA(A, r, c);
    printMatrix("Matrix A (a_ij = max(i, j))", A, r, c);

    cout << "\n=== Part 2 ===\n";
    cout << "Operation: C = A - B\n";
    cout << "Matrix B must be the same size as A.\n";

    int *B = new int[r * c];
    readMatrix(B, r, c, "B", MIN_VAL, MAX_VAL);
    printMatrix("Matrix B", B, r, c);

    int *C = new int[r * c];
    calcC(A, B, C, r, c);
    printMatrix("Matrix C (A - B)", C, r, c);

    delete[] A;
    delete[] B;
    delete[] C;
    return 0;
}