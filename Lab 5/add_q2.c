// II.	Создать связанный список для хранения целых чисел. Число записей неизвестно, но можно ввести число, являющееся признаком окончания ввода данных. Для четных номеров вариантов организовать очередь, а для нечетных – стек. 
// Для исходного списка решить следующую задачу:
// 4)	удалить из списка элементы, большие среднего арифметического;
// Для полученного списка решить следующую задачу:
// 6)	упорядочить по возрастанию методом "пузырька" элементы списка, расположенные после первого элемента равного Z (число Z задано);

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct node {
    int x;
    struct node *next;
} node;

node* pushQueue(node *head, int x) {
    node *p = (node*)malloc(sizeof(node));
    p->x = x;
    p->next = NULL;

    if (!head) return p;

    node *q = head;
    while (q->next) q = q->next;
    q->next = p;

    return head;
}

void printList(node *head) {
    node *p = head;
    while (p) {
        printf("%d ", p->x);
        p = p->next;
    }
    printf("\n");
}

int deleteElements(node *head) {
    node *p = head;
    double avg = 0;
    int flag = 0, cnt = 0;
    while (p) {
        avg += p->x;
        cnt++;
        p = p->next;
    }
    if (cnt == 0) return 0;
    avg /= cnt;
    p = head;
    node *prev = NULL;
    while (p) {
        if (p->x > avg) {
            node *toDelete = p;
            if (prev) {
                prev->next = p->next;
                p = prev->next;
            } else {
                head = p->next;
                p = head;
            }
            free(toDelete);
            flag = 1;
        } 
        else {
            prev = p;
            p = p->next;
        }
    }
    return flag;
}

int bubbleSortBeforeZ(node *head, int Z) {
    if (!head) return 0;

    node *start = head;

    while (start && start->x != Z)
        start = start->next;

    if (!start) return 0;

    int swapped = 1;
    while (swapped) {
        swapped = 0;
        node *p = start;

        while (p->next) {
            if (p->x > p->next->x) {
                int t = p->x;
                p->x = p->next->x;
                p->next->x = t;
                swapped = 1;
            }
            p = p->next;
        }
    }
    return 1;
}


int main() {
    printf("Lab Work #5. Task 2\n");
    node *head = NULL;
    int x;
    char check;

    printf("\nInput integers (-999 ends input):\n");
    
    while (1) {
        do {
            scanf("%d", &x);
            check = getchar();
            if (check != '\n') {
                printf("Invalid input.\n");
                x = INT_MAX;
                while (check != '\n' && check != EOF) {
                        check = getchar();
                }
            }
        } while (check != '\n' || x == INT_MAX);

        if (x == -999) break;
        head = pushQueue(head, x);
    }

    int Z;
    printf("\nEnter Z: ");
    do {
            scanf("%d", &Z);
        check = getchar();
        if (check != '\n') {
            printf("Invalid input.\n");
            Z = INT_MAX;
            while (check != '\n' && check != EOF) {
                    check = getchar();
            }
        }
    } while (check != '\n' || Z == INT_MAX);

    printf("\nInitial list:\n");
    printList(head);

    if (deleteElements(head)) {
        printf("\nNew list:\n");
        printList(head);
    }
    else 
        printf("No positive elements found in the list.\n");

    if (bubbleSortBeforeZ(head, Z)) {
        printf("\nList after sorting elements after first %d:\n", Z);
        printList(head);
    }
    else {
        printf("Element %d not found in the list.\n", Z);
    }

    return 0;
}
