#include <stdio.h>
#include <string.h>

/* Now, find what is common across 3 consecutive lines.*/
int main(){ 

    FILE* input_file = fopen("test.txt","r");
    char input_line[20];
    while(fgets(input_line, 20, input_file)){
        int line_len = strlen(input_line);
        char* comma = strchr(input_line, ',');
        int elf_1_assignment_length = comma - input_line;
        int elf_2_assignment_length = line_len - elf_1_assignment_length + 1;

        char elf_1_assignment[6]; //max size = 5, since zones are 0-99, +1 for null terminator.
        elf_1_assignment[elf_1_assignment_length] = '\0';
        strncpy(elf_1_assignment, input_line, elf_1_assignment_length);
        
        char elf_2_assignment[6];
        elf_2_assignment[elf_2_assignment_length] = '\0';
        strncpy(elf_2_assignment, &input_line[elf_1_assignment_length+1], elf_2_assignment_length);

        printf("Elf 1: %d, %s\n", elf_1_assignment_length, elf_1_assignment);
        printf("Elf 2: %d, %s\n", elf_2_assignment_length, elf_2_assignment);

        int elf1_l, elf1_r, elf2_l, elf2_r; 
        

    }
    return 0;
}
/*
12-64,11-11
7-83,5-91
*/