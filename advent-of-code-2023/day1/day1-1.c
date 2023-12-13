#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define NUMBERS "0123456789"

int main(){
    FILE* input_file = fopen("day1-input.txt", "r");
    char line[MAX_LINE_LENGTH];
    char value_low;
    char value_high;
    int sum = 0;
    while(fgets(line, MAX_LINE_LENGTH, input_file)){
        int i = 0;
        value_low = 'x';
        value_high = 'x';
        while(line[i] != '\0'){
            for(int j=0; j<10; j++){
                if(line[i] == NUMBERS[j]){
                    if(value_low == 'x'){
                        value_low = NUMBERS[j];
                        value_high = value_low;
                    } else {
                        value_high = NUMBERS[j];
                    }
                    break;
                }
            }
            i++;
        }
       char v[3] = {value_low, value_high, '\0'};
       sum += strtol(v, NULL, 10);
    }
    printf("Sum is: %d\n", sum);
    return 0;
}