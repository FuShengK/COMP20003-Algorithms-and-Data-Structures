/*
    This defines implementations for K-D tree-related functions.
*/

#include "data.h"
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <assert.h>
#define TRUE 1
#define FALSE 0
#define DUP 2
#define ROOT_DEPTH 0
#define NEXT_DEPTH 1

struct key {
    char **keys;
};

struct kd *newKD(char *header){
    return NULL;
};

// struct K-D Tree
struct kd{
    struct key *key;
    struct data *data;
    // To the left child of K-D tree
    struct kd *left;
    // To the right child of K-D tree
    struct kd *right;
    // To store duplicate node for same data
    struct kd *chain; 
};

struct kd *newNode(){
    struct kd *returnNode = (struct kd *) malloc(sizeof(struct kd));
    assert(returnNode);
    returnNode->key = NULL;
    returnNode->data = NULL;
    returnNode->left = NULL;
    returnNode->right = NULL;
    returnNode->chain = NULL;
    return returnNode;
};

struct dataMapping {
    char **headers;
    int headerCount;
    int *keyLocations;
    int *dataLocations;
    int keyCount;
};
/*
    To free up memories from K-D tree duplicated nodes
*/
void freeDUP(struct kd *kd, struct dataMapping *mapping);


struct kd *insertToKD(struct kd *kd, struct dataMapping *mapping, 
                      char *row, int depth, int check){
    // build a new node and insert into temporary K-D tree
    struct kd *tmpNode = newNode();
    getData(row, mapping, &(tmpNode->key), &(tmpNode->data), check);
    if(kd == NULL){
        // build a new node
        struct kd *newRoot = newNode();    
        getData(row, mapping, &(newRoot->key), &(newRoot->data), check);
        return newRoot;
    }
    
    int next = checkingKey(kd->key, tmpNode->key, depth);
    // To check if the same
    if(next == DUP){
        struct kd *dup = kd->chain;
        if(dup == NULL){
            dup = tmpNode;       
        } else {
            while(dup != NULL){
                dup = dup->chain;
            }
            dup = tmpNode;
        }
    }
    // To check key value according to the the depth
    if(next){
        kd->left = insertToKD(kd->left, mapping, row, depth + NEXT_DEPTH, check);
    } else {
        kd->right = insertToKD(kd->right, mapping, row, depth + NEXT_DEPTH, check);
    }
    return kd;
}

void assignData(struct kd *kd, struct data ***data, struct key ***keys, int foundMatches){
    *data = realloc(*data, sizeof(struct data *) * (foundMatches + 2));
    assert(*data);
    (*data)[foundMatches] = kd->data;
    (*data)[foundMatches + 1] = NULL;
        
    *keys = realloc(*keys, sizeof(struct key *) * (foundMatches + 2));
    assert(*keys);
    (*keys)[foundMatches] = kd->key;
    (*keys)[foundMatches + 1] = NULL;
    foundMatches++;
}

/*
    Search for the key in the given K-D tree and put the data in the given location.
*/
void nearSearch(struct kd *kd, struct dataMapping *mapping, struct key *query, 
    struct key ***keys ,struct data ***data, double *min_diff, int depth){
    if(kd == NULL) {return;}
    // To get the distance between query and current node
    double distance;
    distance = getD(kd->key, query);
    // If it's smaller than the min_diff, UPDATE info   
    if(distance < (*min_diff)){
        int foundMatches = 0;
        // Chaining situation
        struct kd *dup = kd->chain;
        while(dup != NULL){
            int foundMatches = 0;
            assignData(dup, data, keys, foundMatches);            
            dup = dup->chain; 
        }    
        assignData(kd, data, keys, foundMatches);
        (*min_diff) = distance;
        freeDUP(dup, mapping);     
    }
    double query_diff = getQD(kd->key, query, depth);
    // Check if the node have 2 direction
    if(query_diff > (*min_diff)){
        // Implement one-direction
        if(checkingKey(kd->key, query, depth)){
            nearSearch(kd->left, mapping, query, keys, data, min_diff, 
                       depth + NEXT_DEPTH);
        } else {
            nearSearch(kd->right, mapping, query, keys, data, min_diff, 
                       depth + NEXT_DEPTH);
        }     
    } else {
        nearSearch(kd->left, mapping, query, keys, 
                   data, min_diff, depth + NEXT_DEPTH);
        nearSearch(kd->right, mapping, query, keys, 
                   data, min_diff, depth + NEXT_DEPTH);
    }
}


/*
    Search for the key in the given K-D tree and put the data in the given location
    According to radius.
*/
void radiusSearch(struct kd *kd, struct dataMapping *mapping, struct key *query, 
    struct key ***keys ,struct data ***data, double radius, int depth, int foundMatches){
    if(!kd) return;
    
    // To get the distance between query and current node
    double distance;
    distance = getD(kd->key, query);
    if (distance<radius){
        int foundMatches = 0;
        // Chaining situation
        struct kd *dup = kd->chain;
        while(dup != NULL){
            int foundMatches = 0;
            assignData(dup, data, keys, foundMatches);            
            dup = dup->chain; 
        }
        assignData(kd, data, keys, foundMatches);     
        radiusSearch(kd->left, mapping, query, keys, data, radius, 
                     depth + NEXT_DEPTH, foundMatches);
        radiusSearch(kd->right, mapping, query, keys, data, radius, 
                     depth + NEXT_DEPTH, foundMatches);
        freeDUP(dup, mapping);
    } else {
        double query_diff = getQD(kd->key, query, depth);
        if(query_diff > radius){
            if(checkingKey(kd->key, query, depth)){
                radiusSearch(kd->left, mapping, query, keys, data, 
                             radius,  depth + NEXT_DEPTH, foundMatches);
            } else {
                radiusSearch(kd->right, mapping, query, keys, data, radius, 
                             depth + NEXT_DEPTH, foundMatches);
                }
        } else {
            radiusSearch(kd->left, mapping, query, keys, data, radius, 
                         depth + NEXT_DEPTH, foundMatches);
            radiusSearch(kd->right, mapping, query, keys, data, radius, 
                         depth + NEXT_DEPTH, foundMatches);
        }       
    }
}

void searching(struct kd *kd, struct dataMapping *mapping, struct key *query, 
    struct key ***keys ,struct data ***data){
    /* NULL terminated array. */
    *data = (struct data **) malloc(sizeof(struct data *));
    **data = NULL;
    *keys = (struct key **) malloc(sizeof(struct key *));
    **keys = NULL;
    int depth = ROOT_DEPTH;
    if(mapping->keyCount == 2){
        double min_diff = DBL_MAX;
        nearSearch(kd, mapping, query, keys, data, &min_diff, depth);
    } else {
        double radius = atof(query->keys[2]);
        int foundMatches = 0;
        radiusSearch(kd, mapping, query, keys, data, radius, depth, foundMatches);
    }    
}

void freeKD(struct kd *kd, struct dataMapping *mapping){
    if(!kd) {return;}
    freeKD(kd->left, mapping);
    freeKD(kd->right, mapping);
    if(kd->chain){freeDUP(kd->chain, mapping);}
    freeKeyPair(&(kd->data), &(kd->key), mapping);
    if(kd){free(kd);}
}

void freeDUP(struct kd *kd, struct dataMapping *mapping){
    struct kd *cur = kd, *next;
    while(cur){
        next = cur->chain;
        freeKeyPair(&(cur->data), &(cur->key), mapping);
        free(cur);
        cur = next;
    }
}
