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
 * Program untuk mencari palindrom menggunakan Stack
 * Struktur Data 2021
*/
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/* Struktur Node */

typedef struct stackNode_t {
    char data;
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
void stack_push(Stack *stack, char value);
void stack_pop(Stack *stack);
void stringEdit(char* string, char* temp);
void check(Stack *stack, char* string);
char stack_top(Stack *stack);
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

void stack_push(Stack *stack, char value) 
{
    StackNode *newNode = (StackNode*) malloc(sizeof(StackNode));
    if (newNode) {
        stack->_size++;
        newNode->data = value;
        
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

char stack_top(Stack *stack) 
{
    if (!stack_isEmpty(stack)) 
        return stack->_top->data;
    return 0;
}

unsigned stack_size(Stack *stack) {
    return stack->_size;
}

void stringEdit(char string[], char temp[]) {
	int i, j=0;
	for (i=0;i<strlen(string);i++){
		if (string[i]>=65 && string[i]<=90) {
			temp[j++]=string[i]+32;
		}
		else if (string[i]>=97 && string[i]<=122) {
			temp[j++]=string[i];
		}
		else continue;
	}
	return ;
}

void check(Stack *stack, char* string) {
	int i, len=strlen(string);
	for (i=0;i<len/2;i++){
		stack_push(stack, string[i]);
	}
	if (len%2==1)i++;
	for (i;i<len;i++){
		if (stack_top(stack)!=string[i]){
			printf("mahal, eh bukan palindrome eh\n");
			return;
		}
		stack_pop(stack);
	}
	printf("palindrome\n");
	return;
}

int main(int argc, char const *argv[])
{
    // Buat objek Stack
    Stack myStack;

    // PENTING! Jangan lupa diinisialisasi
    stack_init(&myStack);
	
	char palindrome[100]="", temp[100]="";
	gets(palindrome);
	stringEdit(palindrome, temp);
	
	check(&myStack, temp);
    return 0;
}
