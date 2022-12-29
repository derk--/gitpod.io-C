#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define STACK_COUNT 3

void push(char* stack, char item){
    char str_item[2] = {item, '\0'};
    strcat(stack, str_item);
}

char pop(char* stack){
    char ret = stack[strlen(stack) - 1];
    stack[strlen(stack) - 1] = '\0';
    return ret;
}
    
int calculate_max_stack(FILE* input_file){
    fseek(input_file, 0, SEEK_SET);
    char input_line[100];
    int max_size = 0;
    while(fgets(input_line, 100, input_file)){
        for (int i=0; input_line[i] != '\0'; i++){
            max_size += input_line[i] == '[';
        }
    }
    return max_size;
}

void init_stacks(char* stacks[STACK_COUNT], FILE* input_file){
    char input_line[100];
    for(int i=0; i < STACK_COUNT; i++){
        stacks[i] = (char *)malloc(sizeof(char) * calculate_max_stack(input_file));
    }
    fseek(input_file, 0, SEEK_SET);
    while(fgets(input_line,100,input_file)){
        if(input_line[0] == '['){
            push(stacks[0], input_line[1]);
        }
        if(input_line[4] == '['){
            push(stacks[1], input_line[5]);
        }
        if(input_line[8] == '['){
            push(stacks[2], input_line[9]);            
        }
    }
}

void print_stacks(char* stacks[STACK_COUNT]){
    for(int i=0; i < STACK_COUNT; i++){
        printf("%s\n", stacks[i]);
    }
}

int main(){

    FILE* input_file = fopen("test.txt","r");

    char* stacks[STACK_COUNT];
    rewind(input_file);

    init_stacks(stacks, input_file);

    printf("Initial stacks:\n");
    print_stacks(stacks);

    fseek(input_file, 0, SEEK_SET);

    return 0;
}
