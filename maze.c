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
char message[6];


int legalMazeCheck(){
    // Check rows and columns are in acceptance range 5-100

    // Check only legal characters are in maze
    if(columns < 5 || rows < 5){
        printf("Error: Maze dimensions too small\n");
        return 3;
    }else if(columns > 100 || rows > 100){
        printf("Error: Maze dimensions too large\n");
        return 3;
    }

    FILE *file = fopen(filename, "r");
    int charsInRow = 0;
    int startCount = 0;
    int exitCount = 0;
    //Loop through each row
    for(int i = 0; i < rows; i++){
        //Count chars in each row
        while ((c = fgetc(file)) != '\n' && c != EOF ){
            charsInRow++;
            //Check only legal chars
            if(c != ' ' && c != '#' && c != 'S' && c != 'E'){
                printf("Error: Maze contains illegal characters\n");
                return 3;
            }
            //Check maze has a start and exit
            if(c == 'S'){
                startCount++;
            }else if(c == 'E'){
                exitCount++;
            }
        }
        //Check each row is same length
        if(charsInRow != columns){
            printf("Error: Maze dimensions not consistent\n");
            return 3;
        }
        charsInRow = 0;
    }
    if(startCount != 1 || exitCount != 1){
        printf("Error: Maze contains wrong number of Start and Exit\n");
        return 3;
    }
    fclose(file);
    return 0;

}

int mapShow(){
    printf("\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (player.currentPosition[0] == i && player.currentPosition[1] == j){
                printf("X");
            }else{
                printf("%c", maze[i][j]);
            }
        }
        printf("\n");
    }
    return 0;
}

int gameSetup(){
    
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: File not available\n");
        return 2;
    }
    //counts chars in first row
    while ((c = fgetc(file)) != EOF && c != '\n') {
        columns++;
    }
    //counts remaining rows
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
    return 0;
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
            strcpy(message, "North");
            break;
        case 'a':
            player.futurePosition[1] = player.currentPosition[1] - 1;
            strcpy(message, "West");
            break;
        case 's':
            player.futurePosition[0] = player.currentPosition[0] + 1;
            strcpy(message, "South");
            break;
        case 'd':
            player.futurePosition[1] = player.currentPosition[1] + 1;
            strcpy(message, "East");
            break;
    }
    if (player.futurePosition[0] < 0 || player.futurePosition[1] < 0 || player.futurePosition[0] >= rows || player.futurePosition[1] >= columns){
        printf("Thats the edge of the maze!\n");
        player.futurePosition[0] = player.currentPosition[0];
        player.futurePosition[1] = player.currentPosition[1];
    }
    else if (maze[player.futurePosition[0]][player.futurePosition[1]] == '#' ){
        printf("There is a wall there!\n");
        player.futurePosition[0] = player.currentPosition[0];
        player.futurePosition[1] = player.currentPosition[1];
    }else {
        player.currentPosition[0] = player.futurePosition[0];
        player.currentPosition[1] = player.futurePosition[1];
        printf("You moved %s!\n", message);
    }

}
int main(int argc, char *argv[]){
    if(argc != 2){
        printf("Error: Incorrect Arguments");
        return 1;
    }else{
    strcpy(filename, argv[1]);

    int setupReturnVal = gameSetup();
    if(setupReturnVal == 2){
        return 2;
    }else if (setupReturnVal == 3){
        return 3;
    }
    char playing = 'T';
    // While current player position not at Exit
    while (playing == 'T'){

        // Accept user input
        printf("\nEnter input: ");
        fgets(userInput, sizeof(userInput), stdin);
    
        
        if (inputValidation() == 0){
            if(inputChar == 'm'){
                mapShow();
            }
            else{
                playerMove();
            }
        }
        if(player.currentPosition[0] == exitPos[0] && player.currentPosition[1] == exitPos[1]){
            playing = 'F';
        }
    }
    printf("\nCONGRATULATIONS YOU WON!!\n");
    return 0;
    }
}