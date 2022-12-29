#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
    Split a string into two null terminated strings at (and excluding) delim.
**/
void split_str(char* left, char* right, char* line, char delim){
    int line_len = strlen(line);
    char* split_loc = strchr(line, delim);
    int l = split_loc - line; 
    int r = line_len - l + 1; 
    strncpy(left, line, l); 
    strncpy(right, &line[l + 1], r);
    left[l] = '\0';
    right[r] = '\0';
}

int main(){ 
    int count = 0;
    FILE* input_file = fopen("day4-input.txt","r");
    char input_line[20];
    while(fgets(input_line, 20, input_file)){
        char elf_1_assignment[6], elf_2_assignment[6];
        split_str(elf_1_assignment, elf_2_assignment, input_line, ',');
        printf("Elf 1: %s\n", elf_1_assignment);
        printf("Elf 2: %s\n", elf_2_assignment);

        char elf1_l[3], elf1_r[3], elf2_l[3], elf2_r[3];
        split_str(elf1_l, elf1_r, elf_1_assignment, '-');
        split_str(elf2_l, elf2_r, elf_2_assignment, '-'); 
        count +=
            (atoi(elf1_l) >= atoi(elf2_l) && atoi(elf1_r) <= atoi(elf2_r)) ||
            (atoi(elf1_l) >= atoi(elf2_l) && atoi(elf1_l) <= atoi(elf2_r)) ||
            (atoi(elf2_l) >= atoi(elf1_l) && atoi(elf2_r) <= atoi(elf1_r)) ||
            (atoi(elf2_l) >= atoi(elf1_l) && atoi(elf2_l) <= atoi(elf1_r)) ||
            (atoi(elf1_r) <= atoi(elf2_r) && atoi(elf1_r) >= atoi(elf2_r)) ||
            (atoi(elf1_r) <= atoi(elf2_r) && atoi(elf1_l) >= atoi(elf2_r)) ||
            (atoi(elf2_r) <= atoi(elf1_r) && atoi(elf2_r) >= atoi(elf1_r)) ||
            (atoi(elf2_r) <= atoi(elf1_r) && atoi(elf2_l) >= atoi(elf1_r)) ;
    }
    printf("Containment count: %d\n", count);
    return 0;
}