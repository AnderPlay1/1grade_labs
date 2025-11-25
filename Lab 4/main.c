// Дано k литерных строк. Каждая строка содержит латинские и русские буквы, цифры, а также все возможные разделители. Требуется:

// I.	Выделить из каждой строки и напечатать подстроки:
// 1.	заключенные в фигурные скобки;
// ПРИМЕЧАНИЕ. Пробел считать буквой. Каждую подстроку печатать с новой строки. Пустые подстроки не выделять и не печатать.

// II.	Среди выделенных подстрок найти подстроку (если таких подстрок несколько, выбирается первая из них):
// 3.	содержащую цифры и круглые скобки
// ПРИМЕЧАНИЕ. Если таких подстрок несколько, выбирается первая из них.

// III.	Преобразовать исходную строку, которой принадлежит найденная подстрока, следующим образом:
// 11.	вставить три звездочки перед последней цифрой.
// ЗАМЕЧАНИЕ. Все части оформить как подпрограммы в одной программе. Ввод данных, анализ существования результатов и их вывод оформить в главной программе. Если выполнение какого-либо задания невозможно, то необходимо вывести соответствующее сообщение. 

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define kmax 100
#define maxlen 81


// I. Выделение подстрок в фигурных скобках
int extractBraces(const char *src, char results[][maxlen], int *count) {
    int i = 0, n = strlen(src);
    int found = 0;

    while (i < n) {
        if (src[i] == '{') {
            int j = i + 1;
            while (j < n && src[j] != '}') j++;

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

// II. Проверка, содержит ли подстрока цифры и круглые скобки
int hasDigitsAndParentheses(const char *s) {
    int digit = 0, brace = 0;
    for (int i = 0; s[i]; i++) {
        if (isdigit(s[i])) digit = 1;
        if (s[i] == '(' || s[i] == ')') brace = 1;
    }
    if (digit && brace)
        return 1;
    return 0;
}

// III. Вставить "***" перед последней цифрой строки
int insertStars(char *s) {
    int pos = -1;
    for (int i = 0; s[i]; i++)
        if (isdigit(s[i])) 
            pos = i;

    if (pos == -1) return 0; 

    char temp[maxlen];
    strcpy(temp, s + pos); 

    s[pos] = '\0';          
    strcat(s, "***");       
    strcat(s, temp);        

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
        extractBraces(lines[i], substrings, &total);
        for (int j = startCount; j < total; j++)
            owner[j] = i;
    }

    if (total == 0) {
        printf("There are no non-empty substrings in curly braces.\n");
        return 0;
    }

    printf("\nExtracted substrings:\n");
    for (int i = 0; i < total; i++)
        printf("%s\n", substrings[i]);

    // II. Находим первую подстроку, содержащую цифры и круглые скобки
    int target = -1;
    for (int i = 0; i < total; i++) {
        if (hasDigitsAndParentheses(substrings[i])) {
            target = i;
            break;
        }
    }

    if (target == -1) {
        printf("\nThere is no substring containing numbers and parentheses.\n");
        return 0;
    }
    printf("Substring was found: \n%s\n", substrings[target]);

    // III. Преобразуем исходную строку
    int lineIndex = owner[target];
    printf("\nConverted string:\n%s\n", lines[lineIndex]);

    return 0;
}
