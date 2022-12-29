#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define STACK_COUNT 9
#define BUFFER_SIZE 1024

/* In this scenario, we are pushing stacks on top of other stacks, appending them.*/
void push(char* target_stack, char* items){
    strcat(target_stack, items);
}

/* In this scenario, we "pop" k items at once. In one pop operation, pull out 
the top k elements from the stack, and do not disturb the order of the elements stacked. 
i.e., stack 1234567 , pop @ k =3, now stack is 1234, and the element popped is the stack 567.*/
void pop(char* ret, char* stack, int k){
    int len = strlen(stack);
    for(int i=0; i<k; i++){
        ret[i] = stack[(len - k + i)];
    }
    ret[k] = '\0';
    stack[len - k] = '\0';
}

void print_stacks(char* stacks[STACK_COUNT]){
    for(int i=0; i < STACK_COUNT; i++){
        printf("%s\n", stacks[i]);
    }
}
    
int calculate_max_stack(FILE* input_file){
    fseek(input_file, 0, SEEK_SET);
    char input_line[BUFFER_SIZE];
    int max_size = 0;
    while(fgets(input_line, 100, input_file)){
        for (int i=0; input_line[i] != '\0'; i++){
            max_size += input_line[i] == '[';
        }
    }
    return max_size;
}

/* We need this routine because when we read the stack setup from the file, 
   we read the element at the top of the stack first, going down to the bottom.
   So we can't push, when we read a new value during setup, we need to add it 
   _to the bottom_ of the stack. */
void stack_add_during_init(char* stack, char add){
    char to_push[2] = {add, '\0'};
    memmove(stack + 1, stack, strlen(stack) + 1);
    memcpy(stack, to_push, 1);
}

void init_stacks(char* stacks[STACK_COUNT], FILE* input_file){
    char input_line[BUFFER_SIZE];
    int max_stack_size = calculate_max_stack(input_file);
    for(int i=0; i < STACK_COUNT; i++){
        stacks[i] = (char *)malloc(sizeof(char) * max_stack_size);
    }
    fseek(input_file, 0, SEEK_SET);
    while(fgets(input_line,BUFFER_SIZE,input_file)){
        for(int i=0; i < strlen(input_line); i++){
            if(input_line[i] == '[')
                stack_add_during_init(stacks[i/4], input_line[i+1]);         
        }
    }
}

void move_items(char* stacks[STACK_COUNT], FILE* input_file){
    char input_line[BUFFER_SIZE];
    int move_count, source, target;

    fseek(input_file, 0, SEEK_SET);
    while(fgets(input_line,BUFFER_SIZE,input_file)){
        if(input_line[0] == 'm'){
            sscanf(input_line, "move %d from %d to %d", &move_count, &source, &target);
            char* val = (char*)malloc(sizeof(char)*move_count);
            pop(val, stacks[source - 1], move_count);
            push(stacks[target-1], val);
            free(val);
            printf("stacks after move %d from %d to %d:\n", move_count, source, target);
            print_stacks(stacks);
        }
    }
}


int main(){

    FILE* input_file = fopen("day5-input.txt","r");

    char* stacks[STACK_COUNT];
    init_stacks(stacks, input_file);

    printf("Initial stacks:\n");
    print_stacks(stacks);

    move_items(stacks, input_file);

    printf("Final stacks: \n");
    print_stacks(stacks);

    return 0;
}
