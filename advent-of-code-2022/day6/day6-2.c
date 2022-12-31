#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

#define WINDOW_SIZE 4
#define SOM_MARKER_SIZE 14

int main(){
    char* filename = "day6-input.txt";
    FILE* input_file = fopen(filename,"r");

    struct stat st;
    stat(filename, &st);
    int size = st.st_size;

    char* ds_buffer = (char*)malloc(sizeof(char)*size + 1);
    fgets(ds_buffer, size+1, input_file);
    printf("buffer: %s\n", ds_buffer);
    char w[SOM_MARKER_SIZE]; 
    for(int i=0; i<SOM_MARKER_SIZE; i++){
        w[i] = ds_buffer[i];
    }
    int k = SOM_MARKER_SIZE;
    int not_found;
    for(k; k < size; k++){
        not_found = 0;
        printf("k=%d, current window: %s\n", k, w);
        for(int i=0; i < SOM_MARKER_SIZE; i++){
            for(int j=0; j < SOM_MARKER_SIZE; j++){
                if(i != j && w[i] == w[j]){
                    not_found = 1;
                    break;
                }
            }
        }
        if(not_found){
            for(int i=0; i<SOM_MARKER_SIZE-1; i++){
                w[i] = w[i+1];
            }
            w[SOM_MARKER_SIZE-1] = ds_buffer[k];
        }
        else break;
    }
    if(!not_found)
        printf("%d\n", k);    
    else printf("no marker found.\n");

    return 0;
}
