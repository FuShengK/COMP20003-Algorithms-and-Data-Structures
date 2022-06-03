#ifndef LINKEDLIST
#define LINKEDLIST
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define INPUT 1
#define OUTPUT 2
#define THE_KEY 3
#define CHARS_IN_QUOTES 200
#define CHAR_IN_QUOTES 100
#define HALF_MAX_LEN 256
#define MAX_LENGTH 512
#define QUOTE_SIGN '\"'
#define END_SIGN '\0'
#define COMMA ","
#define END ",\n"
#define ATTRIBUTES 11
#define CHARACTERS 128

typedef struct segment seg_t;
typedef struct linked_list l_t;

struct segment{
    char census_year[CHARACTERS];
    char block_id[CHARACTERS];
    char property_id[CHARACTERS];
    char base_property_id[CHARACTERS];
    char clue_small_area[CHARACTERS];
    char trading_name[CHARACTERS];
    char industry_code[CHARACTERS];
    char industry_description[CHARACTERS];
    char x_coordinate[CHARACTERS];
    char y_coordinate[CHARACTERS];
    char location[CHARACTERS];
    seg_t *next;
};

struct linked_list{
    seg_t *head;
};

int searching(l_t *linking, char* key, l_t* results);
seg_t *build_seg(char *record[ATTRIBUTES]);
l_t *empty_list(void);
l_t *insert_head(l_t *linking, seg_t *new_seg);
seg_t *copying(seg_t *old);
void free_list(l_t *linking);
void get_seg(char* attributes[ATTRIBUTES], char* strings, int quote_num);
void indexing(char* strings, int* index_quote);
int counts(char* strings);
void remove_quotes(char *strings);
#endif
