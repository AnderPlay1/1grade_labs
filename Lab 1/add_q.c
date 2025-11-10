#include <stdio.h>
#include <math.h>
#define lmax 100

int main() {
	int n, i, k = 0, maxIndx = 1;
	double x, h, a, R[lmax];
    char c;
    printf("Лабораторная работа №1 (доп задание)\n");       

    do {
        printf("Введите длину массива R от 1 до %d:\n", lmax);
        scanf("%d%c", &n, &c);
        if (c != '\n' || n <= 0) {
            printf("Ошибка: введено не натуральное число.\n");
            n = lmax + 2;
        }
        while(getchar() != '\n');
    } while (n > lmax);
    
    printf("Введите x, h, a:\n");
    scanf("%lf %lf %lf", &x, &h, &a);

	// I. Вычисление массива
    printf("1. Массив R[1,n]: ");
	for (i = 1; i <= n; i++) {
		R[i] = 2.5 * sin(a * x + i * i * h);
        printf("%8.4lf", R[i]);
	}

    // II. Вычисление максимума
	double max = R[1];
    for (i = 1; i <= n; i++) {
        if (R[i] > max) {
            max = R[i];
            maxIndx = i;
        }
    }
    // Удаление
	for (i = maxIndx; i <= n; i++) {
        R[k + 1] = R[i];
        k += 1;
	}
    if (k == n) 
        printf("\n2. Первый максимум является крайним правым числом, поэтому изменения массива не произошло") ;
    else {
        printf("\n2. Массив R после удаления содержит %d элемент(-а/-ов): ", k);
        for (i = 1; i <= k; i++) {
            printf("%8.4lf ", R[i]);
        }
    }

    if (k == 1) {
        printf("\n3. Нет среднего");
        return 0;
    }

    double sum = 0;
    for (i = 1; i <= k; i++) {
        sum += R[i];
    }
    
    double avg = sum / k;
    printf("\n3. Среднее арифметическое после первого максимума: %8.4lf\n", avg);
    return 0;
}
