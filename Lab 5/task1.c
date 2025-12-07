#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


#define fname "numbers.txt"
#define maxn 1000

// I.	Создать  файл для хранения действительных чисел, вводимых с клавиатуры. Прочитать этот файл и вычислить:
// 1.	минимальное положительное число;

int minPositive(double *res) {
    FILE *f = fopen(fname, "r");
    if (!f) return 0;

    double x, min = INT_MAX;
    int found = 0;

    while (fscanf(f, "%lf", &x) == 1) {
        if (x > 0 && x < min) {
            min = x;
            found = 1;
        }
    }

    fclose(f);

    if (found) *res = min;
    return found;
}

int file_write() {
    int len = 0;
    double x;
    char check;
    FILE *f = fopen(fname, "w");
    if (!f) {
        printf("Cannot create file.\n");
        return 0;
    }

    printf("Enter real numbers for file (q to stop):\n");

    while (1) {
        if (scanf("%lf", &x) == 1) {
            fprintf(f, "%lf ", x);
            len++;
        } else {
            check = getchar();
            if (check == 'q') break;
        }
    }

    fclose(f);
    return len;
}

int main() {
    printf("Lab work. Part I. Task 1\n");

    double result;
    int len = file_write();

    if (len == 0) {
        printf("No numbers were written to the file.\n");
        return 0;
    }

    if (!minPositive(&result)) {
        printf("\nNo positive numbers in file.\n");
        return 0;
    }

    printf("\nMinimal positive number: %lf\n", result);

    return 0;
}
