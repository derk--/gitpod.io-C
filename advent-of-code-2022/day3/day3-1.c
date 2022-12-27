#include <stdio.h>
#include <string.h>

int main(){ 
    char* items = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    FILE* input_file = fopen("day3-input.txt", "r");
   
    char line_buffer[255];
    int item_sum = 0;
    size_t priority = 0;
    while(fgets(line_buffer, 255, input_file)){

        //find the repeating item. 
        size_t sack_size = strlen(line_buffer) / 2;
        char sack_1[sack_size+1]; 
        char sack_2[sack_size+1];
        sack_1[sack_size] = '\0';
        sack_2[sack_size] = '\0';

        strncpy(sack_1,line_buffer,sack_size);
        strncpy(sack_2,&line_buffer[sack_size],sack_size);

        char matching_item = '-';
        for(int i=0; sack_1[i] != '\0'; i++){
            char item = sack_1[i];
            for(int j=0; sack_2[j] != '\0'; j++){
                if(item == sack_2[j]){
                    matching_item = item;
                    break;
                }
            }
            if(matching_item != '-'){
                break;
            }
        }

        char* item_ptr = strchr(items, matching_item);
        if(item_ptr){            
            priority += item_ptr - items + 1;
        }
    }
    printf("Total priority: %zu\n", priority);
    return 0;
}