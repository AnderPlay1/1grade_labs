#include <stdio.h>
#include <math.h>
#define lmax 100

int main() {
	int n, i, k = 0, minIndx = 0;
	double x, h, a, R[lmax];
    printf("Лабораторная работа №1\n");       

    do {
        printf("Введите длину массива R от 1 до %d:\n", lmax);
        scanf("%d", &n);
        while(getchar() != '\n');
    } while (n < 1 || n > lmax);
    
    printf("Введите x, h, a:\n");
    scanf("%lf %lf %lf", &x, &h, &a);

	// I. Вычисление массива
    printf("1. Массив R[1,n]: ");
	for (i = 1; i <= n; i++) {
		R[i] = 2.5 * sin(a * x + i * i * h);
        printf("%8.4lf", R[i]);
	}

	// II. Удаление элементов |R[i]| < 0.7 путем сдвига
	int j = 1;
	for (i = 1; i <= n; i++) {
		if (fabs(R[i]) >= 0.7) {
			R[j] = R[i];
            j++;
		}
	}

	k = j - 1;
	if (k == 0) {
		printf("\n2. Все элементы удалены, массив пуст\n");
		printf("3. Нет среднего значения\n");
	}
    else {
        if (k == n) printf("\n2. Нет элементов, удовлетворяющих условию") ;
        else {
            printf("\n2. Массив R после удаления содержит %d элемент(-а/-ов): ", k);
            for (i = 1; i <= k; i++) {
                printf("%8.4lf ", R[i]);
            }
        }

        // III. Поиск последнего минимального элемента
        double min = R[1];
        for (i = 1; i <= k; i++) {
            if (R[i] <= min) {
                min = R[i];
                minIndx = i;
            }
        }

        // Подсчет среднего арифметического до последнего минимального включительно
        double sum = 0;
        for (i = 1; i <= minIndx; i++) {
            sum += R[i];
        }
        
        double avg = sum / minIndx;
        printf("\n3. Среднее арифметическое до последнего минимума включительно: %8.4lf\n", avg);
        return 0;
    }
}
