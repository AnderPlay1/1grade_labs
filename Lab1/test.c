#include <stdio.h>

int main() {
    int n;
    char c;

    printf("Введите натуральное число: ");
    scanf("%d%c", &n, &c);
    if (c != '\n' || n <= 0) {
        printf("Ошибка: введено не натуральное число.\n");
    } else {
        printf("Введено натуральное число: %d\n", n);
    }

    return 0;
}