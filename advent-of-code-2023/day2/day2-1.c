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

void clear_buffer(char* buf, int size){
    for(int i = 0; i < size; i++){
        buf[i] = 0;
    }
}

int game_plausible(char* string, int max_red, int max_green, int max_blue){
    //game, red, green, blue

    replace_semi(string);
    printf("%s", string);
    char color_buffer[MAX_LINE_SIZE];
    char val_buffer[MAX_LINE_SIZE];

    //get the game number
    char* cur_str_ptr = strchr(string, ':');
    char game_label[cur_str_ptr - string]; 
    strncpy(game_label, string, cur_str_ptr - string);
    int game_num = strtol(strchr(game_label, ' ')+1, NULL, 10);

    //move the pointer index up to the start of the first pull
    cur_str_ptr = cur_str_ptr + 2;
    
    while(*cur_str_ptr != '\0'){

        char* val_ptr = strchr(cur_str_ptr, ' '); 
        clear_buffer(val_buffer, MAX_LINE_SIZE);
        strncpy(val_buffer, cur_str_ptr, val_ptr - cur_str_ptr);
        int val = strtol(val_buffer, NULL, 10);
        //got the pull color val. advance the pointer to the name of the color.
        cur_str_ptr = cur_str_ptr + (val_ptr - cur_str_ptr) + 1;

        clear_buffer(color_buffer, MAX_LINE_SIZE);
        char* color_ptr = 0;
        int i =0; 
        while(*cur_str_ptr != '\0'){
            color_buffer[i] = *cur_str_ptr;
            cur_str_ptr = cur_str_ptr + 1;
            if(*cur_str_ptr == ','){
                color_ptr = cur_str_ptr;
                break;
            }
            i++;
        } 
        if(color_ptr){
            if((color_buffer[0] == 'r' && val > max_red)   ||
            (color_buffer[0] == 'g' && val > max_green) ||
            (color_buffer[0] == 'b' && val > max_blue)  ){
                return 0;
            }
            cur_str_ptr = color_ptr + 2;
        }
    }
    return game_num;
}

int main(){
    FILE* input_file = fopen("/workspace/gitpod.io-C/advent-of-code-2023/day2/day2-input.txt", "r");
    char line[MAX_LINE_SIZE];
    int sum = 0;
    int game_ok = -1;
    while(fgets(line, MAX_LINE_SIZE, input_file)){
        game_ok = game_plausible(line, 12, 13, 14); 
        printf("--> %d\n", game_ok);
        sum += game_ok;
        printf("Solution: %d\n", sum);

    }
}