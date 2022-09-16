/*
    A dictionary based on the CLUE database
    Run with
        dict datafile outputfile < inputfile
    
    where 
        datafile is a CLUE csv,
        outputfile is the name of the file which data will be output to,
    
    and
        inputfile is in the format of the business name to search for,
        with one business name per line.
    
    Written by Grady Fitzpatrick for Algorithms and Data Structures 2020S2
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "read.h"
#include "dict.h"
#include "utils.h"
#define NO_RADIUS 0


int main(int argc, char **argv){
    if(argc < 3){
        fprintf(stderr, "Incorrect arguments\n");
        fprintf(stderr, "Run in the form\n");
        fprintf(stderr, "\tdict datafile outputfile < inputfile\n");
        exit(1);
    }
    
    char *line = NULL;
    size_t size = 0;
    struct dict *dict = readFile(argv[1], NO_RADIUS);
    struct searchResult *result = NULL;
    FILE *outputFile = fopen(argv[2], "w");
    assert(outputFile);
    
    while(getlineClean(&line, &size, stdin) != (-1)){
        
        // To search in K-D tree
        result = queryKD(dict, line);
        writeSearchResult(result, dict, outputFile);
        freeSearchResult(result);
    }

    if(line){
        free(line);
    }
    if(dict){
        freeDict(dict);
    }
    if(outputFile){
        fclose(outputFile);
    }
    
    return 0;
}
