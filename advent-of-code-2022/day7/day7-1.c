#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

#define BUFFER_SIZE 128

struct dir {
    char* dir_path; 
    size_t dir_size; 
};

int compare_dir(gconstpointer dir_a, gconstpointer dir_b){
    struct dir* a = (struct dir*)dir_a;
    struct dir* b = (struct dir*)dir_b;

    return strcmp(a->dir_path, b->dir_path);
}

int main(){
    char* filename = "day7-input.txt";
    FILE* input_file = fopen(filename,"r");
    char line[BUFFER_SIZE];

    struct dir dir_a; 
    struct dir dir_b;
    dir_a.dir_path = "testing";
    dir_b.dir_path = "testing";
    printf("comparing...\n");
    int x = compare_dir(&dir_a, &dir_b);
    printf("%d\n", x);



    while(fgets(line, BUFFER_SIZE, input_file)){



    }
    return 0;
   
}
