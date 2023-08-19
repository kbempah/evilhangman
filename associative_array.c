//
//  associative_array.c
//  HANGMAN
//
//  Created by Kwadwo A Bempah on 4/17/23.
//

#include "associative_array.h"
#include <stdlib.h>

struct node;
typedef struct node Node;

struct node {
    MY_STRING hKey;
    GENERIC_VECTOR hWords;
    int height;
    Node* left;
    Node* right;
};

Node* left_rotation(Node* pNode);
Node* right_rotation(Node* pNode);
int get_balance_factor(Node* root);
int get_height(Node* root);
int max(int a, int b);

Node* left_rotation(Node* pNode)
{
    Node* node = pNode->right;
    Node* temp = node->left;
    
    //perform rotations
    node->left = pNode;
    pNode->left = temp;
    
    //update tree heights
    pNode->height = 1 + max(get_height(pNode->left), get_height(pNode->right));
    node->height = 1 + max(get_height(node->left), get_height(node->right));
    
    return node;
}

Node* right_rotation(Node* pNode)
{
    Node* node = pNode->left;
    Node* temp = node->right;
    
    //perform rotations
    node->right = pNode;
    pNode->left = temp;
    
    //update tree heights
    pNode->height = 1 + max(get_height(pNode->left), get_height(pNode->right));
    node->height = 1 + max(get_height(node->left), get_height(node->right));
    
    return node;
}

int get_balance_factor(Node* root)
{
    if (!root) return 0;
    
    
    //balance factor = height of left subtree - right subtree. If negative, tree is right heavy.
    return get_height(root->left) - get_height(root->right);
}

int get_height(Node* root)
{
    if (!root) return 0;
    
    return root->height;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

ASSOCIATIVE_ARRAY associative_array_init_default(void)
{
    Node* root = (Node*)malloc(sizeof(Node));
    
    if (root != NULL) {
        root->hKey = NULL;
        root->hWords = generic_vector_init_default(my_string_assignment, my_string_destroy);
        
        if (!(root)->hWords) {
            free(root);
            return NULL;
        }
        
        root->height = 1;
        root->left = NULL;
        root->right = NULL;
    }
    
    return (ASSOCIATIVE_ARRAY)root;
}

Status associative_array_insert(ASSOCIATIVE_ARRAY* phArray, MY_STRING hkey, MY_STRING hword)
{
    Node* root = (Node*)*phArray;
    int balance_factor;
    int my_string_comparison;
    
    //do normal BST insertions
    
    if (root->hKey == NULL) {
        Node* root = (Node*)malloc(sizeof(Node));
        
        if (root != NULL) {
            (root)->hKey = NULL;
            
            if (my_string_assignment(&(root)->hKey, hkey) == FAILURE) {
                printf("Failed to assign key at root.\n");
                exit(1);
            }
            
            if ((root)->hKey == NULL) {
                printf("Assignment failed, check my string assignment.\n");
            }
            
            (root)->hWords = generic_vector_init_default(my_string_assignment, my_string_destroy);
            
            if ((root)->hWords == NULL) {
                free(root);
                return FAILURE;
            }
            
            root->height = 1;
            root->left = NULL;
            root->right = NULL;
        }
        else
            return FAILURE;
    }
    
    my_string_comparison = my_string_compare(hkey, (root)->hKey);
    
    if (my_string_comparison == 0) {
        
        if (generic_vector_push_back((root)->hWords, (ITEM)hword) == FAILURE)
            return FAILURE;
        
        *phArray = root;
        return SUCCESS;
    }
    else if (my_string_comparison < 0) {
        if (associative_array_insert((ASSOCIATIVE_ARRAY)&(root->left), hkey, hword) == FAILURE)
            return FAILURE;
    }
    else {
        if (associative_array_insert((ASSOCIATIVE_ARRAY)&(root->right), hkey, hword) == FAILURE)
            return FAILURE;
    }
    
    root->height = 1 + max(get_height(root->left), get_height(root->right));
    
    balance_factor = get_balance_factor(root);
    
    // There are 4 general cases for unbalanced trees.
    // A left-left, right-right, left-right, and right-left.
    
    //left-left case
    if (balance_factor > 1 && my_string_compare(root->left->hKey, hkey) < 0)
        root = right_rotation(root);
    
    //right-right case
    else if (balance_factor < -1 && my_string_compare(root->right->hKey, hkey) > 0)
        root = left_rotation(root);
    
    //left-right case
    else if (balance_factor > 1 && my_string_compare(root->left->hKey, hkey) > 0) {
        root->left = left_rotation(root->left);
        root = right_rotation(root);
    }
    
    //right-left case
    else if (balance_factor < -1 && my_string_compare(root->right->hKey, hkey) < 0) {
        root->right = right_rotation(root->right);
        root = left_rotation(root);
    }
    
    *phArray = root;
    
    return SUCCESS;
}

GENERIC_VECTOR associative_array_search(ASSOCIATIVE_ARRAY hArray, MY_STRING key) {
    Node* root = (Node*)hArray;
    if (root == NULL) {
        return NULL;
    }
    int root_string_compare = my_string_compare(key, root->hKey);
    //if the key matches the root key
    if (root_string_compare == 0) {
        return root->hKey;
    }
    //if it goes on the left
    if (root_string_compare < 0) {
        return associative_array_search((ASSOCIATIVE_ARRAY)(root->left), key);
    }
    //if it goes on the right
    else {
        return associative_array_search((ASSOCIATIVE_ARRAY)(root->right), key);
    }
}

Status associative_array_get_vector_of_keys(ASSOCIATIVE_ARRAY hArray, GENERIC_VECTOR word_keys)
{
    Node* root = (Node*)hArray;
    
    if (root != NULL) {
        associative_array_get_vector_of_keys((ASSOCIATIVE_ARRAY)root->left, word_keys);
        
        if (generic_vector_push_back(word_keys, root->hKey) == FAILURE)
            return FAILURE;
        
        associative_array_get_vector_of_keys((ASSOCIATIVE_ARRAY)root->right, word_keys);
    }
    
    return SUCCESS;
}


void associative_array_destroy(ASSOCIATIVE_ARRAY* phArray)
{
    Node* root = (Node*)*phArray;
    
    if (root) {
        associative_array_destroy((ASSOCIATIVE_ARRAY)&root->left);
        associative_array_destroy((ASSOCIATIVE_ARRAY)&root->right);
        generic_vector_destroy(&root->hWords);
        
        if (root->hKey) {
            my_string_destroy(&root->hKey);
        }
        
        free(root);
        *phArray = NULL;
    }
}

