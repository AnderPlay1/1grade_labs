#include <stdio.h>
#include <limits.h>
#include <math.h>
#define lmax 100

//O = min max|A[i][j]|
void insert_matrix(int A[][lmax], int n, int m) {
    char check;
    int temp;
    printf("Enter the elements of matrix A:\n");
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            do {
                scanf("%d", &temp);
                check = getchar();
                if (check != '\n') {
                    printf("Invalid input.\n");
                    temp = INT_MAX;
                    while (check != '\n' && check != EOF) {
                            check = getchar();
                    }
                }
            } while (check != '\n' || temp == INT_MAX);
            A[i][j] = temp;
        }
    }
}

void print_matrix(int A[][lmax], int n, int m) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }
}

int calculate(int A[][lmax], int n, int m) {
    int min, max;
    min = INT_MAX;
    for (int i = 1; i <= n; i++) {
        max = A[i][1];   
        for (int j = 1; j <= m; j++)
            if (abs(A[i][j]) > abs(max)) 
                max = A[i][j];

        if (max < min)
            min = max;
    }
    return min;
}


int main() {
    int A[lmax][lmax], n, m, V;
    char check;
    printf("Lab work #3, task #2\n");
    do {
        printf("Enter the number of rows in matrix A (from 1 to %d): ", lmax);
        scanf("%d", &n);
        check = getchar();
        if (check != '\n' || n <= 0) {
            printf("Invalid input (n must be a natural number).\n");
            n = 0;
            while (check != '\n' && check != EOF) {
                    check = getchar();
            }
        }
    } while (n <= 0 || n > lmax);

    do {
        printf("Enter the number of columns in matrix A (from 1 to %d): ", lmax);
        scanf("%d", &m);
        check = getchar();
        if (check != '\n' || m <= 0) {
            printf("Invalid input (m must be a natural number).\n");
            m = 0;
            while (check != '\n' && check != EOF) {
                    check = getchar();
            }
        }
    } while (m <= 0 || m > lmax);
    insert_matrix(A, n, m);
    printf("Original matrix A: \n");
    print_matrix(A, n, m);
    V = calculate(A, n, m);
    printf("Your desired value V = %d \n", V);
    return 0;
}