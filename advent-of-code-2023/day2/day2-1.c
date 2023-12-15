#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LINE_SIZE 1024

void replace_semi(char* string){
    char* semi_loc = strchr(string, ';');
    while(semi_loc){
        *semi_loc = ',';
        semi_loc = strchr(string, ';');
    }
}

int game_plausible(char* string, int max_red, int max_green, int max_blue){
    //game, red, green, blue
    //Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green

    replace_semi(string);
    printf("%s", string);

    //get the game number
    char* cur_str_ptr = strchr(string, ':');
    char game_label[cur_str_ptr - string]; 
    strncpy(game_label, string, cur_str_ptr - string);
    int game_num = strtol(strchr(game_label, ' ')+1, NULL, 10);

    //move the pointer index up to the start of the first pull
    cur_str_ptr = cur_str_ptr + 2;
    
    while(cur_str_ptr){

        char* eos = strchr(cur_str_ptr, '\0');
        printf("%s", *eos);
        char* val_ptr = strchr(cur_str_ptr, ' '); 
        printf("%s", cur_str_ptr);

        char val_buffer[val_ptr - cur_str_ptr];
        strncpy(val_buffer, cur_str_ptr, val_ptr - cur_str_ptr);

        int val = strtol(val_buffer, NULL, 10);
        printf("%d\n", val);
        cur_str_ptr = val_ptr;
        printf("Now cur_str_ptr: %s", cur_str_ptr);

        char* color_ptr = strchr(cur_str_ptr, ',');
        char color_buffer[color_ptr - cur_str_ptr];
        strncpy(color_buffer, cur_str_ptr+1, color_ptr - cur_str_ptr); 

        printf("%s\n", color_buffer);
        if((color_buffer[0] == 'r' && val > max_red)   ||
        (color_buffer[0] == 'g' && val > max_green) ||
        (color_buffer[0] == 'b' && val > max_blue)  ){
            return 0;
        }
        cur_str_ptr = color_ptr + 2;
    }
    return game_num;
}

int main(){
    FILE* input_file = fopen("day2-input.txt", "r");
    char line[MAX_LINE_SIZE];
    while(fgets(line, MAX_LINE_SIZE, input_file)){
        printf("--> %d\n", game_plausible(line, 12, 13, 14));
    }
}