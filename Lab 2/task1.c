#include <stdio.h>
#define lmax 100

int main()
{
    int m, n, Q[lmax][lmax];

    do{
        printf("Введите количество строк (m): ");
        if (scanf("%d", &m) != 1 || m <= 0)
        {
            printf("Некорректный ввод m. Должно быть натуральное число.\n");
        }
    } while (m <= 0 || m > lmax);
    do
    {
        printf("Введите кличество столбцов (n): ");
        if (scanf("%d", &n) != 1 || n <= 0)
        {
            printf("Invalid input for n. Must be a natural number.\n");
        }
    } while (n <= 0 || n > lmax);

    printf("Enter matrix elements:\n");
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (scanf("%d", &Q[i][j]) != 1)
            {
                printf("Invalid input. Matrix elements must be integers.\n");
                return 1;
            }
        }
    }

    printf("Matrix entered successfully.\n");
    return 0;
 }