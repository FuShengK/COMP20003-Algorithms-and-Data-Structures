#include <time.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

#include "ai.h"
#include "utils.h"
#include "hashtable.h"
#include "stack.h"
#define DIRECTION 4
#define RANDOM_NUM 1

void copy_state(state_t* dst, state_t* src){
	
	//Copy field
	memcpy( dst->field, src->field, SIZE*SIZE*sizeof(int8_t) );

	dst->cursor = src->cursor;
	dst->selected = src->selected;
}

/**
 * Saves the path up to the node as the best solution found so far
*/
void save_solution( node_t* solution_node ){ 
	node_t* n = solution_node;
	while( n->parent != NULL ){
		copy_state( &(solution[n->depth]), &(n->state) );
		solution_moves[n->depth-1] = n->move;
		n = n->parent;
	}
	solution_size = solution_node->depth;
}


node_t* create_init_node( state_t* init_state ){
	node_t * new_n = (node_t *) malloc(sizeof(node_t));
	new_n->parent = NULL;
	new_n->depth = 0;
	copy_state(&(new_n->state), init_state);
    
	return new_n;
}

/**
 * Apply an action to node n and return a new node resulting from executing the action
*/
node_t* applyAction(node_t* n, position_s* selected_peg, move_t action ){
    node_t* new_node = NULL;
    new_node = create_init_node( &n->state );
    new_node->parent = n;
    new_node->state.cursor.x = selected_peg->x;
    new_node->state.cursor.y = selected_peg->y;
    new_node->depth = n->depth+1;
    new_node->move = action;
    execute_move_t( &(new_node->state), &(new_node->state.cursor), action);
	
    return new_node;
}

/**
 * Find a solution path as per algorithm description in the handout
 */

void find_solution( state_t* init_state  ){
    
    int value = RANDOM_NUM;
	HashTable table;
	// Choose initial capacity of PRIME NUMBER 
	// Specify the size of the keys and values you want to store once 
	ht_setup( &table, sizeof(int8_t) * SIZE * SIZE, sizeof(int8_t) * SIZE * SIZE, 16769023);
    list_t* bye = make_empty_list();
	// Initialize Stack
	initialize_stack();
    
	//Add the initial node
	node_t* check = create_init_node( init_state ); 
    stack_push(check);
    ht_insert(&table, &check->state, &value);
    //GRAPH ALGORITHM
    int remain_pegs = num_pegs(&check->state);

    while(!is_stack_empty()){     
        node_t* n = popping();
        expanded_nodes++;
        bye = insert_at_foot(bye, n);
        if(num_pegs(&n->state) < remain_pegs){
            save_solution(n);
            remain_pegs = num_pegs(&n->state);
        }
        for(int i=0; i<SIZE; i++){
            for(int j=0; j<SIZE; j++){
                for(int action=0; action<DIRECTION; action++){
                    position_s p = {i, j};
                    if(can_apply(&n->state, &p, action)){
                        node_t* new_node = applyAction(n, &p, action);
                        generated_nodes++;
                        if(won(&new_node->state)){
                            save_solution(new_node);
                            remain_pegs = num_pegs(&new_node->state);
                            free_pack(&table); 
                            free_list(bye);
                            free(new_node);
                            return;
                        } 
                        if(ht_contains(&table, &new_node->state.field)){
                            free(new_node);
                            continue;
                        } else if ( !ht_contains(&table, &new_node->state.field)){
                            stack_push(new_node);
                            ht_insert(&table, &new_node->state.field, 
                                      &value);
                        } 
                    }                     
                }
            }
        }
        if(expanded_nodes >= budget){
            free_pack(&table);
            free_list(bye);
            return; 
        }  
    }
}

void free_pack(HashTable* table){  
    free_stack();
    ht_destroy(table);
}