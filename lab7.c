#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "generic_vector.h"
#include "my_string.h"

#define SIZE 30

ITEM init_assignment(ITEM* phItem, ITEM hItem);
void destroy(ITEM* phItem);


void read_dictionary(GENERIC_VECTOR dictionary[], int size);

int main(int argc, char** argv)
{
    GENERIC_VECTOR dictionary[SIZE];
    
    read_dictionary(dictionary, SIZE);
    
    for (int i = 0; i < SIZE; i++) {
        printf("Words of length %d : %d\n", i, generic_vector_get_size(dictionary[i]));
    }
    
    for (int i = 0; i < SIZE; i++) {
        generic_vector_destroy(&dictionary[i]);
    }
    
    return 0;
}

ITEM init_assignment(ITEM* phItem, ITEM hItem)
{
    MY_STRING hArg = (MY_STRING)hItem;
    MY_STRING hString = my_string_init_default();
    
    if (hString == NULL)
        exit(1);
    
    hString = my_string_init_copy(hArg);
    
    return hString;
}

void destroy(ITEM* phItem)
{
    MY_STRING hString = (MY_STRING)*phItem;
    my_string_destroy(&hString);
    *phItem = NULL;
}

void read_dictionary(GENERIC_VECTOR dictionary[], int size)
{
    FILE* fp = NULL;
    MY_STRING hWord = my_string_init_default();
    
    if (!hWord) {
        printf("Failed to allocate space for word in read dictionary.\n");
        exit(1);
    }
    
    fp = fopen("dictionary.txt", "r");
    
    if (!fp)
    {
        printf("Unable to open \"dictionary.txt\" file for reading.\n");
        exit(1);
    }
    
    for (int i = 0; i < size; i++) {
        dictionary[i] = generic_vector_init_default(my_string_assignment, destroy);
    }
    
    while (my_string_extraction(hWord, fp)) {
        if (my_string_get_size(hWord) < size) {
            if (generic_vector_push_back(dictionary[my_string_get_size(hWord)], hWord) == FAILURE) {
                printf("Failed to allocate space for one of the dictionary words in a generic vector.\n");
                exit(1);
            }
        }
    }
    
    fclose(fp);
}

