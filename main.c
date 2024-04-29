#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct Player {
    int currentPosition[2]; 
    int futurePosition[2];  
}Player;

int rows, columns;
char c;
char filename[20];
char userInput[20];
struct Player player;
int exitPos[2];
char inputChar;
char maze[100][100];


int legalMazeCheck(){
    if(columns < 5 || rows < 5){
        printf("Error: Maze dimensions too small\n");
        return 3;
    }else if(columns > 100 || rows > 100){
        printf("Error: Maze dimensions too large\n");
        return 3;
    }

    FILE *file = fopen(filename, "r");
    int charsInRow = 0;
    for(int i = 0; i < rows; i++){
        while ((c = fgetc(file)) != '\n' && c != EOF ){
            charsInRow++;
            if(c != ' ' && c != '#' && c != 'S' && c != 'E'){
                printf("Error: Maze contains illegal characters\n");
                return 3;
            }
        }
        if(charsInRow != columns){
            printf("Error: Maze dimensions not consistent\n");
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
    
    int j;
    

    for (int i = 0; i < rows; i++){
        j = 0;
        while ((c = fgetc(file)) != '\n' && c != EOF ){
            maze[i][j] = c;
            if (c == 'E'){
                exitPos[0] = i;
                exitPos[1] = j;
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

    if (userInput[strlen(userInput) - 1] == '\n'){
        userInput[strlen(userInput) - 1] = '\0';
    }

    if (strlen(userInput) != 1) {
        printf("Error: Bad input\n");
        return -1;
    } else {
        inputChar = tolower(userInput[0]);
        if (inputChar != 'm' && inputChar != 'w' && inputChar != 'a' && inputChar != 's' && inputChar != 'd'){
            printf("Error: Bad \n");
            return -1;
        }else{
            return 0;
        }
    }
}

int playerMove(){ 
    // Adjust future player position based on user input
    switch (inputChar){
        case 'w':
            player.futurePosition[0] = player.currentPosition[0] - 1;
            break;
        case 'a':
            player.futurePosition[1] = player.currentPosition[1] - 1;
            break;
        case 's':
            player.futurePosition[0] = player.currentPosition[0] + 1;
            break;
        case 'd':
            player.futurePosition[1] = player.currentPosition[1] - 1;
            break;
    }
    if (player.futurePosition[0] < 0 || player.futurePosition[1] < 0 || player.futurePosition[0] >= rows || player.futurePosition[1] >= columns){
        printf("Thats the edge of the maze!\n");
    }
    else if (maze[player.futurePosition[0]][player.futurePosition[1]] == '#' ){
        printf("There is a wall there!\n");
    }else{
        player.currentPosition[0] = player.futurePosition[0];
        player.currentPosition[0] = player.futurePosition[0];
    }

}
int main(){
    gameSetup();

    // While current player position not at Exit
    while (player.currentPosition[0] != exitPos[0] && player.currentPosition[1] != exitPos[1]){

        // Accept user input
        printf("Enter input: ");
        fgets(userInput, sizeof(userInput), stdin);
    
        
        if (inputValidation() == 0){
            if(inputChar == 'm'){
                printf("mapShow()");
            }
            else{
                playerMove();
            }
        }
    }
    printf("FINISHED");
}