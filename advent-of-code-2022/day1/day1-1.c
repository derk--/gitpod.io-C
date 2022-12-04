#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 7

int main(){
    FILE* input_file = fopen("day1-input.txt", "r");
    char line[MAX_LINE_LENGTH];
    int max_cal = -1;
    int cal_count = 0;
    while(fgets(line, MAX_LINE_LENGTH, input_file)){
        if(line[0] == '\n'){
            if(cal_count > max_cal){
                max_cal = cal_count;
            }
            cal_count = 0;
        }
        else{
            cal_count += atoi(line);
        }
    }
    printf("Max calroies: %d\n", max_cal);
    return 0;
}