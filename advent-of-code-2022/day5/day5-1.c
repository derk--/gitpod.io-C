#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define STACK_COUNT 9
#define BUFFER_SIZE 1024

void push(char* stack, char item){
    char str_item[2] = {item, '\0'};
    strcat(stack, str_item);
}

char pop(char* stack){
    int len = strlen(stack);
    char ret = stack[len-1];
    stack[len-1] = '\0';
    return ret;
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
    for(int i=0; i < STACK_COUNT; i++){
        stacks[i] = (char *)malloc(sizeof(char) * calculate_max_stack(input_file));
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
    char input_line[BUFFER_SIZE], val;
    int move_count, source, target;

    fseek(input_file, 0, SEEK_SET);
    while(fgets(input_line,BUFFER_SIZE,input_file)){
        if(input_line[0] == 'm'){
            sscanf(input_line, "move %d from %d to %d", &move_count, &source, &target);
            for(int i=0; i < move_count; i++){
                val = pop(stacks[source-1]);
                push(stacks[target-1], val);
                printf("stacks after move from %d to %d:\n", source, target);
                print_stacks(stacks);
            }
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
