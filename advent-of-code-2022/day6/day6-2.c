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
    int not_found=1;
    for(k; k < size; k++){
        printf("k=%d, current window: %s\n", k, w);
        for(int i=0; i<SOM_MARKER_SIZE; i++){
            for(int j=0; j < SOM_MARKER_SIZE; j++){
                not_found = w[i] == w[j]; //doesnt quite work.
                if(!not_found){
                    break;
                }
            }
            if(!not_found){
                break;
            }
        }
        if(not_found){
            w[0] = w[1]; 
            w[1] = w[2];
            w[2] = w[3];
            w[3] = (char)ds_buffer[k];
        }
        else break;
    }
    if(!not_found)
        printf("%d\n", k);    
    else printf("no marker found.\n");

    return 0;
}
