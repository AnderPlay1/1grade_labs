//2)	Сформировать новый массив, содержащий все различные элементы массива A по одному разу. 
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

int calculate(int A[], int B[], int n, int k) {
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < k; j++) {
            if (A[i] == B[j]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            B[k] = A[i];
            k++;
        }
    }
    return k;
}

void count_duplicates(int A[], int n) {
    printf("Element counts:\n");
    int processed = 0;
    
    for (int i = 0; i < n; i++) {
        int count = 0;
        processed = 0;
        for (int j = 0; j < i; j++) {
            if (A[i] == A[j]) {
                processed = 1;
                continue;
            }
        }
        if(processed)
            continue;
        for (int j = i + 1; j < n; j++){
            if (A[i] == A[j]) 
                count++;
        }           
        printf("Element %d repeats %d time(s)\n", A[i], count);
    }
}

int main() {
    int A[lmax], B[lmax], n, m, V, k = 0;
    char check;
    printf("Lab work #3, task #3\n");
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

    insert_array(A, n);
    printf("Original array A: \n");
    print_array(A, n);
    count_duplicates(A, n);
    k = calculate(A, B, n, k);
    printf("Array B: \n");
    print_array(B, k);
    return 0;
}
