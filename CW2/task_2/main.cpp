#include <iostream>
#include "lib.h"
#include "task2.hpp"

using namespace std;

/**
 * @file main.cpp
 * @brief Главный файл программы для задания 2.
 * @details Полное условие:
 * Дан одномерный массив целых чисел A[0:lenA-1]. Удалить путем сдвига все элементы,
 * являющиеся полными квадратами. Дополнительный массив не использовать. Обработку
 * массива оформить в виде функции с параметрами. Обращение к элементам массива —
 * с использованием указателя.
 * @author Андреев Глеб
 * @date 12.03.2026
 */

int main()
{
    int lenA = readInt("Enter lenA (0..100): ", 0, MAX_LEN_A);

    int A[MAX_LEN_A];

    if (lenA > 0)
    {
        readArray(A, lenA, "A", -1000000, 1000000);
    }

    printArray("Array A before", A, lenA);

    if (!removeSquares(A, lenA))
    {
        cout << "Invalid input data.\n";
        return 1;
    }

    printArray("Array A after", A, lenA);

    return 0;
}