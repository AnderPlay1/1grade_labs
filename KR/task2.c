// Дана символьная строка. Обращаться к символам по указателю.
// Ввод данных, анализ существования и вывод результата оформить в
// главной функции, вычисления – в отдельной функции с
// параметрами. Удалить все цифры, кратные 3, путем сдвига.


#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define lmax 81

void remove_from_str(char *str) {
    char *s1 = str, *s2 = str;
    
    while (*s1 != '\0') {
        if (!isdigit(*s1) || (*s1 - '0') % 3 != 0) {
            *s2 = *s1; 
            s2++;       
        }
        s1++; 
    }
    *s2 = '\0';
}

int main() {
    char str[lmax];
    printf("Insert string: \n");
    fgets(str, sizeof(str), stdin);
    if (strlen(str) < 2) {
        printf("String is empty");
        return 0;
    }
    remove_from_str(str);
    printf("Result: \n%s\n", str);
    
    return 0;
}
