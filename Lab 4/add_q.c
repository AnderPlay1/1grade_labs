// Дано k литерных строк. Каждая строка содержит латинские и русские буквы, цифры, а также все возможные разделители. Требуется:
// I.	Выделить из каждой строки и напечатать подстроки:
// 3.	ограниченные с обеих сторон одной или несколькими звездочками;

// II.	Среди выделенных подстрок найти подстроку (если таких подстрок несколько, выбирается первая из них):
// 4.	содержащую максимальное (но не нулевое) число цифр;

// III.	Преобразовать исходную строку, которой принадлежит найденная подстрока, следующим образом:
// 2.	удалить путем сдвига все символы, отличные от русских букв;


#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define kmax 100
#define maxlen 81


int extractStars(const char *src, char results[][maxlen], int *count) {
    int i = 0, n = strlen(src);
    int found = 0;

    while (i < n) {
        if (src[i] == '*') {
            while (src[i] == '*') i++;
            int j = i;
            while (j < n && src[j] != '*') j++;

            if (j < n && j > i + 1) {  
                int len = j - i - 1;
                strncpy(results[*count], src + i + 1, len);
                results[*count][len] = '\0';
                (*count)++;
                found = 1;
            }
            i = j;
        }
        i++;
    }
    return found;
}

// 4.	содержащую максимальное (но не нулевое) число цифр;
int cntDigits(const char *s) {
    int cnt_digits = 0;
    for (int i = 0; s[i]; i++) {
        if (isdigit(s[i])) cnt_digits++;
    }
    return cnt_digits;
}

// 2.	удалить путем сдвига все символы, отличные от русских букв;
int deleteNotRus(char *s) {
    int pos = -1, j = 0;
    int len = strlen(s);
    for (int i = 0; s[i]; i++)
        if (isalpha(s[i])) {      
            s[j] = s[i];
            j++;
        }
    s[j - 1] = '\0';
    return 1;
}


int main() {
    int k;
    char check;
    printf("Lab work #4\n");
    do {
        printf("Enter the number of strings (from 1 to %d): ", kmax);
        scanf("%d", &k);
        check = getchar();
        if (check != '\n' || k <= 0) {
            printf("Invalid input (n must be a natural number).\n");
            k = 0;
            while (check != '\n' && check != EOF) {
                    check = getchar();
            }
        }
    } while (k <= 0 || k > kmax);

    char lines[kmax][maxlen];
    printf("Insert %d lines:\n", k);
    for (int i = 0; i < k; i++) {
        fgets(lines[i], maxlen, stdin);
        lines[i][strcspn(lines[i], "\n")] = '\0';
    }

    char substrings[kmax * 100][maxlen];
    int total = 0;
    int owner[kmax * 100]; 

    // I. Извлекаем подстроки
    for (int i = 0; i < k; i++) {
        int startCount = total;
        extractStars(lines[i], substrings, &total);
        for (int j = startCount; j < total; j++)
            owner[j] = i;
    }

    if (total == 0) {
        printf("There are no non-empty substrings in curly braces.\n");
        return 0;
    }

    printf("\nExtracted substrings(count: %d):\n", total);
    for (int i = 0; i < total; i++)
        printf("%s\n", substrings[i]);

    // II. Находим первую подстроку, содержащую цифры и круглые скобки
    int target = -1, max = 0;
    for (int i = 0; i < total; i++) {
        int cnt = cntDigits(substrings[i]);
        if (max < cnt) {
            target = i;
            max = cnt;
        }
    }

    if (target == -1) {
        printf("\nThere is no substring containing numbers and parentheses.\n");
        return 0;
    }
    printf("Substring was found: \n%s\n", substrings[target]);
    deleteNotRus(lines[target]);
    // III. Преобразуем исходную строку
    int lineIndex = owner[target];
    printf("\nConverted string:\n%s\n", lines[lineIndex]);

    return 0;
}
