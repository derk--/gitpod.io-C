#include <stdio.h>

int main(){ 
    FILE* input_file = fopen("day2-input.txt", "r");
    //XA=0+3 XB=0+1 XC=0+2 
    //YA=3+1 YB=3+2 YC=3+3
    //ZA=6+2 ZB=6+3 ZC=6+1
    /*
    X for Rock, Y for Paper, and Z for Scissors. 
    A for Rock, B for Paper, and C for Scissors. 
    /*X means you need to lose, 
    Y means you need to end the round in a draw, 
    Z means you need to win. Good luck!"*/

    int s[3][3]; 
    s[0][0]=3; s[0][1]=1; s[0][2]=2;
    s[1][0]=4; s[1][1]=5; s[1][2]=6;
    s[2][0]=8; s[2][1]=9; s[2][2]=7;

    char line_buffer[255];
    int score = 0;
    while(fgets(line_buffer, 255, input_file)){
        int x, y = -1;
        if(line_buffer[0] == 'A')
            y=0;
        else if(line_buffer[0] == 'B')
            y=1;
        else if(line_buffer[0] == 'C')
            y=2;
        
        if(line_buffer[2] == 'X')
            x=0;
        else if(line_buffer[2] == 'Y')
            x=1;
        else if(line_buffer[2] == 'Z')
            x=2;
            
        printf("x=%d y=%d s[x][y]=%d \n", x, y, s[x][y]);
        score += s[x][y];
    }
    printf("\nTotal score: %d\n", score);
    return 0;
}