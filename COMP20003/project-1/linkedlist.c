#include "linkedlist.h"

/*
 * To search the key in list then copy the data to results list
*/
int searching(l_t *linking, char* key, l_t* results){
    assert(linking!=NULL && linking->head!=NULL);
    int found=0;
    seg_t *cur = linking->head;
    while(cur!=NULL){
        if(!strcmp(cur->trading_name, key)){
            seg_t *new_seg = copying(cur);
            new_seg->next = results->head;
            results->head = new_seg;
            found = 1;
        }
        cur = cur->next;
    }
    free(cur);
    return found;
}
/*
 * Make empty list
 */
l_t *empty_list(void){
    l_t *linking;
    linking = (l_t*)malloc(sizeof(*linking));
    assert(linking!=NULL);
    linking->head=NULL;
    return linking;
}
/*
 * Insert into the linked-list
*/
l_t *insert_head(l_t *linking, seg_t *new_seg){
    assert(linking!=NULL && new_seg!=NULL);
    new_seg->next=linking->head;
    linking->head = new_seg;
    return linking;
}
/*
 * Purely copy the data of segment
*/
seg_t *copying(seg_t *old){
    seg_t *ans;
    ans = (seg_t*)malloc(sizeof(*ans));
    strcpy(ans->census_year, old->census_year);
    strcpy(ans->block_id, old->block_id);
    strcpy(ans->property_id, old->property_id);
    strcpy(ans->base_property_id, old->base_property_id);
    strcpy(ans->clue_small_area, old->clue_small_area);
    strcpy(ans->trading_name, old->trading_name);
    strcpy(ans->industry_code, old->industry_code);
    strcpy(ans->industry_description, old->industry_description);
    strcpy(ans->x_coordinate, old->x_coordinate);
    strcpy(ans->y_coordinate, old->y_coordinate);
    strcpy(ans->location, old->location);
    ans->next = NULL;
    return ans;
}
/*
 * To free up the superfluous space and memory
 */
void free_list(l_t *linking){
    seg_t *tmp;
    seg_t *head = linking->head;
    while(head!=NULL){
        tmp = head;
        head = head->next;
        free(tmp);
    }
    free(head);
    free(linking);
}
/*
 * To build segment with proper attributes
*/
seg_t *build_seg(char *record[ATTRIBUTES]){
    seg_t *ans;
    ans = (seg_t*)malloc(sizeof(*ans));
    ans->next = NULL;
    strcpy(ans->census_year, record[0]);
    strcpy(ans->block_id, record[1]);
    strcpy(ans->property_id, record[2]);
    strcpy(ans->base_property_id, record[3]);
    strcpy(ans->clue_small_area, record[4]);
    strcpy(ans->trading_name, record[5]);
    strcpy(ans->industry_code, record[6]);
    strcpy(ans->industry_description, record[7]);
    strcpy(ans->x_coordinate, record[8]);
    strcpy(ans->y_coordinate, record[9]);
    strcpy(ans->location, record[10]);
    return ans;
}
