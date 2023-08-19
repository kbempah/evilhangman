#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "my_string.h"

typedef struct {
	int size;
	int capacity;
	char* data;
} My_string;

MY_STRING my_string_init_default(void)
{
	My_string* pString = (My_string*)malloc(sizeof(My_string));
    
	if (pString != NULL) {
		pString->size = 0;
		pString->capacity = 7;
		pString->data = (char*)malloc(pString->capacity * sizeof(char));
        
		if (pString->data == NULL) {
			free(pString);
			return NULL;
		}
	}

	return (MY_STRING)pString;
}

MY_STRING my_string_init_c_string(const char* c_string) {
	My_string* pString = (My_string*)malloc(sizeof(My_string));

	if (pString != NULL) {
		pString->size = 0;
		while (c_string[pString->size] != '\0')
			pString->size++;
	}
	
    pString->capacity = pString->size + 1;
	pString->data = (char*)malloc(sizeof(char) * pString->capacity);
	
    if (pString->data == NULL) {
		free(pString);
		return NULL;
	}

	for (int i = 0; i < pString->size; i++) 
		pString->data[i] = c_string[i];

	return pString;
}

int my_string_get_capacity(MY_STRING hMy_string) {
	My_string* pString = (My_string*)hMy_string;
	return pString->capacity; 
}

int my_string_get_size(MY_STRING hMy_string) {
	My_string* pString = (My_string*)hMy_string;
	return pString->size;
}

int my_string_compare(MY_STRING hLeft_string, MY_STRING hRight_string) {
	My_string* pLeft = (My_string*)hLeft_string;
	My_string* pRight = (My_string*)hRight_string;
	int i = 0, difference = 0;
    
    while (i < pLeft->size || i < pRight->size) {
        difference = pLeft->data[i] - pRight->data[i];
    
        if (difference) break;
        
        i++;
    }
	
    return difference;
}

Status my_string_extraction(MY_STRING hMy_string, FILE* fp) {
	My_string* pString = (My_string*)hMy_string;

	int c;	
	char first_character;
	int noc;
	char *temp;

	pString->size = 0;

	noc = fscanf(fp, " %c", &first_character);
    
	if (noc != 1)
		return FAILURE;

	pString->data[pString->size] = first_character;;
	pString->size++;
	c = fgetc(fp);
    
	while (c != EOF && !isspace(c)) 
	{
		if (pString->size >= pString->capacity) 
		{
			temp = (char*)malloc(sizeof(char) * pString->capacity * 2);
			if (temp == NULL) 
			{
				return FAILURE;
			}
			for (int i = 0; i < pString->size; i++) 
			{
				temp[i] = pString->data[i];
			}
			free(pString->data);
			pString->data = temp;
			pString->capacity *= 2;

		}

		pString->data[pString->size] = c;
		pString->size++;
		c = fgetc(fp);
	}

	if (c != EOF) {
		ungetc(c, fp);
	}
    
	return SUCCESS;
}

Status my_string_insertion(MY_STRING hMy_string, FILE* fp) {
	My_string* pString = (My_string*)hMy_string;

	for (int i = 0; i < pString->size; i++)
	{
		if (fputc(pString->data[i], fp) == EOF) 
		{
			return FAILURE;
		}	
	}
	return SUCCESS;
}

Status my_string_push_back(MY_STRING hMy_string, char item)
{
	My_string* pString = (My_string*)hMy_string;

    if (pString->size >= pString->capacity) {
        //Needs resizing
        char* temp = (char*)malloc(sizeof(char) * pString->capacity * 2);
        
        if (temp == NULL) {
            //Resizing failed
            printf("Failed to resize in my_string_push_back.\n");
            return FAILURE;
        }
        
        for (int i = 0; i < pString->size; i++)
            temp[i] = pString->data[i];
        
        free(pString->data);
        pString->data = temp;
        pString->capacity *= 2;
    }
    
    pString->data[pString->size] = item;
    pString->size++;
    
	return SUCCESS;
}

Status my_string_pop_back(MY_STRING hMy_string)
{
	My_string* pString = (My_string*)hMy_string;

    if (my_string_empty(hMy_string)) {
		printf("pop_back failed. empty string.\n");
		return FAILURE;
	}
    
	pString->size--;

	return SUCCESS;
}

char* my_string_at(MY_STRING hMy_string, int index)
{
	My_string* pString = (My_string*)hMy_string;

	if (index < 0 || index >= pString->size)
		return NULL;

	return pString->data + index;

}

char* my_string_c_str(MY_STRING hMy_string)
{
	My_string* pString = (My_string*)hMy_string;

	if (my_string_push_back(pString, '\0') == FAILURE)
		return NULL;

	pString->size--;

	return pString->data;
}

Status my_string_concat(MY_STRING hResult, MY_STRING hAppend)
{
	My_string* pResult = (My_string*)hResult;
	My_string* pAppend = (My_string*)hAppend;

	if (pResult->capacity < (pResult->size + pAppend->size))
	{
		char* temp = (char*)malloc(sizeof(char) * (pResult->size + pAppend->size + 1));
		if (!temp)
			return FAILURE;
		for (int i = 0; i < pResult->size; i++)
			temp[i] = pResult->data[i];

		free(pResult->data);
		pResult->data = temp;
	}

	pResult->capacity = (pResult->size + pAppend->size + 1);

	for (int i = 0; i < pAppend->size; i++)
		my_string_push_back(pResult, pAppend->data[i]);

	return SUCCESS;
}

Boolean my_string_empty(MY_STRING hMy_string)
{
	My_string* pString = (My_string*)hMy_string;
	return (Boolean)(pString->size <= 0);
}

Status my_string_assignment(ITEM* phLeft, ITEM hRight)
{
	My_string* pLeft;
	My_string* pRight;

    if (*phLeft == NULL) {
        *phLeft = my_string_init_c_string(my_string_c_str(hRight));
        
        if (*phLeft == NULL)
            return FAILURE;
    }
    else {
        pLeft = (My_string*)*phLeft;
        pRight = (My_string*)hRight;
        
        if (pRight->size >= pLeft->capacity) {
            char* temp = (char*)malloc(sizeof(char) * (pRight->size + 1));
            
            if (!temp) {
                return FAILURE;
            }
            
            free(pLeft->data);
            pLeft->data = temp;
            pLeft->capacity = pRight->size + 1;
        }
        
        for (int i = 0; i < pRight->size; i++) {
            pLeft->data[i] = pRight->data[i];
        }
        
        pLeft->size = pRight->size;
    }
    
    return SUCCESS;
}

MY_STRING my_string_init_copy(MY_STRING hMy_string)
{
	MY_STRING hCopy = my_string_init_default();
	My_string* pString = (My_string*)hMy_string;

	if (hCopy == NULL || pString == NULL)
		return NULL;

	for (int i = 0; i < my_string_get_size(hMy_string); i++)
		my_string_push_back(hCopy, *my_string_at(hMy_string, i));

	return hCopy; 
}

void my_string_swap(MY_STRING hLeft, MY_STRING hRight)
{
	My_string* pLeft = (My_string*)hLeft;
	My_string* pRight = (My_string*)hRight;

	int a = pLeft->size;
	pLeft->size = pRight->size;
	pRight->size = a;

	int b = pLeft->capacity;
	pLeft->capacity = pRight->capacity;
	pRight->capacity = b;

	char* temp = pLeft->data;
	pLeft->data = pRight->data;
	pRight->data = temp;

	return;
}

void my_string_destroy(ITEM* phItem) {
    My_string* pString = (My_string*)*phItem;
    free(pString->data);
    free(pString);
    *phItem = NULL;
}

Status get_word_key_value(MY_STRING current_word_family, MY_STRING new_key, MY_STRING word, char guess)
{
    if (my_string_assignment(&new_key, current_word_family) == FAILURE) {
        return FAILURE;
    }
    
    for (int i = 0; i < my_string_get_size(word); i++) {
        if (tolower(*my_string_at(word, i)) == tolower(guess)) {
            *my_string_at(new_key, i) = tolower(guess);
        }
    }
    
    return SUCCESS;
}
