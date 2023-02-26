#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>

#define BUFFER_SIZE 32768
#define INPUT_FILE "day7-input.txt"

struct dir {
    char* dir_path; 
    size_t dir_size; 
};
static int total_size = 0;


/*
Print the path represented by the GList parts.
max < g_list_length(parts) means to return the partial path 
max subdirectories down from the root.
*/
char* get_full_path(GList* parts, int max){
    int length = g_list_length(parts);
    length = length >= max ? max : length;
    int path_length = 0;
    for(int i=0; i < length; i++){
        path_length += strlen(g_list_nth_data(parts, i));
    }
    printf("path_length: %d\n",path_length);
    char* full_path = (char *)malloc(sizeof(*full_path) * (path_length + 1));
    for(int i=0; i < length; i++){
        char* part = g_list_nth_data(parts, i);
        strncat(full_path, part, strlen(part) );
    }  
    return full_path;
}

static void print_size(gpointer key, gpointer value, gpointer user_data){
    long val = (long)value;
    if(val > 0 && val <= 100000){
        printf("size of %s is: %ld\n", (gchar*)key, val);
        total_size += val;
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
                char* dir = (char *)malloc(sizeof(char) * (dir_len + 3));
                strncpy(dir, &line[5], dir_len);
                dir[dir_len] = '/';
                dir[dir_len+1] = '\0';
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
                }
                printf("current path: %s\n", get_full_path(path_parts, BUFFER_SIZE));
            } 
            listing = line[2] == 'l';
        } 
        else if(listing){
            long size = strtol(line, NULL, 10);
            //add to listing size for this and all parents of this path. 
            GList* copy_of_path_parts = g_list_copy_deep(path_parts, NULL, NULL);
            do {
                char* dir_path = get_full_path(copy_of_path_parts, BUFFER_SIZE);
                void* new_size = g_hash_table_lookup(dir_sizes, dir_path) + size;
                g_hash_table_insert(dir_sizes, dir_path, new_size);
                copy_of_path_parts = g_list_remove(copy_of_path_parts, g_list_last(copy_of_path_parts) -> data);
            } while(copy_of_path_parts != NULL);
            g_list_free_full(copy_of_path_parts, NULL);
        }
    }
    g_hash_table_foreach(dir_sizes, print_size, NULL);
    printf("Solution: %d\n", total_size);


    g_hash_table_destroy(dir_sizes);
    return 0;
   
}