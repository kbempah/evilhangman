//
//  assoc.h
//  HANGMAN
//
//  Created by Kwadwo A Bempah on 4/22/23.
//

#ifndef assoc_h
#define assoc_h

#include <stdio.h>
#include "my_string.h"
#include "generic_vector.h"
#include "Status.h"

typedef void* ASSOCIATIVE_ARRAY;

ASSOCIATIVE_ARRAY associative_array_init_default(void);
Status associative_array_insert(ASSOCIATIVE_ARRAY* phRoot, MY_STRING h_key, MY_STRING h_word);
void associative_array_destroy(ASSOCIATIVE_ARRAY* phArray);

#endif /* assoc_h */
