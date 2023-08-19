//
//  associative.h
//  HANGMAN
//
//  Created by Kwadwo A Bempah on 4/25/23.
//

#ifndef associative_h
#define associative_h

#include <stdio.h>
#include "my_string.h"
#include "generic_vector.h"

typedef void* ASSOCIATIVE_ARRAY;

ASSOCIATIVE_ARRAY associative_array_init_default(void);
Status associative_array_insert(ASSOCIATIVE_ARRAY* phArray, MY_STRING hKey, MY_STRING hWord);
void associative_array_destroy(ASSOCIATIVE_ARRAY* phArray);

#endif /* associative_h */
