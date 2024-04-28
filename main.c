#include <stdio.h>
#include <string.h>

int rows, columns;
char c;
char filename[20];
char userInput[20];

typedef struct Player {
    int currentPosition[2]; 
    int futurePosition[2];  
}Player;

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
    fclose(file);
    return 0;

}

/*int mapShow(){
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%c ", maze[i][j]);
        }
        printf("\n");
    }
    // Replace current player position with X
}*/

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
    fclose(file);
    
    if (legalMazeCheck() != 0){
        return 3;
    }

    file = fopen(filename, "r");
    struct Player player;
    char maze[rows][columns];
    int exit[2];
    int j;

    for (int i = 0; i < rows; i++){
        j = 0;
        while ((c = fgetc(file)) != '\n' && c != EOF ){
            maze[i][j] = c;
            if (c == 'E'){
                exit[0] = i;
                exit[1] = j;
            }else if (c == 'S'){
                player.currentPosition[0] = i;
                player.currentPosition[1] = j;
                player.futurePosition[0] = i;
                player.futurePosition[1] = j;
            }
            j++;
        }
    }
}

int inputValidation(){
    // Check for null input
    int length = strlen(userInput);
    printf("%d", length);
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
    while (player.currentPosition[0] != exit[0] && player.currentPosition[1] != exit[1]);

        // Accept user input
        print("Enter input: ");
        scanf("%s", userInput);
        inputValidation()

        // If user input M
            // Call mapShow()
        // If user input W,A,S,D
            // Call playerMove()
        
        // 
}