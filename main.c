#include <stdio.h>
#include <string.h>

int rows, columns;
char c;
char filename[20];




struct Player {
    int currentPosition[2]; 
    int futurePosition[2];  
};

int legalMazeCheck(){
    if(columns < 5 || rows < 5){
        printf("Error: Maze dimensions too small");
        return 3;
    }else if(columns > 100 || rows > 100){
        printf("Error: Maze dimensions too large");
        return 3;
    }

    FILE *file = fopen(filename, "r");
    int charsInRow = 0;
    for(int i = 0; i < rows; i++){
        while ((c = fgetc(file)) != '\n' && c != EOF ){
            charsInRow++;
            if(c != ' ' && c != '#' && c != 'S' && c != 'E'){
                printf("Error: Maze contains illegal characters %c", c);
                return 3;
            }
        }
        if(charsInRow != columns){
            printf("Error: Maze dimensions not consistent   %d", i);
            return 3;
        }
        charsInRow = 0;
    }
    return 0;

}

int mapShow(){
    // Nested for loops to cycle through every position in maze array
    // Print each row together
    // Replace current player position with X
}

int gameSetup(){
    printf("Enter the file name: ");
    scanf("%s", filename);

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: File not available\n");
        return 2;
    }
    
    while ((c = fgetc(file)) != EOF && c != '\n') {
        columns++;
    }
    rows = 2;
    while ((c = fgetc(file)) != EOF) {
        if (c == '\n') {
            rows++;
        }
    }
    printf("%d %d\n", columns, rows);
    fclose(file);
    
    legalMazeCheck();

    // Create 2D array with size[rows][columns]
    
    // Populate with maze contents

    // Store coordinate of Exit as an array of length 2

    // Create a player
    // Set both current and future player positon to position of S in maze

}

int inputValidation(){
    // Check for null input

    // Check for string input

    // Check for legal char input

}

int playerMove(){ 
    // Adjust future player position based on user input
    
    // Check if that future player position is # or maze edge
    // Update current player position if legal
    // Error message if not
}
int main(){
    gameSetup();

    // While current player position not at Exit

        // Accept user input

        // Call inputValidation()

        // If user input M
            // Call mapShow()
        // If user input W,A,S,D
            // Call playerMove()
        
        // 
}