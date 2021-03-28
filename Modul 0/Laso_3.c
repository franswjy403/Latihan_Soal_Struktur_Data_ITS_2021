/**
 * Implementasi ADT SInglyList (Singly Linked List)
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
 * Modifikasi data yang disimpan menjadi string untuk keperluan latihan modul-0
 * Struktur Data 2021
*/
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/* Struktur Node */

typedef struct snode_t {
    char data[100];
    struct snode_t *next;
} SListNode;

/* Struktur ADT SinglyList */

typedef struct slist_t {
    unsigned _size;
    SListNode *_head;
} SinglyList;

/* DAFTAR FUNGSI YANG TERSEDIA */

void slist_init(SinglyList *list);
bool slist_isEmpty(SinglyList *list);
void slist_pushFront(SinglyList *list, char* value);
void slist_popFront(SinglyList *list);
void slist_pushBack(SinglyList *list, char* value);
void slist_popBack(SinglyList *list);
void slist_insertAt(SinglyList *list, int index, char* value);
void slist_removeAt(SinglyList *list, int index);
void slist_remove(SinglyList *list, char* value);
void forEachElement(SinglyList *list, void (*f)(SListNode*) );
void print (SListNode*);
char*  slist_front(SinglyList *list);
char* slist_back(SinglyList *list);
char*  slist_getAt(SinglyList *list, int index);

/* Function definition below */

void slist_init(SinglyList *list) 
{
    list->_head = NULL;
    list->_size = 0;
}

bool slist_isEmpty(SinglyList *list) {
    return (list->_head == NULL);
}

void slist_pushFront(SinglyList *list, char* value) 
{
    SListNode *newNode = (SListNode*) malloc(sizeof(SListNode));
    if (newNode) {
        list->_size++;
        strcpy(newNode->data, value);

        if (slist_isEmpty(list)) newNode->next = NULL;
        else newNode->next = list->_head;
        list->_head = newNode;
    }
}

void slist_popFront(SinglyList *list)
{
    if (!slist_isEmpty(list)) {
        SListNode *temp = list->_head;
        list->_head = list->_head->next;
        free(temp);
        list->_size--;
    }
}

void slist_pushBack(SinglyList *list, char* value)
{
    SListNode *newNode = (SListNode*) malloc(sizeof(SListNode));
    if (newNode) {
        list->_size++;
        strcpy(newNode->data, value);
        newNode->next = NULL;
        
        if (slist_isEmpty(list)) 
            list->_head = newNode;
        else {
            SListNode *temp = list->_head;
            while (temp->next != NULL) 
                temp = temp->next;
            temp->next = newNode;
        }
    }
}

void slist_popBack(SinglyList *list)
{
    if (!slist_isEmpty(list)) {
        SListNode *nextNode = list->_head->next;
        SListNode *currNode = list->_head;

        if (currNode->next == NULL) {
            free(currNode);
            list->_head = NULL;
            return;
        }

        while (nextNode->next != NULL) {
            currNode = nextNode;
            nextNode = nextNode->next;
        }
        currNode->next = NULL;
        free(nextNode);
        list->_size--;
    }
}

void slist_insertAt(SinglyList *list, int index, char* value)
{
    /* Kasus apabila posisinya melebihi batas */
    if (slist_isEmpty(list) || index >= list->_size) {
        slist_pushBack(list, value);
        return;    
    }
    else if (index == 0 || index < 0) {
        slist_pushFront(list, value);
        return;
    }
    
    SListNode *newNode = (SListNode*) malloc(sizeof(SListNode));
    if (newNode) {
        SListNode *temp = list->_head;
        int _i = 0;
        while (temp->next != NULL && _i < index-1) {
            temp = temp->next;
            _i++;
        }
        strcpy(newNode->data, value);
        newNode->next = temp->next;
        temp->next = newNode;
        list->_size++;
    }
}

void slist_removeAt(SinglyList *list, int index)
{
    if (!slist_isEmpty(list)) {
        
        /* Kasus apabila posisinya melebihi batas */
        if (index >= list->_size) {
            slist_popBack(list);
            return;    
        }
        else if (index == 0 || index < 0) {
            slist_popFront(list);
            return;
        }
        
        SListNode *temp = list->_head;
        int _i = 0;
        while (temp->next != NULL && _i < index-1) {
            temp = temp->next;
            _i++;
        }
        SListNode *nextTo = temp->next->next;
        free(temp->next);
        temp->next = nextTo;
        list->_size--;
    }
}

void slist_remove(SinglyList *list, char* value)
{
    if (!slist_isEmpty(list)) {
        SListNode *temp, *prev;
        temp = list->_head;

        if (strcmp(temp->data, value) == 0) {
            slist_popFront(list);
            return;
        }
        while (temp != NULL && strcmp(temp->data, value) != 0) {
            prev = temp;
            temp = temp->next;
        }

        if (temp == NULL) return;
        prev->next = temp->next;
        free(temp);
        list->_size--;
    }
}

char* slist_front(SinglyList *list)
{
    if (!slist_isEmpty(list)) {
        return list->_head->data;
    }
    return NULL;
}

char* slist_back(SinglyList *list)
{
    if (!slist_isEmpty(list)) {
        SListNode *temp = list->_head;
        while (temp->next != NULL) 
            temp = temp->next;
        return temp->data;
    }
    return NULL;
}

char* slist_getAt(SinglyList *list, int index)
{
    if (!slist_isEmpty(list)) {
        SListNode *temp = list->_head;
        int _i = 0;
        while (temp->next != NULL && _i < index) {
            temp = temp->next;
            _i++;
        }
        return temp->data;
    }
    return NULL;
}

//Fungsi untuk mencetak elemen sebuah node
void print (SListNode *node) {
	printf("%s ", node->data);
	return;
}

//Fungsi untuk menunjuk setiap elemen link list kemudian mengoperasikannya dengan funsi tertentu
void forEachElement (SinglyList *list, void(*f)(SListNode*)) {
	if (slist_isEmpty(list)) {
		printf ("List kosong\n");
	}
	else {
		SListNode *temp = list->_head;
		while (temp->next != NULL) {
			(*f)(temp);
			temp = temp->next;
		}
		(*f)(temp);
	}
	return ;
}

int main(int argc, char const *argv[])
{
    // Buat objek SinglyList
    SinglyList myList;

    // PENTING! Jangan lupa diinisialisasi
    slist_init(&myList);

    // Gunakan operasi linked list
    slist_pushBack(&myList, "aku");
    slist_pushBack(&myList, "dia");
    slist_pushBack(&myList, "frans");
    slist_pushBack(&myList, "nata");

    slist_pushFront(&myList, "tiki");
    slist_pushFront(&myList, "lisa");
    slist_pushFront(&myList, "pikachu");
    slist_pushFront(&myList, "bdikz");

	forEachElement(&myList, print);
	printf("\n");
	
    slist_popBack(&myList);
    slist_popFront(&myList);
	
	forEachElement(&myList, print);
	printf("\n");
	
    slist_removeAt(&myList, 3);
	
	forEachElement(&myList, print);
    printf("\n");
	
    slist_insertAt(&myList, 1, "testing");
    slist_pushBack(&myList, "jason");
    
    forEachElement(&myList, print);
    printf("\n");
    
    slist_remove(&myList, "jason");
    
    forEachElement(&myList, print);
    printf("\n");
    
    printf("%s\n", slist_front(&myList));
    printf("%s\n", slist_back(&myList));
    printf("%s\n", slist_getAt(&myList, 3));
    
    puts("");
    return 0;
}
