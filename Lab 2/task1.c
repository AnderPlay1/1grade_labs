#include <stdio.h>
#include <limits.h>
#define lmax 100

int main()
{
    int m, n, Q[lmax][lmax];
    char check;

    do {
        printf("Введите количество строк матрицы Q (от 1 до %d): ", lmax);
        scanf("%d", &m);
        check = getchar();
        if (check != '\n' || m <= 0) {
            printf("Некорректнрый ввод (m должно быть натуральным).\n");
            m = 0;
            while (check != '\n' && check != EOF) {
                    check = getchar();
            }
        }
    } while (m <= 0 || m > lmax);

    do {
        printf("Введите количество столбцов матрицы Q (от 1 до %d): ", lmax);
        scanf("%d", &n);
        check = getchar();
        if (check != '\n' || n <= 0) {
            printf("Некорректнрый ввод (n должно быть натуральным).\n");
            n = 0;
            while (check != '\n' && check != EOF) {
                    check = getchar();
            }
        }
    } while (n <= 0 || n > lmax);

    int temp;
    printf("Введите элементы матрицы:\n");
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            do {
                scanf("%d", &temp);
                check = getchar();
                if (check != '\n') {
                    printf("Некорректный ввод.\n");
                    temp = INT_MAX;
                    while (check != '\n' && check != EOF) {
                            check = getchar();
                    }
                }
            } while (check != '\n' || temp == INT_MAX);
            Q[i][j] = temp;
        }
    }

    printf("Исходная матрица Q:\n");
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            printf("%d ", Q[i][j]);
        }
        printf("\n");
    }

    int Z[lmax], k;
    do {
        printf("Введите длину массива Z (от 1 до %d): ", lmax);
        scanf("%d", &k);
        check = getchar();
        if (check != '\n' || k <= 0) {
            printf("Некорректнрый ввод (k должно быть натуральным).\n");
            k = 0;
            while (check != '\n' && check != EOF) {
                    check = getchar();
            }
        }
    } while (k <= 0 || k > lmax);
    
    printf("Введите элементы массива Z:\n");
    for (int i = 1; i <= k; i++) {   
        do {
            scanf("%d", &temp);
            check = getchar();
            if (check != '\n') {
                printf("Некорректный ввод.\n");
                temp = INT_MAX;
                while (check != '\n' && check != EOF) {
                        check = getchar();
                }
            }
        } while (check != '\n' || temp == INT_MAX);
        Z[i] = temp;
    }
    
    int lineSum = 0, g = 1;
    for (int i = 1; i <= m; i++) {
        lineSum = 0;
        for (int j = 1; j <= n; j++) {
            lineSum += Q[i][j];
        }
        g = 1;
        while (g <= k && lineSum != Z[g]) {
            g++;
        }
        if (g <= k) {
            printf("Сумма элементов %d-й строки матрицы Q равна %d, что совпадает с элементом Z[%d] = %d\n", i, lineSum, g, Z[g]);
            for (int j = 1; j < n; j++) {
                for (int p = j + 1; p <= n; p++) {
                    if (Q[i][j] > Q[i][p]) {
                        int swap = Q[i][j];
                        Q[i][j] = Q[i][p];
                        Q[i][p] = swap;
                    }
                }
            }
        } 
        else {
            printf("Сумма элементов %d-й строки матрицы Q равна %d, что не совпадает ни с одним элементом массива Z\n", i, lineSum);
        }
    }

    printf("Преобразованная матрица Q:\n");
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            printf("%d ", Q[i][j]);
        }
        printf("\n");
    }
    return 0;
 }