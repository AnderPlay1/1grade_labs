#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


#define fname "numbers.txt"

// I.	Создать  файл для хранения действительных чисел, вводимых с клавиатуры. Прочитать этот файл и вычислить:
// 2.	сумму положительных чисел;

int sumPositive(double *res) {
    FILE *f = fopen(fname, "r");
    if (!f) return 0;

    double x, sum = 0;
    int found = 0;

    while (fscanf(f, "%lf", &x) == 1) {
        if (x > 0) {
            sum += x;
            found = 1;
        }
    }

    fclose(f);

    if (found) *res = sum;
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

    if (!sumPositive(&result)) {
        printf("\nNo positive numbers in file.\n");
        return 0;
    }

    printf("\nSum of positive numbers: %lf\n", result);

    return 0;
}
