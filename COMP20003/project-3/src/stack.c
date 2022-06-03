#include<stdio.h>
#include "stack.h"
#include "utils.h"


void initialize_stack(){ stack_top_idx = -1;}

void stack_push(node_t* n) {
  if(stack_top_idx == STACK_SIZE -1) { // overflow case. 
		printf("Error: stack overflow\n");
		return;
	}
	stack[++stack_top_idx] = n;
}

void stack_pop() {
	if(stack_top_idx == -1) { // If stack is empty, pop should throw error. 
		printf("Error: No element to pop\n");
		return;
	}
	stack_top_idx--;
}

/*
 * I add some and change the name to simplify my pop process
*/
node_t* popping() { 
    node_t* new_node = stack[stack_top_idx];
    stack_pop();
    return new_node; 
}

int is_stack_empty() {
    if(stack_top_idx == -1) return 1;
    return 0;
}

void print_stack() {
	printf("Stack: ");
	for(int i = 0;i<=stack_top_idx;i++)
		drawBoard( &(stack[i]->state) );
	printf("\n");
}

void free_stack() {
	for(int i = 0;i<=stack_top_idx;i++)
		free(stack[i]);
    stack_top_idx = -1;
	printf("\n");
}
