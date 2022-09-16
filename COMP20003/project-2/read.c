/*
    This defines implementations for read-related functions.
*/

#include "dict.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "utils.h"

struct dict *readFile(char *filename, int check){
    FILE *file = NULL;
    struct dict *returnDict = NULL;
    file = fopen(filename, "r");
    assert(file);
    
    char *line = NULL;
    size_t size = 0;
    
    /* First line is headers, so we handle differently. */
    if(getlineClean(&line, &size, file) != (-1)){
        returnDict = newDict(line, check);
    }
    
    /* Rest of lines are rows. */
    while(getlineClean(&line, &size, file) != (-1)){
        // Insert data into K-D tree
        prependRow(returnDict, line, check);
    }
    
    if(line){
        free(line);
    }
    if(file){
        fclose(file);
    }
    return returnDict;
}
