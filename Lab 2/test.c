#include <stdio.h>
#define lmax 100

int main()
{
    int m, n, Q[lmax][lmax];
    char check;

    do {
        printf("Введите количество строк (m): ");
        while(getchar() != '\n');
        scanf("%d", &m);
    } while (getchar() != '\n' || m <= 0 || m > lmax);
}