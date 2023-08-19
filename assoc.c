//
//  assoc.c
//  HANGMAN
//
//  Created by Kwadwo A Bempah on 4/22/23.
//

#include "assoc.h"
#include <stdlib.h>
#include <stdio.h>


struct node;
typedef struct node Node;

struct node {
    MY_STRING hKey;
    GENERIC_VECTOR hWords;
    Node* left;
    Node* right;
};

ASSOCIATIVE_ARRAY associative_array_init_default(void)
{
    Node* pRoot = (Node*)malloc(sizeof(Node));
    
    if (pRoot) {
        pRoot->hKey = NULL;
        pRoot->hWords = generic_vector_init_default(my_string_assignment, my_string_destroy);
        
        if (!pRoot->hWords) {
            free(pRoot);
            return NULL;
        }
        
        pRoot->left = NULL;
        pRoot->right = NULL;
    }

    return (ASSOCIATIVE_ARRAY)pRoot;
}

Status associative_array_insert(ASSOCIATIVE_ARRAY* phRoot, MY_STRING h_key, MY_STRING h_word)
{
    Node* pRoot = (Node*)*phRoot;
    
    if (pRoot->hKey == NULL) {
        Node* pRoot = (Node*)malloc(sizeof(Node));
        
        if (pRoot == NULL) {
            printf("Failed to allocate node in tree.\n");
            exit(1);
        }
        
        pRoot->hKey = NULL;
        my_string_assignment((ITEM*)&pRoot->hKey, (ITEM)h_key);
        
        //DEBUG
        printf("Added new node with key ");
        my_string_insertion(pRoot->hKey, stdout);
        printf("\n");
        
        pRoot->hWords = generic_vector_init_default(my_string_assignment, my_string_destroy);
        
        if (pRoot->hWords == NULL) {
            printf("Failed to allocate space for generic vector\n");
            exit(1);
        }
        
        if (generic_vector_push_back(pRoot->hWords, h_word) == FAILURE) {
            printf("Could not insert word into word family.\n");
            exit(1);
        }
       
        pRoot->left = NULL;
        pRoot->right = NULL;
    }
    else if (my_string_compare((pRoot)->hKey, h_key) < 0) {
       
        if (associative_array_insert((ASSOCIATIVE_ARRAY*)&pRoot->left, h_key, h_word) == FAILURE) {
            printf("Failed to insert word into family.\n");
            exit(1);
        }
    }
    else if (my_string_compare((pRoot)->hKey, h_key) > 0) {
       
        if (associative_array_insert((ASSOCIATIVE_ARRAY*)&pRoot->right, h_key, h_word) == FAILURE) {
            printf("Failed to insert word into family.\n");
            exit(1);
        }
    }
    else {
        if (generic_vector_push_back(pRoot->hWords, (ITEM)h_word) == FAILURE) {
            printf("Failed to insert word into family.\n");
            exit(1);
        }
    }
    
    return SUCCESS;
}

