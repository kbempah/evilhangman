//
//  avl_test.c
//  HANGMAN
//
//  Created by Kwadwo A Bempah on 4/23/23.
//

#include <stdio.h>
#include <stdlib.h>
#include "associative_array.h"

int main(int argc, char* argv[]) {

    MY_STRING key = my_string_init_c_string("testing");
    if (key == NULL) {
        printf("My_string object couldn't initialize.\n");
        exit(1);
    }
    ASSOCIATIVE_ARRAY hArray = associative_array_init_default();
    if (hArray == NULL) {
        printf("Associative_array object couldn't initialize.\n");
        exit(1);
    }

    GENERIC_VECTOR hVector = associative_array_search(hArray, key);
    if (generic_vector_is_empty(hVector)) {
        printf("Empty\n");
    }

    MY_STRING word = my_string_init_c_string("TEST");
    if (word == NULL) {
        printf("My_string object couldn't initialize.\n");
        exit(1);
    }
    Status status =    associative_array_insert(&hArray, key, word);
    if (status == FAILURE) {
        printf("Bad insert\n");
        exit(1);
    }

    hVector = associative_array_search(hArray, key);
    if (generic_vector_is_empty(hVector)) {
        printf("Still empty... Not good\n");
    }

    MY_STRING word_after_insertion = generic_vector_at(hVector, 0);

    printf("%s\n", my_string_c_str(word_after_insertion));

    if (my_string_compare(word, word_after_insertion) == 0) {
        printf("Insertion worked!\n");
    }

    /////////////////////////////////////////////////////////////

    MY_STRING new_key = my_string_init_c_string("tacobell");
    MY_STRING new_word = my_string_init_c_string("chalupa");
    status = associative_array_insert(&hArray, new_key, new_word);
    if (status == FAILURE) {
        printf("Bad insert (new key)\n");
        exit(1);
    }

    hVector = associative_array_search(hArray, new_key);
    if (generic_vector_is_empty(hVector)) {
        printf("Still empty... Not good\n");
    }

    word_after_insertion = generic_vector_at(hVector, 0);

    printf("%s\n", my_string_c_str(word_after_insertion));

    if (my_string_compare(new_word, word_after_insertion) == 0) {
        printf("Insertion worked!\n");
    }

    return 0;
}
