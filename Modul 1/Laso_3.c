/**
 * Implementasi ADT Stack (Stack menggunakan Linked List)
 * 
 * Dibuat dan ditulis oleh Bayu Laksana
 * -- tanggal 22 Januari 2019
 * Struktur Data 2020
 * Implementasi untuk bahasa C
 * 
 * !!NOTE!!
 * cara menggunakan lihat pada fungsi main()
 */
 
/*
 * Diupdate oleh Frans Wijaya
 * -- tanggal 28 Maret 2021
 * Stack penyimpan string untuk latihan soal 3 modul-1
 * Struktur Data 2021
*/
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/* Struktur Node */

typedef struct stackNode_t {
    char data[100];
    struct stackNode_t *next;
} StackNode;

/* Struktur ADT Stack */

typedef struct stack_t {
    StackNode *_top;
    unsigned _size;
} Stack;

/* Function prototype */

void stack_init(Stack *stack);
bool stack_isEmpty(Stack *stack);
void stack_push(Stack *stack, char* value);
void stack_pop(Stack *stack);
char* stack_top(Stack *stack);
unsigned stack_size(Stack *stack);

/* Function definition below */

void stack_init(Stack *stack) 
{
    stack->_size = 0;
    stack->_top = NULL;
}

bool stack_isEmpty(Stack *stack) {
    return (stack->_top == NULL);
}

void stack_push(Stack *stack, char* value) 
{
    StackNode *newNode = (StackNode*) malloc(sizeof(StackNode));
    if (newNode) {
        stack->_size++;
        strcpy(newNode->data, value);
        
        if (stack_isEmpty(stack)) newNode->next = NULL;
        else newNode->next = stack->_top;

        stack->_top = newNode;
    }
}

void stack_pop(Stack *stack) 
{
    if (!stack_isEmpty(stack)) {
        StackNode *temp = stack->_top;
        stack->_top = stack->_top->next;
        free(temp);
        stack->_size--;
    }
}

char* stack_top(Stack *stack) 
{
    if (!stack_isEmpty(stack)) 
        return stack->_top->data;
    return 0;
}

unsigned stack_size(Stack *stack) {
    return stack->_size;
}

int main(int argc, char const *argv[])
{
    // Buat objek Stack
    Stack myStack;

    // PENTING! Jangan lupa diinisialisasi
    stack_init(&myStack);

    // Operasi pada stack
    stack_push(&myStack, "Struktur Data");
    stack_push(&myStack, "2021");
    stack_push(&myStack, "Stack");

    // cetak isi stack
    while (!stack_isEmpty(&myStack)) {
        printf("%s ", stack_top(&myStack));
        stack_pop(&myStack);
    }
    puts("");
    return 0;
}
