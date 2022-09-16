/*
    This defines implementations for dictionary-related functions.
*/

#include "dict.h"
#include "data.h"
#include "kdtree.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define ROOT_DEPTH 0
#define KEYDATAJOIN "-->"
#define FAILTEXT "NOTFOUND"

struct dict {
    struct dataMapping *mapping;
    // the pointer to the root of K-D tree
    struct kd *tree;
};

struct searchResult {
    struct key *key;
    // store the keys of all matched records
    struct key **keys;
    /* NULL terminated array of data. */
    struct data **data;
    struct dataMapping *mapping;
};

struct dataMapping {
    char **headers;
    int headerCount;
    int *keyLocations;
    int *dataLocations;
    int keyCount;
};

struct dict *newDict(char *header, int check){
    struct dict *returnDict = (struct dict *) malloc(sizeof(struct dict));
    assert(returnDict);
    returnDict->mapping = getDataMapping(header, check);
    returnDict->tree = newKD();
    return returnDict;
}

void prependRow(struct dict *dict, char *row, int check){
    dict->tree = insertToKD(dict->tree, dict->mapping, row, ROOT_DEPTH, check);
}

struct searchResult *queryKD(struct dict *dict, char *string){
    struct key *searchKey = readKey(string, dict->mapping);
    struct searchResult *result = (struct searchResult *) 
        malloc(sizeof(struct searchResult));
    assert(result);
    result->key = searchKey;
    result->keys = NULL;
    result->data = NULL;
    result->mapping = dict->mapping;
    searching(dict->tree, dict->mapping, searchKey, &(result->keys), &(result->data));
    return result;
}

void writeSearchResult(struct searchResult *result, struct dict *dict, FILE *file){
    char *keyText;
    char *resultText;
    int i;
    /* Commented out code is fairly clean way output-wise to display results */
    // int j;
    int first = 1;
    keyText = getKeyString(dict->mapping, result->key);
    i = 0;
    while((result->data)[i]){

        fprintf(file, "%s", keyText);
        resultText = getDataString(dict->mapping, (result->data)[i]);
        fprintf(file, " %s %s\n", KEYDATAJOIN, resultText);
        if(resultText){
            free(resultText);
        }
        i++;
        first = 0;
    }
    if(first){
        fprintf(file, "%s\n", FAILTEXT);
    }
    if(keyText){
        free(keyText);
    }
}

void freeDict(struct dict *dict){
    freeKD(dict->tree, dict->mapping);
    freeDataMapping(&(dict->mapping));
    free(dict);
}

void freeSearchResult(struct searchResult *result){
    if(result){
        //freeKey(&(result->key), result->mapping, check);
        if(result->data){free(result->data);}
        if(result->keys){free(result->keys);}
        free(result);
    }
}
