/*
    This defines prototypes for dictionary-related functions.
*/

#include <stdio.h>

struct dict;

struct searchResult;

/*
    Returns a new dictionary.
*/
struct dict *newDict(char *header, int check);

/*
    Add the given row to the dictionary.
*/
void prependRow(struct dict *dict, char *row, int check);

/*
    Search the given key in the dictionary.
*/
struct searchResult *queryKD(struct dict *dict, char *string);

/*
    Print the given search result to a file.
*/
void writeSearchResult(struct searchResult *result, struct dict *dict, FILE *file);

/*
    Frees all memory associated with dictionary.
*/
void freeDict(struct dict *dict);

/*
    Frees anything used only by the search result.
*/
void freeSearchResult(struct searchResult *result);
