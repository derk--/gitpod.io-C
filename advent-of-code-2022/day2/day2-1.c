#include <stdio.h>

int main(){ 
    FILE* input_file = fopen("day2-input.txt", "r");
    //XA=3+1 XB=0+1 XC=6+1 
    //YA=6+2 YB=3+2 YC=0+2
    //ZA=0+3 ZB=6+3 ZC=3+3
    /*
    X for Rock, Y for Paper, and Z for Scissors. 
    A for Rock, B for Paper, and C for Scissors. 
    
    The score for a single round is the 
    score for the shape you selected (1 for Rock, 2 for Paper, and 3 for Scissors) plus the 
    score for the outcome of the round (0 if you lost, 3 if the round was a draw, and 6 if you won).
*/
    int s[3][3]; 
    s[0][0]=4; s[0][1]=1; s[0][2]=7;
    s[1][0]=8; s[1][1]=5; s[1][2]=2;
    s[2][0]=3; s[2][1]=9; s[2][2]=6;
    //x=row 1 y = row2 z = row3
    //a=col 1 b = col2 c = col3
    char line_buffer[255];
    int score = 0;
    while(fgets(line_buffer, 255, input_file)){
        //printf("%s", line_buffer);
        int x, y = -1;
        if(line_buffer[0] == 'A'){y=0;}
        else if(line_buffer[0] == 'B'){y=1;}
        else if(line_buffer[0] == 'C'){y=2;}
        
        if(line_buffer[2] == 'X'){x=0;}
        else if(line_buffer[2] == 'Y'){x=1;}
        else if(line_buffer[2] == 'Z'){x=2;}
        printf("x=%d y=%d s[x][y]=%d \n", x, y, s[x][y]);
        score += s[x][y];
    }
    printf("\nTotal score: %d\n", score);
    return 0;
}