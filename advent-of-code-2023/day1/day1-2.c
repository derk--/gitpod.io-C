#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define NUMBERS "0123456789"

int num_check(char* string, int index){
    for(int i=0; i<10; i++){
        if(string[index] == NUMBERS[i]){
            char ret[] = {string[index], '\0'};
            return strtol(ret, NULL, 10);
        }
    }
    if(
        string[index] == 'o' &&
        string[index+1] == 'n' &&
        string[index+2] == 'e') { return 1; }
    if(
        string[index] == 't' &&
        string[index+1] == 'w' &&
        string[index+2] == 'o') { return 2;}
    if(
        string[index] == 't' &&
        string[index+1] == 'h' &&
        string[index+2] == 'r' &&
        string[index+3] == 'e' &&
        string[index+4] == 'e') { return 3;}
    if(
        string[index] == 'f' &&
        string[index+1] == 'o' &&
        string[index+2] == 'u' &&
        string[index+3] == 'r') { return 4;}
    if(
        string[index] == 'f' &&
        string[index+1] == 'i' &&
        string[index+2] == 'v' &&
        string[index+3] == 'e') { return 5;}
    if(
        string[index] == 's' &&
        string[index+1] == 'i' &&
        string[index+2] == 'x') { return 6;}
    if(
        string[index] == 's' &&
        string[index+1] == 'e' &&
        string[index+2] == 'v' &&
        string[index+3] == 'e' &&
        string[index+4] == 'n') { return 7; }
    if(
        string[index] == 'e' &&
        string[index+1] == 'i' &&
        string[index+2] == 'g' &&
        string[index+3] == 'h' &&
        string[index+4] == 't') { return 8;}
    if(
        string[index] == 'n' &&
        string[index+1] == 'i' &&
        string[index+2] == 'n' &&
        string[index+3] == 'e') { return 9;}
    return -1;
}

int main(){
    FILE* input_file = fopen("day1-input.txt", "r");
    char line[MAX_LINE_LENGTH];
    int value_low;
    int value_high;
    int sum = 0;
    while(fgets(line, MAX_LINE_LENGTH, input_file)){
        int i = 0;
        value_low = -1;
        value_high = -1;
        while(line[i] != '\0'){
            int scanned_val = num_check(line,i); 
            if(value_low < 0){
                value_low = scanned_val;
                value_high = value_low;
            }
            if(value_high >= 0 && scanned_val >= 0){
                value_high = scanned_val;
            }
            i++;
        }
       sum += 10*value_low + value_high;
    }
    printf("Sum is: %d\n", sum);
    return 0;
}