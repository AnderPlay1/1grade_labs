#include "task2.hpp"

/**
 * @file task2.cpp
 * @brief Реализация функций для задания 2.
 * @details Содержит функции проверки полного квадрата и удаления таких элементов
 * из массива с помощью сдвига.
 * @author Андреев Глеб
 * @date 12.03.2026
 */

bool isSquare(int value)
{
    if (value < 0)
    {
        return false;
    }

    int k = 0;
    while (k * k < value)
    {
        ++k;
    }

    return k * k == value;
}

bool removeSquares(int *A, int &lenA)
{
    if (A == nullptr || lenA < 0 || lenA > MAX_LEN_A)
    {
        return false;
    }

    int i = 0;
    while (i < lenA)
    {
        if (isSquare(*(A + i)))
        {
            for (int j = i; j < lenA - 1; ++j)
            {
                *(A + j) = *(A + j + 1);
            }
            --lenA;
        }
        else
        {
            ++i;
        }
    }

    return true;
}