#include <stdio.h>
#include <string.h>

/* Now, find what is common across 3 consecutive lines.*/
int main(){ 
    char* items = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    FILE* input_file = fopen("day3-input.txt", "r");
   
    char buf1[255], buf2[255], buf3[255]; 
    int item_sum = 0;
    size_t priority = 0;
    while(1){
        char matching_item = '-';
        if(
            fgets(buf1, 255, input_file) && 
            fgets(buf2, 255, input_file) && 
            fgets(buf3, 255, input_file)){

            for(int i=0; buf1[i] != '\0'; i++){
                for(int j=0; buf2[j] != '\0'; j++){
                    for(int k=0; buf3[k] != '\0'; k++){
                        if(buf1[i] == buf2[j] && buf2[j] == buf3[k] && matching_item == '-'){
                            matching_item = buf1[i];
                        }
                    }
                }

            }
        } else {
            break;
        }
        char* item_ptr = strchr(items, matching_item);
        if(item_ptr){            
            priority += item_ptr - items + 1;
        }
    }
    printf("Total priority: %zu\n", priority);
    return 0;
}