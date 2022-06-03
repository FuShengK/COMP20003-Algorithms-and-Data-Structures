#include "linkedlist.h"

int main(int argc, char const *argv[]){
    char in_file[HALF_MAX_LEN], out_file[HALF_MAX_LEN];
    strcpy(in_file, argv[INPUT]);
    strcpy(out_file, argv[OUTPUT]);
    FILE* f = fopen(in_file, "r");
    char strings[MAX_LENGTH];
    fgets(strings, MAX_LENGTH, f);

    l_t *new_list = empty_list();
    while(fgets(strings, MAX_LENGTH, f)){
        char *tmp = strdup(strings);
        char *record[ATTRIBUTES];
        int quote_num = counts(tmp);

        //build my dictionary
        get_seg(record, tmp, quote_num);
        seg_t *new_seg = build_seg(record);
        insert_head(new_list, new_seg);
        free(tmp);

    }
    l_t *results = empty_list();
    l_t *not_found = empty_list();
	while(fgets(strings, MAX_LENGTH, stdin)){
        char* search_key = strdup(strings);
        strtok(search_key, "\n");
        int found;
        //To check if the new_list contains key then add in results
        //vice versa and put in not found list
        found = searching(new_list, search_key, results);
        if(found==0){
            seg_t *notfound_seg = (seg_t*)malloc(sizeof(*notfound_seg));
            notfound_seg->next=NULL;
            strcpy(notfound_seg->trading_name, search_key);
            insert_head(not_found, notfound_seg);
        }
        free(search_key);
    }

    FILE *out;
    out = fopen(out_file, "w");
    while(results->head!=NULL){
		results->head->location[strlen(results->head->location)] = END_SIGN;
        fprintf(out, "%s --> Census year: %s || Block ID: %s || Property ID: %s || Base property ID: %s || CLUE small area: %s || Industry (ANZSIC4) code: %s || Industry (ANZSIC4) description: %s || x coordinate: %s || y coordinate: %s || Location: %s ||\n", results->head->trading_name, results->head->census_year, results->head->block_id, results->head->property_id, results->head->base_property_id, results->head->clue_small_area, results->head->industry_code, results->head->industry_description, results->head->x_coordinate, results->head->y_coordinate, results->head->location);
        results->head = results->head->next;
    }
    while(not_found->head!=NULL){
        fprintf(out, "%s --> NOTFOUND\n", not_found->head->trading_name);
        not_found->head = not_found->head->next;
    }

    free_list(new_list);
    free_list(results);
    free_list(not_found);
    fclose(f);
    fclose(out);
    return 0;
}
/*
 * To get the attributes from each segment
*/
void get_seg(char* record[ATTRIBUTES], char* strings, int quote_num){

    int index = 0;
    if(quote_num==2){
        char *tok;
        for(tok=strtok(strings, COMMA); tok && *tok; tok= strtok(NULL, END)){

            // Make sure the location is in a proper representation
            if(index==10){
                record[index] = (char*)calloc(CHARACTERS, sizeof(char));
                strcpy(record[index], tok);
                index++;
                continue;
            }
            if(index==11){
                strcat(record[index-1], tok);
                char* tmp = (char*)calloc(CHARACTERS, sizeof(char));
                strncpy(tmp, record[index-1] + 1, (int)strlen(record[index-1]) - 3);
                record[index-1] = tmp;
                record[index-1][(int)strlen(tmp)] = END_SIGN;
                continue;
            }
            record[index] = (char*)calloc(CHARACTERS, sizeof(char));
            strcpy(record[index], tok);
            index++;
			record[index] = END_SIGN;
        }
   }
   if(quote_num == 4){
        int index_quote[4];
        char *tok;
        indexing(strings, index_quote);
        char *A = (char*)calloc(index_quote[0]-1 ,sizeof(char*));
        char *B = (char*)calloc(index_quote[1]-index_quote[0]-1 ,sizeof(char*));
        char *C = (char*)calloc(index_quote[2]-index_quote[1]-3 ,sizeof(char*));
        char *D = (char*)calloc(index_quote[3]-index_quote[2]-1 ,sizeof(char*));

        //Make four parts by being separate by quote
        strncpy(A, strings, index_quote[0]-1);
        A[index_quote[0]-1] = END_SIGN;
        strncpy(B, strings+index_quote[0]+1, index_quote[1]-index_quote[0]-1);
		B[index_quote[1]-index_quote[0]-1] = END_SIGN;
        strncpy(C, strings+index_quote[1]+2, index_quote[2]-index_quote[1]-3);
		C[index_quote[2]-index_quote[1]-3] = END_SIGN;
        strncpy(D, strings+index_quote[2]+1, index_quote[3]-index_quote[2]-1);
        D[index_quote[3]-index_quote[2]-1] = END_SIGN;

        //put them into record array and make sure it will display correctly
        for(tok=strtok(A, COMMA); tok && *tok; tok= strtok(NULL, END)){
            record[index] = strdup(tok);
            index++;
        }
        free(A);
        record[index] = strdup(B);
        index++;
        free(B);
        for(tok=strtok(C, COMMA); tok && *tok; tok= strtok(NULL, END)){
            record[index] = strdup(tok);
            index++;
        }
        free(C);
        record[index] = strdup(D);
        free(D);
    }
}
/*
 * To know the position of each quote
*/
void indexing(char* strings, int* index_quote){
    int count = 0, index = 0;
    while(strings[count] != END_SIGN){
        if(strings[count] == QUOTE_SIGN){
            index_quote[index] = count;
            index++;
            count++;
        }
        count++;
    }
}
/*
 * Get the number of quotes
*/
int counts(char* strings){
    int count = 0, index = 0;
    while(strings[index] != END_SIGN){
        if(strings[index] == QUOTE_SIGN){
            index++;
            count++;
        }
        index++;
    }
    return count;
}
