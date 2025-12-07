// Даны целочисленная матрица С[0:N-1,0:M-1] и целочисленный
// массив D[0:K-1]. Написать программу, которая сортирует по
// убыванию методом пузырька элементы тех строк матрицы С, номера
// которых присутствуют в массиве D. Вычисления оформить в виде
// функции с параметрами.

#include <stdio.h>
#define lmax 100

int sort(int C[][lmax], int D[], int k, int n, int m) {
    int flag = 0;
    for (int i = 0; i < k; i++) {
        if (D[i] < 0 || D[i] >= n)
            printf("%d is not a row of matrix C \n", D[i]);
        else {
            flag = 1;
            for (int j = 0; j < m - 1; j++)
               for (int p = j + 1; p < m; p++) {
                    if (C[D[i]][j] < C[D[i]][p]) {
                        int swap = C[D[i]][j];
                        C[D[i]][j] = C[D[i]][p];
                        C[D[i]][p] = swap;
                    }
                }
        }
    }
    return flag;
}

int main() {
    printf("Final test \n");
    int n, m, k, C[lmax][lmax], D[lmax];
    char check;

    do {
        printf("Insert the number of rows in matrix C (from 1 to %d): ", lmax);
        scanf("%d", &n);
        check = getchar();
        if (check != '\n' || n <= 0) {
            printf("Input is not correct (n must be a natural number).\n");
            n = 0;
            while (check != '\n' && check != EOF) {
                    check = getchar();
            }
        }
    } while (n <= 0 || n > lmax);

    do {
        printf("Insert the number of columns in matrix C (from 1 to %d): ", lmax);
        scanf("%d", &m);
        check = getchar();
        if (check != '\n' || m <= 0) {
            printf("Input is not correct (m must be a natural number).\n");
            m = 0;
            while (check != '\n' && check != EOF) {
                    check = getchar();
            }
        }
    } while (m <= 0 || m > lmax);

    do {
        printf("Insert the number of elements in array D (from 1 to %d): ", lmax);
        scanf("%d", &k);
        check = getchar();
        if (check != '\n' || k <= 0) {
            printf("Input is not correct (k must be a natural number).\n");
            k = 0;
            while (check != '\n' && check != EOF) {
                    check = getchar();
            }
        }
    } while (k <= 0 || k > lmax);

    int temp;
    printf("Enter the elements of matrix C:\n");
    for (int i = 0; i < n; i++) 
        for (int j = 0; j < m; j++) 
                scanf("%d", &C[i][j]);

    printf("Enter the elements of array D:\n");
    for (int i = 0; i < k; i++) 
            scanf("%d", &D[i]);


    printf("Matrix C:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    printf("Array D:\n");
    for (int i = 0; i < k; i++) 
        printf("%d ", D[i]);

    printf("\n\n");

    if (sort(C, D, k, n, m)) {
        printf("Sorted matrix C:\n");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                printf("%d ", C[i][j]);
            }
            printf("\n");
        }
    }
    else 
        printf("Matrix was not sorted \n");
    return 0;
}