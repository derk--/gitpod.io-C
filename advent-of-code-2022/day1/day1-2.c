#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_LINE_LENGTH 7

int min_index(int* arr){
    int min = INT_MAX;
    int idx = -1;
    for(int i=0; i <= sizeof(arr) / sizeof(int); i++){
        if(arr[i] <= min){
            min = arr[i];
            idx = i;
        }
    }
    return idx;
}

void update_cals(int* max_cals, int* cal_count){
    int idx = min_index(max_cals);
    max_cals[idx] = *cal_count >= max_cals[idx] ? *cal_count : max_cals[idx];
    *cal_count = 0;
}

int main(){
    FILE* input_file = fopen("day1-input.txt", "r");
    char line_buffer[7];
    int max_cals[3] = {-1};
    int cal_count = 0;
    while(fgets(line_buffer, MAX_LINE_LENGTH, input_file)){
        if(line_buffer[0] == '\n'){
            update_cals(max_cals, &cal_count);
        }
        else{
            cal_count += atoi(line_buffer);
        }
    }
    update_cals(max_cals, &cal_count);

    printf("Top3 cals: %d, %d, %d; Max calroies: %d\n", max_cals[0], max_cals[1], max_cals[2], max_cals[0] + max_cals[1] + max_cals[2]);
    return 0;
}
