#ifndef header_h
#define header_h
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>


typedef struct node            // structure for single linked list to store filenames
{
    char arr[150];
    struct node *link;
}invert;

typedef enum                    // enum for success and failure
{
    failure,
    success,
} status;

typedef struct sub_node         // structure for subnode
{
    int w_count;
    char f_name[20];
    struct sub_node * slink;
}sub_node;

typedef struct main_node        // structure for mainnode
{
    int f_count;
    char word[20];
    sub_node *slink;
    struct main_node * mlink;
}main_node;

typedef struct has_node         // structure for hash table
{
    int index;
    main_node *link;
}hash;

status check(invert *head,char* str);                // func for finding dupicate files
status insert_list(invert **head,char* str);         // func for inserting files in slist
status create(hash *arr,invert *head);               // func create hash table
status display(hash *arr);                           // func for dispaly output
status search(hash *arr,char *user);                 // func for search user given word
status save(hash *arr, FILE *fptr);                  // func for save data in to file
status update(FILE *fptr1, hash *arr,invert **head); // func for update new file
status free_head(invert ** head, char *str);         // func for free the files which are already present

#endif
