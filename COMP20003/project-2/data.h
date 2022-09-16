/*
    This defines prototypes for data-related functions.
*/

struct data;

struct key;

struct dataMapping;

/*
    Read the given line and store the mapping from row to values.
*/
struct dataMapping *getDataMapping(char *header, int check);

/*
    Read a line into the given key and data locations.
*/
void getData(char *row, struct dataMapping *mapping, struct key **key, 
    struct data **data, int check);

/*
    Read a line as a key and return it.
*/
struct key *readKey(char *row, struct dataMapping *mapping);

    
/*
    Frees the key and data in the given pair.
*/
void freeKeyPair(struct data **dataLoc, struct key **keyLoc, struct dataMapping *mapping);

/*
    Frees a standalone key.
*/
void freeKey(struct key **keyLoc, struct dataMapping *mapping);

/*
    Frees the given data mapping.
*/
void freeDataMapping(struct dataMapping **mapping);

/*
    Allocates space for a string representing the given
    key and returns it.
*/
char *getKeyString(struct dataMapping *mapping, struct key *key);

/*
    Allocates space for a string representing the given
    data and returns it.
*/
char *getDataString(struct dataMapping *mapping, struct data *data);

/*
    To get Distance from point to point
*/
double getD(struct key *key, struct key *query);

/*
    To get Distance from x-points or y-points
*/
double getQD(struct key *key, struct key *query, int depth);

/*
    To check keys'value and if they are the same based on depth
*/
int checkingKey(struct key *key, struct key *tmpKey, int depth);