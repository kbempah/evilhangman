//
//  associative.c
//  HANGMAN
//
//  Created by Kwadwo A Bempah on 4/25/23.
//

#include <stdio.h>
#include <stdlib.h>
#include "associative.h"

struct node;
typedef struct node Node;

struct node {
    MY_STRING hKey;
    GENERIC_VECTOR hWords;
    Node* left;
    Node* right;
};

ASSOCIATIVE_ARRAY associative_array_init_default(void) {
    Node* root = (Node*)malloc(sizeof(Node));
    
    if (root) {
        root->hKey = NULL;
        root->hWords = generic_vector_init_default(my_string_assignment, my_string_destroy);
        
        if (root->hWords == NULL) {
            printf("Failed to allocate space for root->hWords generic vector.\n");
            exit(1);
        }
        
        root->left = NULL;
        root->right = NULL;
    }
    
    return (ASSOCIATIVE_ARRAY)root;
}

Status associative_array_insert(ASSOCIATIVE_ARRAY* phArray, MY_STRING hKey, MY_STRING hWord)
{
    Node* root = (Node*)*phArray;
    
    if (root == NULL) {
        Node* temp = (Node*)malloc(sizeof(Node));
        
        if (temp == NULL) {
            printf("Failed to allocate space for node in tree.\n");
            return FAILURE;
        }
        
        (temp)->hKey = NULL;
        my_string_assignment(&(temp)->hKey, hKey);
        
        if ((temp)->hKey == NULL) {
            printf("Failed to copy hKey to temp->hKey.\n");
            return FAILURE;
        }
        
        //DEBUG
        printf("Added new node with key ");
        my_string_insertion((temp)->hKey, stdout);
        printf("\n");
        
        (temp)->hWords = generic_vector_init_default(my_string_assignment, my_string_destroy);
        
        if ((temp)->hWords == NULL) {
            printf("Failed to allocate space for generic vector temp->hWords in insert.\n");
            return FAILURE;
        }
        
        if (generic_vector_push_back((temp)->hWords, hWord) == FAILURE) {
            printf("Failed to insert into generic_vector temp->hWords in insert.\n");
            return FAILURE;
        }
        
        (temp)->left = NULL;
        (temp)->right = NULL;
        
        *phArray = temp;
        
    }
    else if (my_string_compare((root)->hKey, hKey) < 0) {
        if(associative_array_insert((ASSOCIATIVE_ARRAY)&(root)->left, hKey, hWord) == FAILURE) {
            printf("Failed to insert hWord into left subtree in insert.\n");
            return FAILURE;
        }
    }
    else if (my_string_compare((root)->hKey, hKey) > 0) {
        if(associative_array_insert((ASSOCIATIVE_ARRAY)&(root)->right, hKey, hWord) == FAILURE) {
            printf("Failed to insert hWord into right subtree in insert.\n");
            return FAILURE;
        }
    }
    else {
        if (generic_vector_push_back((root)->hWords, hWord) == FAILURE) {
            printf("Failed to insert hWord at root->hWords in insert.\n");
            return FAILURE;
        }
    }
    
    return SUCCESS;
}
