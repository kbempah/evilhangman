#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"
#include "generic_vector.h"

struct generic_vector
{
	int size;
	int capacity;
	ITEM* data;
	Status (*item_assignment)(ITEM* phLeft, ITEM hRight);
	void (*item_destroy)(ITEM* phItem);
};
typedef struct generic_vector Generic_vector;

GENERIC_VECTOR generic_vector_init_default(Status (*item_assignment)(ITEM* phLeft, ITEM hRight),void (*item_destroy)(ITEM* phItem))
{
	Generic_vector* pVector = (Generic_vector*)malloc(sizeof(Generic_vector));
    
    if (pVector != NULL) {
		pVector->size = 0;
		pVector->capacity = 1;
		pVector->data = (ITEM*)malloc(sizeof(ITEM) * pVector->capacity);

        if (pVector->data == NULL) {
			free(pVector);
			return NULL;
		}

		for (int i = 0; i < pVector->capacity; i++)
			pVector->data[i] = NULL;
        
        pVector->item_assignment = item_assignment;
        pVector->item_destroy = item_destroy;
	}
	
	return pVector;
}

Status generic_vector_push_back(GENERIC_VECTOR hVector, ITEM hItem)
{
	Generic_vector* pVector = (Generic_vector*)hVector;
    
	if (pVector->size >= pVector->capacity)
	{
		ITEM* temp = (ITEM*)malloc(sizeof(ITEM) * pVector->capacity * 2);

		if (temp == NULL)
			return FAILURE;

		for (int i = 0; i < pVector->size; i++)
			temp[i] = pVector->data[i];
		
		for (int i = pVector->size; i < (pVector->capacity * 2); i++)
			temp[i] = NULL;

		free(pVector->data);
		pVector->data = temp;
		pVector->capacity *= 2;
	}
	pVector->item_assignment(&(pVector->data[pVector->size]), hItem);

	if (pVector->data[pVector->size] == NULL)
		return FAILURE;

	pVector->size++;
	return SUCCESS;
}

Status generic_vector_pop_back(GENERIC_VECTOR hVector)
{
    Generic_vector* pVector = (Generic_vector*)hVector;

    if (generic_vector_is_empty(hVector))
        return FAILURE;

    pVector->item_destroy(&(pVector->data[pVector->size - 1]));
    pVector->size--;
    
    return SUCCESS;
}

int generic_vector_get_size(GENERIC_VECTOR hVector)
{
	Generic_vector* pVector = (Generic_vector*)hVector;
	return pVector->size;
}

int generic_vector_get_capacity(GENERIC_VECTOR hVector)
{
	Generic_vector* pVector = (Generic_vector*)hVector;
	return pVector->capacity;
}

ITEM* generic_vector_at(GENERIC_VECTOR hVector, int index)
{
	Generic_vector* pVector = (Generic_vector*)hVector;

	if (index < 0 || index >= pVector->size)
		return NULL;

	return pVector->data + index;
}

Boolean generic_vector_is_empty(GENERIC_VECTOR hVector)
{
    Generic_vector* pVector = (Generic_vector*)hVector;
    
    return (pVector->size <= 0) ? TRUE : FALSE;
}

void generic_vector_destroy(GENERIC_VECTOR* phVector)
{
	Generic_vector* pVector = (Generic_vector*)*phVector;

	for (int i = 0; i < pVector->size; i++)
		pVector->item_destroy(&(pVector->data[i]));

	free(pVector->data);
	free(pVector);
	*phVector = NULL;
}

