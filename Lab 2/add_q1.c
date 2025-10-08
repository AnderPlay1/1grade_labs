#include <stdio.h>
#include <limits.h>
#define lmax 100

/*2. Даны целочисленная матрица A[1:n, 1:m]. Удалить путем сдвига все
столбцы матрицы, не содержащие ни одного нуля.*/

int main() {
    int m, n, A[lmax][lmax];
    char check;
    printf("Лабораторная работа №2, дополнительная задача №1\n");
    do {
        printf("Введите количество строк матрицы A (от 1 до %d): ", lmax);
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

    do {
        printf("Введите количество столбцов матрицы A (от 1 до %d): ", lmax);
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
    int temp;
    printf("Введите элементы матрицы:\n");
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
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
            A[i][j] = temp;
        }
    }
    printf("Исходная матрица A:\n");
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }
    int flag;
    for (int j = 1; j <= m; j++) {
        flag = 0;
        for (int i = 1; i <= n; i++) {
            if (A[i][j] == 0) {
                flag = 1;
                break;
            }
        }
        if (!flag) {
            for (int p = j; p < m; p++) {
                for (int i = 1; i <= n; i++) {
                    A[i][p] = A[i][p + 1];
                }
            }
            m--;
            j--;
        }
    }

    if (m == 0) {
        printf("Все столбцы матрицы не содержали ни одного нуля. Матрица удалена.\n");
        return 0;
    }

    printf("Преобразованная матрица A:\n");
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }
}