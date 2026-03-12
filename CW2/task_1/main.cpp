#include <iostream>
#include "lib.h"
#include "task1.hpp"

using namespace std;

/**
 * @file main.cpp
 * @brief Главный файл программы для задания 1.
 * @details Полное условие:
 * Дана матрица A[0:rowsA-1][0:colsA-1] и массив B[0:lenB-1]. Разработать программу,
 * которая вычисляет массив C, состоящий из элементов матрицы A, расположенных перед
 * минимальным элементом каждого столбца, если сумма этих элементов (расположенных строго
 * перед минимальным) содержится в массиве B. Вычисления оформить в виде отдельных функций
 * с параметрами. Обращение к элементам матрицы и массива — по индексу.
 * @author Student
 * @date 2026-03-12
 */

int main()
{
    int rowsA = readInt("Enter rowsA (1..20): ", 1, MAX_ROWS);
    int colsA = readInt("Enter colsA (1..20): ", 1, MAX_COLS);
    int lenB = readInt("Enter lenB (1..100): ", 1, MAX_B);

    int A[MAX_ROWS * MAX_COLS];
    int B[MAX_B];
    int C[MAX_C];
    int lenC = 0;

    readMatrix(A, rowsA, colsA, "A", -1000000, 1000000);
    readArray(B, lenB, "B", -1000000, 1000000);

    printMatrix("Matrix A", A, rowsA, colsA);
    printArray("Array B", B, lenB);

    if (!buildArrayC(A, rowsA, colsA, B, lenB, C, lenC))
    {
        cout << "Invalid input data.\n";
        return 1;
    }

    printArray("Array C", C, lenC);

    return 0;
}