#include <stdio.h>
#include <limits.h>
#define lmax 100

/*Для каждого элемента массива поменять порядок следования цифр на
обратный.*/

int main() {
    int n, A[lmax];
    char check;
    printf("Лабораторная работа №2, дополнительная задача №2\n");
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
    int temp;
    printf("Введите элементы массива A:\n");
    for (int i = 1; i <= n; i++) {   
        do {
            scanf("%d", &temp);
            check = getchar();
            if (check != '\n' || temp <= 0) {
                printf("Некорректный ввод (элемент должен быть натуральным).\n");
                temp = INT_MAX;
                while (check != '\n' && check != EOF) {
                        check = getchar();
                }
            }
        } while (check != '\n' || temp == INT_MAX);
        A[i] = temp;
    }

    int B[lmax];
    for (int i = 1; i <= n; i++) {
        int rev = 0, x = A[i];
        while (x > 0) {
            rev = rev * 10 + (x % 10);
            x /= 10;
        }
        B[i] = rev;
    }
    printf("Исходный массив A:\n");
    for (int i = 1; i <= n; i++) 
        printf("%d ", A[i]);
    
    printf("\nПреобразованный массив B:\n");
    for (int i = 1; i <= n; i++) 
        printf("%d ", B[i]);
    return 0;
}
