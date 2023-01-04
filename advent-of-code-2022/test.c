#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

void test(){
    char* output = (char*)malloc(sizeof(char)*6);
    output[0] = 'h';
    output[1] = 'e';
    output[2] = 'l';
    output[3] = 'l';
    output[4] = 'o';
    output[5] = '\0';
}

int main(){
    char* output;
    test();
    printf("%s/n", output);
    return 0;
}