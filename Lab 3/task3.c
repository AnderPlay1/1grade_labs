#include <stdio.h>
#include <limits.h>
#include <math.h>
#define lmax 100

void insert_array(int A[], int n) {
    char check;
    int temp;
    printf("Enter the elements of array A:\n");
    for (int i = 0; i < n; i++) {
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
        A[i] = temp;
    }
}


void print_array(int A[], int n) {
    for (int i = 0; i < n; i++) 
        printf("%d ", A[i]);
    printf("\n");
}

int calculate(int A[], int n) {
    int is_found = 0, i = 0;
    while (i < n) {
        is_found = 0;
        for (int j = i + 1; j < n; j++) {
            if (A[i] == A[j]) {
                if (j != n - 1)
                    for (int g = j; g < n - 1; g++)
                        A[g] = A[g + 1];
                n--;
                is_found = 1;
            }
        }
        if (is_found) {
            for (int j = i; j < n - 1; j++)
                A[j] = A[j + 1];
            n--;
            i = 0;
        }
        else 
            i++;
    }
    return n;
}


int main() {
    int A[lmax][lmax], n, m, V;
    char check;
    printf("Lab work #3, task #2\n");
    do {
        printf("Enter the number of elements in array A (from 1 to %d): ", lmax);
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

    insert_array(*A, n);
    printf("Original array A: \n");
    print_array(*A, n);

    n = calculate(*A, n);
    printf("New n: %d\n", n);
    printf("New array: \n");
    print_array(*A, n);
    return 0;
}
