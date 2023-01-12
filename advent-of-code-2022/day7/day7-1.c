#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>

#define BUFFER_SIZE 4096

struct dir {
    char* dir_path; 
    size_t dir_size; 
};

char* get_full_path(GList* parts){
    int length = g_list_length(parts);
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

int main(){
    char* filename = "test-input.txt";
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
                    path_parts = g_list_remove(path_parts, g_list_last(path_parts));
                } 
                //move to this directory
                else { 
                    path_parts = g_list_append(path_parts, dir);
                    printf("current path: %s\n", get_full_path(path_parts));
                }
            } 
            listing = line[2] == 'l';
        } 
        else if(listing){
            long size = strtol(line, NULL, 10);
            printf("size: %ld\n", size);
            g_hash_table_lookup()
        }
    }
    g_hash_table_destroy(dir_sizes);

    return 0;
   
}