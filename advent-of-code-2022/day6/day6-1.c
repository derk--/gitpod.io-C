#include <sys/stat.h>
#include <stdio.h>

#define WINDOW_SIZE 4

int main(){
    char* filename = "day6-input.txt";
    FILE* input_file = fopen(filename,"r");

    struct stat st;
    stat(filename, &st);
    int size = st.st_size;

    char* ds_buffer = (char*)malloc(sizeof(char)*size);
    

    printf("%d", size);
    return 0;
}
