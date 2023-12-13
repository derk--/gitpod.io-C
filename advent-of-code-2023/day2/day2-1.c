#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LINE_SIZE 1024

int game_plausible(char* string, int max_red, int max_green, int max_blue){
    //game, red, green, blue
    //Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green

    //get the game number
    char* cur_str_ptr = strchr(string, ':');
    char game_label[cur_str_ptr - string]; 
    strncpy(game_label, string, cur_str_ptr - string);
    int game_num = strtol(strchr(game_label, ' ')+1, NULL, 10);
    printf("%d\n", game_num);

    //move the pointer index up to the start of the first pull
    cur_str_ptr = cur_str_ptr + 2;
    
    char* pull_str_end = strchr(cur_str_ptr, ';');
    do{
        while(cur_str_ptr < pull_str_end){
                printf("%X\n", cur_str_ptr);
                printf("%X\n", pull_str_end);

                char* val_ptr = strchr(cur_str_ptr, ' ');
                printf("%X\n", val_ptr);

                char val_buffer[val_ptr - cur_str_ptr];
                strncpy(val_buffer, cur_str_ptr, val_ptr - cur_str_ptr);
                int val = strtol(val_buffer, NULL, 10);
                printf("%d\n", val);
                cur_str_ptr = val_ptr;

                char* color_ptr = strchr(cur_str_ptr, ',');
                char color_buffer[color_ptr - cur_str_ptr];
                strncpy(color_buffer, cur_str_ptr+1, color_ptr - cur_str_ptr-1); 
                if((color_buffer[0] == 'r' && val > max_red)   ||
                (color_buffer[0] == 'g' && val > max_green) ||
                (color_buffer[0] == 'b' && val > max_blue)  ){
                    return 0;
                }
                cur_str_ptr = color_ptr + 2;
            }
            pull_str_end = strchr(cur_str_ptr, ';');
    } while(pull_str_end);
    return game_num;
}

int main(){
    FILE* input_file = fopen("day2-input.txt", "r");
    char line[MAX_LINE_SIZE];
    while(fgets(line, MAX_LINE_SIZE, input_file)){
        printf("--> %d\n", game_plausible(line, 12, 13, 14));
    }
}