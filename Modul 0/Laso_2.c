/**
 * Implementasi ADT Dynamic Array
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
 * Penambahan insertAt dan removeAt untuk latihan soal 2 modul-0
 * Struktur Data 2021
*/
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
// Struktur ADT DynamicArray

typedef struct dynamicarr_t {
    int *_arr;
    unsigned _size, _capacity;
} DynamicArray;

// Prototipe fungsi

void dArray_init(DynamicArray *darray);
bool dArray_isEmpty(DynamicArray *darray);
void dArray_pushBack(DynamicArray *darray, int value);
void dArray_popBack(DynamicArray *darray);
int  dArray_back(DynamicArray *darray);
int  dArray_front(DynamicArray *darray);
void dArray_setAt(DynamicArray *darray, unsigned index, int value);
int  dArray_getAt(DynamicArray *darray, unsigned index);
void dArray_insertAt(DynamicArray *darray, unsigned index, int value);
void dArray_removeAt (DynamicArray *darray, unsigned index);

// Definisi fungsi

void dArray_init(DynamicArray *darray)
{
    darray->_capacity = 2u;
    darray->_size = 0u;
    darray->_arr = (int*) malloc(sizeof(int) * 2);
}

bool dArray_isEmpty(DynamicArray *darray) {
    return (darray->_size == 0);
}

void dArray_pushBack(DynamicArray *darray, int value)
{
    if (darray->_size + 1 > darray->_capacity) {
        unsigned it;
        darray->_capacity *= 2;
        int *newArr = (int*) malloc(sizeof(int) * darray->_capacity);

        for (it=0; it < darray->_size; ++it)
            newArr[it] = darray->_arr[it];
        
        int *oldArray = darray->_arr;
        darray->_arr = newArr;
        free(oldArray);
    }
    darray->_arr[darray->_size++] = value;
}

void dArray_popBack(DynamicArray *darray) {
    if (!dArray_isEmpty(darray)) darray->_size--;
    else return;
}

int dArray_back(DynamicArray *darray) {
    if (!dArray_isEmpty(darray))
        return darray->_arr[darray->_size-1];
    else return 0;
}

int dArray_front(DynamicArray *darray) {
    if (!dArray_isEmpty(darray))
        return darray->_arr[0];
    else return 0;
}

void dArray_setAt(
    DynamicArray *darray, unsigned index, int value)
{
    if (!dArray_isEmpty(darray)) {
        if (index >= darray->_size)
            darray->_arr[darray->_size-1] = value;
        else
            darray->_arr[index] = value;
    }
}

int dArray_getAt(DynamicArray *darray, unsigned index)
{
    if (!dArray_isEmpty(darray)) {
        if (index >= darray->_size)
            return darray->_arr[darray->_size-1];
        else
            return darray->_arr[index];
    }
}

void dArray_insertAt(DynamicArray *darray, unsigned index, int value) {
	if (dArray_isEmpty(darray) || index>=darray->_size) {
		dArray_pushBack(darray, value);
		return;
	}
	else {
		if (darray->_size + 1 > darray->_capacity) {
	        unsigned it;
	        darray->_capacity *= 2;
	        int *newArr = (int*) malloc(sizeof(int) * darray->_capacity);
	
	        for (it=0; it < darray->_size; ++it)
	            newArr[it] = darray->_arr[it];
	        
	        int *oldArray = darray->_arr;
	        darray->_arr = newArr;
	        free(oldArray);
	    }
	    int *tempArr = (int*) malloc(sizeof(int) * (darray->_size - index + 1));
	    unsigned i, it=0;
		for (i=index;i<darray->_size;i++){
			tempArr[it] = darray->_arr[i];
			it++;
		}
		darray->_arr[index] = value;
		memcpy(darray->_arr + index + 1, tempArr, sizeof(int) * it);
		free(tempArr);
	    darray->_size++;
	}
}

void dArray_removeAt (DynamicArray *darray, unsigned index) {
	if (dArray_isEmpty(darray)) return;
	else if (index >= darray->_size) dArray_popBack(darray);
	else {
		int *tempArr = (int*) malloc(sizeof(int) * (darray->_size - index + 1));
		unsigned i, it=0;
		for (i=index+1;i<darray->_size;i++){
			tempArr[it] = darray->_arr[i];
			it++;
		}
		memcpy(darray->_arr + index, tempArr, sizeof(int) * it);
		free(tempArr);
		darray->_size--;
	}
}
/* Gunakan ini untuk mempersingkat penulisan kode */

#define d_init dArray_init
#define d_isEmpty dArray_isEmpty
#define d_pushBack dArray_pushBack
#define d_popBack dArray_popBack
#define d_back dArray_back
#define d_front dArray_front
#define d_setAt dArray_setAt
#define d_getAt dArray_getAt

/* */

#include <stdio.h>

int main(int argc, char const *argv[])
{
    // Buat objek DynamicArray
    DynamicArray myArray;

    // PENTING! Jangan lupa diinisialisasi
    dArray_init(&myArray);

    // Operasi-operasi
    // myArray => [11, 14, 17, 23]
    dArray_pushBack(&myArray, 11);
    dArray_pushBack(&myArray, 14);
    dArray_pushBack(&myArray, 17);
    dArray_pushBack(&myArray, 23);
    // isi myArray => [11, 14, 17]
    dArray_popBack(&myArray);

    int i = 0;
    for (; i < myArray._size; ++i) {
        printf("%d ", dArray_getAt(&myArray, i));
    }
    
    printf("\n");
    dArray_insertAt(&myArray, 0, 34);
    dArray_insertAt(&myArray, 1, 44);
    dArray_insertAt(&myArray, 2, 64);
    dArray_insertAt(&myArray, 3, 24);
    dArray_insertAt(&myArray, 100, 14);
    
    printf("Dynamic Array setelah diinsert wave 1 :\n");
    i=0;
    for (; i < myArray._size; ++i) {
        printf("%d ", dArray_getAt(&myArray, i));
    }
    
    printf("\n");
    
    dArray_insertAt(&myArray, 11, 34);
    dArray_insertAt(&myArray, 12, 44);
    dArray_insertAt(&myArray, 15, 64);
    dArray_insertAt(&myArray, 18, 24);
    dArray_insertAt(&myArray, 2, 14);
    
    printf("Dynamic Array setelah diinsert wave 2 :\n");
    i=0;
    for (; i < myArray._size; ++i) {
        printf("%d ", dArray_getAt(&myArray, i));
    }
    
    printf("\n");
    
    dArray_removeAt(&myArray, 2);
    dArray_removeAt(&myArray, 100);
    dArray_removeAt(&myArray, 0);
    dArray_removeAt(&myArray, 7);
    
    printf("Dynamic Array setelah dihapus :\n");
    i=0;
    for (; i < myArray._size; ++i) {
        printf("%d ", dArray_getAt(&myArray, i));
    }
    
    printf("\n");
    
    printf("Dynamic Array popback :\n");
    while (!dArray_isEmpty(&myArray)) {
        printf("%d ", dArray_back(&myArray));
        dArray_popBack(&myArray);
    }
    printf("\n");
    
    return 0;
}
