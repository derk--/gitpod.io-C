#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>

#define BUFFER_SIZE 4096
#define INPUT_FILE "day7-input.txt"

struct dir {
    char* dir_path; 
    size_t dir_size; 
};

/*
Print the path represented by the GList parts.
max < g_list_length(parts) means to return the partial path 
max subdirectories down from the root.*/
char* get_full_path(GList* parts, int max){
    int length = g_list_length(parts);
    length = length >= max ? max : length;
    int path_length = 0;
    for(int i=0; i < length; i++){
        path_length += strlen(g_list_nth_data(parts, i));
    }
    char* full_path = (char *)malloc(sizeof(char) * path_length);
    for(int i=0; i < length; i++){
        strncat(full_path, 
                g_list_nth_data(parts, i), 
                strlen(g_list_nth_data(parts, i))
            );
    }
    return full_path;
}

static void print_size(gpointer key, gpointer value, gpointer user_data){
    long val = (long)value;
    if(val > 0 && val <= 100000){
        printf("size of %s is: %ld\n", (char *)key, (long)value);
    }
}

int main(){
    char* filename = INPUT_FILE;
    FILE* input_file = fopen(filename,"r");
    char line[BUFFER_SIZE];

    GHashTable* dir_sizes = g_hash_table_new(g_str_hash, g_str_equal);
    GList* path_parts = NULL;
    path_parts = g_list_append(path_parts, "/");

    gboolean listing = FALSE;
    while(fgets(line, BUFFER_SIZE, input_file)){
        printf("command: %s\n", line);
        if(line[0] == '$'){
            listing = FALSE;
            //if this is a directory change: 
            if(line[2] == 'c'){
                int dir_len = strlen(&line[5]) - 1;
                char* dir = (char *)malloc(sizeof(char) * dir_len + 1);
                dir[dir_len] = '/';
                printf("dir_len: %d, ", dir_len);
                strncpy(dir, &line[5], dir_len);
                printf("subdir: %s\n", dir);
                //if the change is to the parent of cwd:
                if(!strcmp(dir, "//")){ 
                    continue;
                }
                if(!strcmp(dir, "../")){
                    printf("here\n");
                    path_parts = g_list_remove(path_parts, g_list_last(path_parts) -> data);
                } 
                //move to this directory
                else { 
                    path_parts = g_list_append(path_parts, dir);
                    //printf("current path: %s\n", get_full_path(path_parts, BUFFER_SIZE));
                }
            } 
            listing = line[2] == 'l';
        } 
        else if(listing){
            long size = strtol(line, NULL, 10);
            //printf("size: %ld\n", size);
            char* dir_path = get_full_path(path_parts, BUFFER_SIZE);
            //add to listing size for all parents of this path too.. 
            int length = g_list_length(path_parts);
            //TODO
            //and then add to this path. 
            printf("pp: %s, size: ", dir_path);
            long dir_size = (long) g_hash_table_lookup(dir_sizes, dir_path);
            printf("%ld\n", dir_size);
            g_hash_table_insert(dir_sizes, dir_path, dir_size + size);
            //free(dir_path);
        }
    }
    g_hash_table_foreach(dir_sizes, print_size, NULL);

    g_hash_table_destroy(dir_sizes);
    return 0;
   
}

/** This code corrupts memory
for(int i=0; i < length; i++){
                char* partial_path = get_full_path(path_parts, i);
                printf("pp: %s, size: ", partial_path);
                long dir_size = (long) g_hash_table_lookup(dir_sizes, partial_path);
                printf("%ld\n", dir_size);
                if(dir_size){
                    g_hash_table_insert(dir_sizes, partial_path, dir_size + size);
                } else { 
                    g_hash_table_insert(dir_sizes, partial_path, size);
                }
                
                //free(partial_path);
            }
            */