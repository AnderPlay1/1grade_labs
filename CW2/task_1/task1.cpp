#include "task1.hpp"

/**
 * @file task1.cpp
 * @brief Реализация функций для задания 1.
 * @details Содержит проверку размеров, поиск минимума по столбцу, вычисление суммы
 * элементов до минимума и формирование массива результата.
 * @author Андреев Глеб
 * @date 12.03.2026
 */

int findMinRowInColumn(const int A[], int rowsA, int colsA, int col)
{
    int minRow = 0;
    for (int i = 1; i < rowsA; ++i)
    {
        if (A[i * colsA + col] < A[minRow * colsA + col])
        {
            minRow = i;
        }
    }
    return minRow;
}

int sumBeforeMinInColumn(const int A[], int rowsA, int colsA, int col, int minRow)
{
    int sum = 0;
    for (int i = 0; i < minRow; ++i)
    {
        sum += A[i * colsA + col];
    }
    return sum;
}

bool containsValue(const int B[], int lenB, int value)
{
    for (int i = 0; i < lenB; ++i)
    {
        if (B[i] == value)
        {
            return true;
        }
    }
    return false;
}

bool buildArrayC(const int A[], int rowsA, int colsA, const int B[], int lenB, int C[], int &lenC)
{
    if (A == nullptr || B == nullptr || C == nullptr)
    {
        lenC = 0;
        return false;
    }

    lenC = 0;

    for (int col = 0; col < colsA; ++col)
    {
        int minRow = findMinRowInColumn(A, rowsA, colsA, col);
        int sum = sumBeforeMinInColumn(A, rowsA, colsA, col, minRow);

        if (containsValue(B, lenB, sum))
        {
            for (int i = 0; i < minRow; ++i)
            {
                C[lenC++] = A[i * colsA + col];
            }
        }
    }

    return true;
}