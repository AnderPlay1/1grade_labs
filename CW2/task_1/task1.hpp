#ifndef TASK1_HPP
#define TASK1_HPP

/**
 * @file task1.hpp
 * @brief Заголовочный файл функций для задания 1.
 * @details Содержит объявления функций для формирования массива C из элементов матрицы A,
 * расположенных перед минимальным элементом каждого столбца, если сумма этих элементов
 * содержится в массиве B.
 * @author Андреев Глеб
 * @date 12.03.2026
 */

const int MAX_ROWS = 20;
const int MAX_COLS = 20;
const int MAX_B = 100;
const int MAX_C = MAX_ROWS * MAX_COLS;

/**
 * @brief Ищет индекс минимального элемента в столбце матрицы.
 * @details Если минимальных элементов несколько, возвращается индекс первого сверху.
 * @param A Матрица, хранящаяся в виде одномерного массива.
 * @param rowsA Количество строк.
 * @param colsA Количество столбцов.
 * @param col Индекс столбца.
 * @return Индекс строки минимального элемента.
 * @author Андреев Глеб
 * @date 12.03.2026
 */
int findMinRowInColumn(const int A[], int rowsA, int colsA, int col);

/**
 * @brief Вычисляет сумму элементов столбца, расположенных строго перед минимумом.
 * @param A Матрица, хранящаяся в виде одномерного массива.
 * @param rowsA Количество строк.
 * @param colsA Количество столбцов.
 * @param col Индекс столбца.
 * @param minRow Индекс строки минимального элемента.
 * @return Сумма элементов до минимума.
 * @author Андреев Глеб
 * @date 12.03.2026
 */
int sumBeforeMinInColumn(const int A[], int rowsA, int colsA, int col, int minRow);

/**
 * @brief Проверяет наличие значения в массиве.
 * @param B Массив.
 * @param lenB Длина массива.
 * @param value Искомое значение.
 * @return true, если значение найдено, иначе false.
 * @author Андреев Глеб
 * @date 12.03.2026
 */
bool containsValue(const int B[], int lenB, int value);

/**
 * @brief Формирует массив C по условию задачи.
 * @details В массив C последовательно добавляются элементы каждого столбца, расположенные
 * строго перед минимальным элементом, если сумма этих элементов содержится в B.
 * @param A Матрица A.
 * @param rowsA Количество строк A.
 * @param colsA Количество столбцов A.
 * @param B Массив B.
 * @param lenB Длина массива B.
 * @param C Выходной массив C.
 * @param lenC Выходная длина массива C.
 * @return true, если входные данные корректны, иначе false.
 * @author Андреев Глеб
 * @date 12.03.2026
 */
bool buildArrayC(const int A[], int rowsA, int colsA,
                 const int B[], int lenB,
                 int C[], int &lenC);

#endif