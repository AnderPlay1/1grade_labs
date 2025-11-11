#include <stdio.h>
#include <limits.h>

float calculate_function(float x1, float x2, float x3, float y1, float y2, float y3) {
    float x;
    int ret;
    do {
        printf("Insert value of point x (It must belong to the segment [x1; x3]): \n");
        ret = scanf("%f", &x);
        while (getchar() != '\n'); 
    } while (ret != 1);

    float result;
    if (x < x2) {
        result = y1 + (x - x1) * (y2 - y1) / (x2 - x1);
    } else if (x < x3) {
        result = y2 + (x - x2) * (y3 - y2) / (x3 - x2);
    } else {
        result = y3;
    }

    printf("Approximate value f(%.2f) = %.2f \n", x, result);
    return result;
}

void input_vars(float *x1, float *x2, float *x3, float *y1, float *y2, float *y3) {
    int ret;
    do {
        printf("Enter the real variable x1: \n");
        ret = scanf("%f", x1);
        while (getchar() != '\n'); 
    } while (ret != 1);

    do {
        printf("Enter the real variable x2: \n");
        ret = scanf("%f", x2);
        while (getchar() != '\n'); 
    } while (ret != 1);

    do {
        printf("Enter the real variable x3: \n");
        ret = scanf("%f", x3);
        while (getchar() != '\n'); 
    } while (ret != 1);

    do {
        printf("Enter the real variable y1: \n");
        ret = scanf("%f", y1);
        while (getchar() != '\n'); 
    } while (ret != 1);

    do {
        printf("Enter the real variable y2: \n");
        ret = scanf("%f", y2);
        while (getchar() != '\n');
    } while (ret != 1);

    do {
        printf("Enter the real variable y3: \n");
        ret = scanf("%f", y3);
        while (getchar() != '\n'); 
    } while (ret != 1);
}

int main() {
    float x1, x2, x3, y1, y2, y3;
    printf("Лабораторная работа №3, задача №2\n");
    input_vars(&x1, &x2, &x3, &y1, &y2, &y3);
    calculate_function(x1, x2, x3, y1, y2, y3);
    return 0;
}