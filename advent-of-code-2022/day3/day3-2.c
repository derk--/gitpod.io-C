#include <stdio.h>
#include <string.h>

/* Now, find what is common across 3 consecutive lines.*/
int main(){ 
    char* items = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    FILE* input_file = fopen("day3-input.txt", "r");
    char buf1[100], buf2[100], buf3[100]; 
    int item_sum = 0;
    size_t priority = 0;
    while(1){
        char matching_item = '-';
        if(
            fgets(buf1, 100, input_file) && 
            fgets(buf2, 100, input_file) && 
            fgets(buf3, 100, input_file)){
                char* x, y, z;
                for(char* i = buf1; *i !='\0'; i++){
                    for(char* j = buf2; *j != '\0'; j++){
                        for(char* k = buf3; *k != '\0'; k++){
                            if(*i == *j && *j == *k && matching_item == '-'){
                                matching_item = *i;
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