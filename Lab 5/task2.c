// II.	Создать связанный список для хранения целых чисел. Число записей неизвестно, но можно ввести число, являющееся признаком окончания ввода данных. Для четных номеров вариантов организовать очередь, а для нечетных – стек. 
// Для исходного списка решить следующую задачу:
// 6)	вставить заданное число A1 после каждого положительного элемента списка.
// Для полученного списка решить следующую задачу:
// 11)	упорядочить по возрастанию методом "пузырька" элементы списка, расположенные до первого четного элемента. 

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct node {
    int x;
    struct node *next;
} node;

node* pushStack(node *head, int x) {
    node *p = (node*)malloc(sizeof(node));
    p->x = x;
    p->next = head;
    return p;
}

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

int insertAfterPositive(node *head, int A1) {
    node *p = head;
    int flag = 0;
    while (p) {
        if (p->x > 0) {
            node *q = (node*)malloc(sizeof(node));
            q->x = A1;
            q->next = p->next;
            p->next = q;
            p = q->next;  
            flag = 1;        
        } 
        else {
            p = p->next;
        }
    }
    return flag;
}

void bubbleSortBeforeEven(node *head) {
    if (!head) return;

    node *stop = head;

    while (stop && stop->x % 2 != 0)
        stop = stop->next;

    if (stop == head) return; 

    int swapped = 1;
    while (swapped) {
        swapped = 0;
        node *p = head;

        while (p->next && p->next != stop) {
            if (p->x > p->next->x) {
                int t = p->x;
                p->x = p->next->x;
                p->next->x = t;
                swapped = 1;
            }
            p = p->next;
        }
    }
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

    int A1;
    printf("\nEnter A1: ");
    do {
            scanf("%d", &A1);
        check = getchar();
        if (check != '\n') {
            printf("Invalid input.\n");
            A1 = INT_MAX;
            while (check != '\n' && check != EOF) {
                    check = getchar();
            }
        }
    } while (check != '\n' || A1 == INT_MAX);

    printf("\nInitial list:\n");
    printList(head);

    if (insertAfterPositive(head, A1)) {
        printf("\nNew list:\n");
        printList(head);
    }
    else 
        printf("No positive elements found in the list.\n");

    bubbleSortBeforeEven(head);

    printf("\nSorted list:\n");
    printList(head);

    return 0;
}
