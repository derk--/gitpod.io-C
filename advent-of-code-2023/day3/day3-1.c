#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define DIM 140
#define BUF_MAX 1024

void null_buf(char* buf){
    for(int i=0; i < BUF_MAX; i++){
        buf[i] = '\0';
    }
}

int is_valid(int row_idx, int digit, int col_start, int col_end, char schematic[DIM][DIM]){
    int i=0;
    char area[BUF_MAX]; 
    null_buf(area);

     // First get left side.
    if(col_start > 0){
        area[i++] = schematic[row_idx][col_start - 1];
        if(row_idx > 0)
            area[i++] = schematic[row_idx - 1][col_start - 1];
        if(row_idx < DIM-1)
            area[i++] = schematic[row_idx + 1][col_start - 1];
    }
    // now get right side.
    if(col_end < DIM-1){
        area[i++] = schematic[row_idx][col_end + 1];
        if(row_idx > 0)
             area[i++] = schematic[row_idx - 1][col_end + 1];
        if(row_idx < DIM-1)
            area[i++] = schematic[row_idx + 1][col_end + 1];
    }
    /* now check top and bottom.*/
    for(int j=col_start; j <= col_end; j++){
        if(row_idx > 0)
            area[i++] = schematic[row_idx - 1][j];
        if(row_idx < DIM-1)
            area[i++] = schematic[row_idx + 1][j];
    }
    //scan area buffer to see if there are no symbols.
    char test[BUF_MAX];
    null_buf(test);
    for(int k =0; k < i; k++){
        test[k] = '.';
    }
    if(strcmp(test, area)){
        //the area is different; the number is adjacent to a symbol.
        return digit;
    }
    return 0;
}

int scan_line(int row_idx, char schematic[DIM][DIM]){
    char* line = schematic[row_idx]; //this is not a string 
    int digit_start = -1;
    int digit_end = -1;
    int j=0;
    int buf_i = 0;
    char digit_buf[BUF_MAX];
    int line_val = 0;
    
    null_buf(digit_buf);
    //printf("%s\n", line);
    while(j <= DIM){ //need to check past last column to catch digit @ end of line
        char cur = line[j];
        if(isdigit(cur)){
            digit_buf[buf_i++] = cur;
            digit_start = digit_start < 0 ? j : digit_start;
        }
        //@ a character. 
        else if(digit_start > -1 && digit_end < 0) {
                digit_end = j-1; //its the character after the digit. 
        }
        if(digit_start > -1 && digit_end > -1){
            //check if digit is valid. 
            int digit = strtol(digit_buf, NULL, 10);
            line_val += is_valid(row_idx, digit, digit_start, digit_end, schematic);
            //reset digit_start and end, and the buffer
            digit_start = -1;
            digit_end = -1;
            null_buf(digit_buf);
            buf_i = 0;
        }
        j++;
    }
    return line_val;
}


int main(){

    char schematic[DIM][DIM];
    char row[BUF_MAX];
    int solution = 0;

    FILE* input_file = fopen("/workspace/gitpod.io-C/advent-of-code-2023/day3/day3-input.txt", "r");
    int i = 0;
    while(fgets(row, BUF_MAX, input_file)){
        for(int j=0; j < DIM; j++){
            schematic[i][j] = row[j];
        }
        i++;
    }
    for(int i=0; i < DIM; i++){
        int line_val = scan_line(i, schematic);
        printf("Line: %d - %d\n", i, line_val);
        solution += line_val;
        printf("Solution: %d\n", solution);

    }
    printf("\nSolution: %d\n", solution);

    return 0;
}