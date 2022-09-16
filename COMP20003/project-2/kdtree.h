/*
    This defines prototypes for K-D tree-related functions.
*/

#include "data.h"

struct kd;

/* 
    Creates an empty linked list.
*/
struct kd *newKD();

/*
    Prepend the item in the line to the given K-D tree.
*/
struct kd *insertToKD(struct kd *kd, struct dataMapping *mapping, char *row, int depth, int check);


/*
    Search for the key in the given K-D tree and put the data in the given location.
*/
void searching(struct kd *kd, struct dataMapping *mapping, struct key *query, 
    struct key ***keys ,struct data ***data);

/*
    To free up memories from K-D tree;
*/
void freeKD(struct kd *kd, struct dataMapping *mapping);

