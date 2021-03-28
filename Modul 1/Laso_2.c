/**
 * Implementasi ADT PriorityQueue menggunakan Linked List
 * [default: minimum priority]
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
 * Pembuatan Program Klinik TC untuk latihan soal 2 modul-1
 * Struktur Data 2021
*/
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
/* Struktur Node */

typedef struct pqueueNode_t {
    int data;
    int urgency;
    struct pqueueNode_t *next;
} PQueueNode;

/* Struktur ADT PriorityQueue menggunakan Linked List */

// Prioritas default: nilai minimum
typedef struct pqueue_t {
    PQueueNode *_top;
    unsigned _size;
} PriorityQueue;

/* Function prototype */

void pqueue_init(PriorityQueue *pqueue);
bool pqueue_isEmpty(PriorityQueue *pqueue);
void pqueue_push(PriorityQueue *pqueue, int value, int x);
void pqueue_pop(PriorityQueue *pqueue);
int  pqueue_top(PriorityQueue *pqueue);

/* Function definition below */

void pqueue_init(PriorityQueue *pqueue)
{
    pqueue->_top = NULL;
    pqueue->_size = 0;
}

bool pqueue_isEmpty(PriorityQueue *pqueue) {
    return (pqueue->_top == NULL);
}

void pqueue_push(PriorityQueue *pqueue, int value, int x)
{
    PQueueNode *temp = pqueue->_top;
    PQueueNode *newNode = \
        (PQueueNode*) malloc (sizeof(PQueueNode));
    newNode->data = value;
    newNode->urgency = x;
    newNode->next = NULL;

    if (pqueue_isEmpty(pqueue)) {
        pqueue->_top = newNode;
        return;
    }

    if (x > pqueue->_top->urgency) {
        newNode->next = pqueue->_top;
        pqueue->_top = newNode;
    }
    else {
        while ( temp->next != NULL && 
                temp->next->urgency > x)
            temp = temp->next;
        newNode->next = temp->next;
        temp->next = newNode;
    }
}

void pqueue_pop(PriorityQueue *pqueue)
{
    if (!pqueue_isEmpty(pqueue)) {
        PQueueNode *temp = pqueue->_top;
        pqueue->_top = pqueue->_top->next;
        free(temp);
    }
}

int pqueue_top(PriorityQueue *pqueue) {
    if (!pqueue_isEmpty(pqueue))
        return pqueue->_top->data;
    else return 0;
}

int main(int argc, char const *argv[])
{
    // Buat objek PriorityQueue
    PriorityQueue myPque;

    // PENTING! Jangan lupa diinisialisasi
    pqueue_init(&myPque);

	char string[100];
	int jml, id, x, i;
    scanf("%d", &jml);
    for (i=0;i<jml;i++){
    	getchar();
    	scanf("%s", &string);
    	if (strcmp(string,"MASUK")==0) {
    		scanf("%d %d", &id, &x);
    		pqueue_push(&myPque, id, x);
		}
		else {
			if (pqueue_isEmpty(&myPque)) {
				printf("HORE\n");
				continue;
			}
			printf("%d\n", pqueue_top(&myPque));
			pqueue_pop(&myPque);
		}
	}
    return 0;
}
