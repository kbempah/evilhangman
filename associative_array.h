//
//  associative_array.h
//  HANGMAN
//
//  Created by Kwadwo A Bempah on 4/17/23.
//

#ifndef associative_array_h
#define associative_array_h
#include "Status.h"
#include "generic.h"
#include "my_string.h"
#include "generic_vector.h"

typedef void* ASSOCIATIVE_ARRAY;

ASSOCIATIVE_ARRAY associative_array_init_default(void);
Status associative_array_insert(ASSOCIATIVE_ARRAY* phArray, MY_STRING hkey, MY_STRING hvalue);
GENERIC_VECTOR associative_array_search(ASSOCIATIVE_ARRAY hArray, MY_STRING hkey);
Status associative_array_get_vector_of_keys(ASSOCIATIVE_ARRAY hArray, GENERIC_VECTOR word_keys);
void associative_array_destroy(ASSOCIATIVE_ARRAY* phArray);

#endif /* associative_array_h */
