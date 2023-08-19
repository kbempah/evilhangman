#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "generic_vector.h"
#include "my_string.h"

#define SIZE 30

struct node;
typedef struct node Node;

struct node {
    MY_STRING hKey;
    GENERIC_VECTOR hWords;
    Node* left;
    Node* right;
};

Node* root;

void tree_insert(Node** pRoot, MY_STRING hKey, MY_STRING hWord);
Node* find_largest_family(Node* root);
void print_all_bins(Node* root);
void tree_swap_and_destroy(Node** pRoot, GENERIC_VECTOR* phWorking_words, MY_STRING* phDisplay_string);
void tree_destroy(Node* root);

void read_dictionary(GENERIC_VECTOR dictionary[], int size);
Boolean user_wishes_to_play_again(void);
void play_evil_hangman(GENERIC_VECTOR dictionary[], int size);
int get_number_of_letters(GENERIC_VECTOR dictionary[], int size);
void get_valid_word_length(GENERIC_VECTOR* words_of_length, int* word_length);
int get_number_of_guesses(void);
void clear_keyboard_buffer(void);
void show_guesses(Boolean* past_guesses);
char get_guess(Boolean* past_guesses);

/*int main(int argc, char* argv[])
{
    GENERIC_VECTOR dictionary[SIZE];
    
    /*printf("\t\t\t\t\t\tEVIL HANGMAN GAME\n");
    printf("\t\t\t\tPress the enter key to continue...\n");
    
    getchar();
    
    fflush(stdin);
    
    read_dictionary(dictionary, SIZE);
    
    do {
        printf("\t\t\t\t\t\tEVIL HANGMAN GAME\n");
        printf("\t\t\t\tPress the enter key to continue...\n");
        
        getchar();
        
        fflush(stdin);
        play_evil_hangman(dictionary, SIZE);
    } while (user_wishes_to_play_again());
    
    for (int i = 0; i < SIZE; i++) {
        generic_vector_destroy(&dictionary[i]);
    }
    
    return 0;
}*/

/*int main(int argc, char* argv[])
{
    MY_STRING hOld_key = my_string_init_c_string("---");
    MY_STRING hNew_key = my_string_init_default();
    MY_STRING hWord = my_string_init_c_string("The");
    char guess = 'T';
    
    GENERIC_VECTOR dictionary[SIZE];
    
    read_dictionary(dictionary, SIZE);
    
    if (get_word_key_value(hOld_key, hNew_key, hWord, guess) != FAILURE) {
        printf("The old key is ");
        my_string_insertion(hOld_key, stdout);
        printf("\n");
        printf("The new key is ");
        my_string_insertion(hNew_key, stdout);
        printf("\n");
    }
    
    for (int i = 0; i < SIZE; i++) {
        generic_vector_destroy(&dictionary[i]);
    }
    
    my_string_destroy(&hOld_key);
    my_string_destroy(&hNew_key);
    my_string_destroy(&hWord);
    
    return 0;
}*/

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

void read_dictionary(GENERIC_VECTOR dictionary[], int size)
{
    FILE* fp = fopen("dictionary.txt", "r");
    
    if (!fp)
    {
        printf("Unable to open \"dictionary.txt\" file for reading.\n");
        exit(1);
    }
    
    MY_STRING hWord = my_string_init_default();
    
    if (!hWord) {
        printf("Failed to allocate space for word in read dictionary.\n");
        exit(1);
    }
    
    for (int i = 0; i < size; i++) {
        dictionary[i] = generic_vector_init_default(my_string_assignment, my_string_destroy);
        
        if (dictionary[i] == NULL)
            printf("Error occured initializing dictionary of words at %d.\n", i);
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

void play_evil_hangman(GENERIC_VECTOR dictionary[], int size)
{
    GENERIC_VECTOR hWorking_words;
    MY_STRING hNewKey;
    Node* largest_family;
    Boolean past_guesses[26];   //For tracking already guessed characters
    int number_of_letters;
    int number_of_guesses;
    int number_of_incorrect_guesses = 0;
    char guess;
    
    MY_STRING hDisplay_string = my_string_init_default();
    
    if (hDisplay_string == NULL) {
        printf("Failed to allocate space for hDisplay_string.\n");
        exit(1);
    }
    
    hNewKey = my_string_init_default();
    
    if (hNewKey == NULL) {
        printf("Failed to allocate space for new key.\n");
        exit(1);
    }
    
    for (int i = 0; i < 26; i++) {
        past_guesses[i] = FALSE;
    }
    
    //Get number of letters user wants to play with
    number_of_letters = get_number_of_letters(dictionary, size);
    
    hWorking_words = generic_vector_init_default(my_string_assignment, my_string_destroy);
    
    if (hWorking_words == NULL) {
        printf("Failed to allocate space for hWorking_words.\n");
        exit(1);
    }
    
    //Initialize hWorking_words with all words in the dictionary at the specified length
    for (int i = 0; i < generic_vector_get_size(dictionary[number_of_letters]); i++) {
        if (generic_vector_push_back(hWorking_words, *generic_vector_at(dictionary[number_of_letters], i)) == FAILURE) {
            printf("Failed to initialize hWorking_words.\n");
            exit(1);
        }
    }
    
    printf("Total number of words left: %d\n", generic_vector_get_size(hWorking_words));
    
    //Get number of guesses that user wants to play with
    number_of_guesses = get_number_of_guesses();
    printf("Remaining number of guesses : %d\n", number_of_guesses - number_of_incorrect_guesses);
    
    for (int i = 0; i < number_of_letters; i++) {
        my_string_push_back(hDisplay_string, '-');
    }
    
    //Loop until they win or run out guesses
    while (number_of_guesses > 0) {
        printf("Word: ");
        my_string_insertion(hDisplay_string, stdout);
        printf("\n");
        printf("Previous guesses : ");
        show_guesses(past_guesses);
        guess = get_guess(past_guesses);
        
        //build the associative array based on AVL tree
        for (int i = 0; i < generic_vector_get_size(hWorking_words); i++) {
            
            if (get_word_key_value(hDisplay_string, hNewKey, *generic_vector_at(hWorking_words, i), guess) == FAILURE) {
                printf("Could not generate key for word.\n");
                exit(1);
            }
            
            tree_insert(&root, hNewKey, *generic_vector_at(hWorking_words, i));
        }
        
        largest_family = find_largest_family(root);
        
        if (my_string_compare(largest_family->hKey, hDisplay_string) == 0) {
            printf("Sorry, there are no %c's in the word.\n", guess);
            number_of_incorrect_guesses++;
            number_of_guesses--;
            printf("Remaining guesses : %d\n", number_of_guesses);
        }
        else {
            printf("Good guess! Keep going.\n");
            number_of_guesses--;
            printf("Remaining guesses : %d\n", number_of_guesses);
        }
        
        
        if (generic_vector_get_size(hWorking_words) <= 1 && my_string_compare(*generic_vector_at(hWorking_words, 0), hNewKey) == 0) {
            printf("You won!\n");
            break;
        }
        
        if (number_of_guesses == 0) {
            printf("\t\t\t\t\t\tGAME OVER!\n");
            printf("You ran out of guesses, better luck next time :(\n");
            printf("The word was \"%s\"\n", my_string_c_str(*generic_vector_at(largest_family->hWords, 0)));
        }
        
        tree_swap_and_destroy(&root, &hWorking_words, &hDisplay_string);
        
        //print_all_bins(root);
        //printf("The largest bin has %d words in it.\n", generic_vector_get_size(largest_family->hWords));
    }
    
    
    my_string_destroy(&hNewKey);
    my_string_destroy(&hDisplay_string);
    generic_vector_destroy(&hWorking_words);
}

Boolean user_wishes_to_play_again(void)
{
    char option;
    int noc;
    
    printf("Would you like to play again? (y / n) > ");
    noc = scanf("%c", &option);
    clear_keyboard_buffer();
    
    while (noc != 1 || (tolower(option) != 'y' && tolower(option) != 'n')) {
        printf("Valid inputs are y or n.\n");
        printf("Would you like to play again? (y / n) > ");
        noc = scanf("%c", &option);
        clear_keyboard_buffer();
    }
    
    return (tolower(option) == 'y') ? TRUE : FALSE;
}

void get_valid_word_length(GENERIC_VECTOR* words_of_length, int* word_length) {
    int noc;
    printf("Enter the word length: ");
    noc = scanf("%d", word_length);
    
    while (noc != 1 || *word_length <= 0 || *word_length >= 30 ||
        generic_vector_is_empty(words_of_length[*word_length])) {
        clear_keyboard_buffer();
        if (noc != 1 || *word_length <= 0) {
            printf("Please enter an integer greater than 0.\n");
        }
        else {
            printf("No words of this length are present in the dictionary.\n");
        }
        printf("Enter the word length: ");
        noc = scanf("%d", word_length);
    }
    clear_keyboard_buffer();
}

int get_number_of_letters(GENERIC_VECTOR dictionary[], int size)
{
    int length;
    int noc;
    
    printf("What word length do you wish to play with? > ");
    noc = scanf("%d", &length);
    clear_keyboard_buffer();
    
    while (noc != 1 || length <= size - size || length >= size || generic_vector_get_size(dictionary[length]) <= 0) {
        if (noc != 1 || length <= 0) {
            printf("Enter a value greater than 0.\n");
        }
        else {
            printf("No words available at this length, try again.\n");
        }
        printf("What word length do you wish to play with? > ");
        noc = scanf("%d", &length);
        clear_keyboard_buffer();
    }
    
    return length;
}

int get_number_of_guesses(void)
{
    int guesses, noc;

    printf("How many guesses would you like to play with? > ");
    noc = scanf("%d", &guesses);
    clear_keyboard_buffer();
    while (noc != 1 || guesses < 1 || guesses > 26) {
        printf("Enter a number between 1 and 26.\n");
        printf("How many guesses would you like to play with? > ");
        noc = scanf("%d", &guesses);
        clear_keyboard_buffer();
    }
    
    return guesses;
}

void clear_keyboard_buffer(void)
{
    char c;
    
    scanf("%c", &c);
    
    while (c != '\n') {
        scanf("%c", &c);
    }
}

void show_guesses(Boolean* past_guesses)
{
    for (int i = 0; i < 26; i++) {
        if (past_guesses[i])
            printf("%c", tolower('A' + i));
    }
    printf("\n");
}

char get_guess(Boolean* past_guesses)
{
    char c;
    
    printf("Enter guess > ");
    scanf(" %c", &c);
    clear_keyboard_buffer();
    
    while (!isalpha(c) || past_guesses[tolower(c) - 'a']) {
        printf("I'm sorry but I do not understand.\n");
        printf("Perhaps you have already guessed that letter.\n");
        printf("Enter guess > ");
        scanf(" %c", &c);
        clear_keyboard_buffer();
    }
    
    past_guesses[tolower(c) - 'a'] = TRUE;
    
    return c;
}

void tree_insert(Node** pRoot, MY_STRING hKey, MY_STRING hWord)
{
    if (*pRoot == NULL) {
        *pRoot = (Node*)malloc(sizeof(Node));
        
        if (*pRoot == NULL) {
            printf("Failed to allocate node in tree.\n");
            exit(1);
        }
        
        (*pRoot)->hKey = NULL;
        if (!my_string_assignment(&((*pRoot)->hKey), hKey)) {
            printf("Failed to copy hKey to pRoot->hKey in tree_insert.\n");
            exit(1);
        }
        
        //DEBUG
        //printf("Added new node with key ");
        //my_string_insertion((*pRoot)->hKey, stdout);
        //printf("\n");
        
        (*pRoot)->hWords = generic_vector_init_default(my_string_assignment, my_string_destroy);
        
        if ((*pRoot)->hKey == NULL) {
            printf("Failed to allocate space for generic vector pRoot->hWords in tree_insert.\n");
            exit(1);
        }
        
        if (!generic_vector_push_back((*pRoot)->hWords, hWord)) {
            printf("Failed to push back *pRoot->hWords.\n");
            exit(1);
        }
        
        (*pRoot)->left = (*pRoot)->right = NULL;
    }
    //go left since hKey lexicographically precedes word at root
    else if (my_string_compare((*pRoot)->hKey, hKey) < 0) {
        tree_insert(&((*pRoot)->left), hKey, hWord);
    }
    //go right since hKey lexicographically succeeds word at root
    else if (my_string_compare((*pRoot)->hKey, hKey) > 0) {
        tree_insert(&((*pRoot)->right), hKey, hWord);
    }
    else {
        generic_vector_push_back((*pRoot)->hWords, hWord);
    }
}

Node* find_largest_family(Node* root)
{
    Node* left_subtree;
    Node* right_subtree;
    Node* largest_subtree;
    
    //largest_subtree holds the largest subtree of words in the tree
    
    //Empty tree;
    if (root == NULL) {
        return NULL;
    }
    else {
        left_subtree = find_largest_family(root->left);
        right_subtree = find_largest_family(root->right);
        
        //Check if there are children, if none root is the largest family of words
        if (left_subtree == NULL && right_subtree == NULL) {
            return root;
        }
        else if (left_subtree && right_subtree) {
            //compare the left and right subtrees and choose the largest
            largest_subtree = (generic_vector_get_size(left_subtree->hWords) > generic_vector_get_size(right_subtree->hWords)) ? left_subtree : right_subtree;
            
            //compare largest subtree to root and choose the largest
            largest_subtree = (generic_vector_get_size(largest_subtree->hWords) > generic_vector_get_size(root->hWords)) ? largest_subtree : root;
        }
        else if (left_subtree && !right_subtree) {
            //NO right subtree, compare the left and root subtrees and choose the largest
            largest_subtree = (generic_vector_get_size(left_subtree->hWords) > generic_vector_get_size(root->hWords)) ? left_subtree : root;
        }
        else {
            //NO left subtree, compare the right and root subtrees and choose the largest
            largest_subtree = (generic_vector_get_size(right_subtree->hWords) > generic_vector_get_size(root->hWords)) ? right_subtree : root;
        }
    }
    
    return largest_subtree;
}

void print_all_bins(Node* root)
{
    if (root != NULL) {
        print_all_bins(root->left);
        my_string_insertion(root->hKey, stdout);
        printf(" %d", generic_vector_get_size(root->hWords));
        printf("\n");
        print_all_bins(root->right);
    }
}

void tree_swap_and_destroy(Node** pRoot, GENERIC_VECTOR* phWorking_words, MY_STRING* phDisplay_string)
{
    Node* largest_family = find_largest_family(*pRoot);
    GENERIC_VECTOR temp_vector;
    
    //do swap for largest family of words
    temp_vector = *phWorking_words;
    *phWorking_words = largest_family->hWords;
    largest_family->hWords = temp_vector;
    
    //do display key for key of largest
    my_string_swap(*phDisplay_string, largest_family->hKey);
    
    tree_destroy(*pRoot);
    *pRoot = NULL;
}

void tree_destroy(Node* root) {
    if (root == NULL) {
        tree_destroy(root->left);
        tree_destroy(root->right);
        free(root);
        
    }
}
