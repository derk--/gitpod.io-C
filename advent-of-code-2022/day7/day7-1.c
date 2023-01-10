#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>

#define BUFFER_SIZE 4096

struct dir {
    char* dir_path; 
    size_t dir_size; 
};

int compare_dir(gconstpointer dir_a, gconstpointer dir_b){
    struct dir* a = (struct dir*)dir_a;
    struct dir* b = (struct dir*)dir_b;

    return strcmp(a->dir_path, b->dir_path);
}

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
    path_parts = g_list_append(path_parts, "derek/");

    char* full_path = get_full_path(path_parts);

    g_hash_table_insert(dir_sizes,full_path,25);
    g_hash_table_insert(dir_sizes,"Mr Darcy","Treats");

    printf("dir: %s \t size: %d\n",full_path, g_hash_table_lookup(dir_sizes,full_path));

   while(fgets(line, BUFFER_SIZE, input_file)){



    }
    g_hash_table_destroy(dir_sizes);

    return 0;
   
}
