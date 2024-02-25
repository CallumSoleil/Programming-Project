//Code skelton for the maze game

int legalMazeCheck(){
    // Check rows and columns are in acceptance range 5-100

    // Check every row has same length

    // Check every column has same length

    // Check only legal characters are in maze
}

int mapShow(){
    // Nested for loops to cycle through every position in maze array
    // Print each row together
    // Replace player position with X
}

int gameSetup(){
    // Input maze file name

    // Open maze file with validation to check it exists

    // Count number of lines in file, storing in a variable (rows)

    // Count number of chars  in first line of file, storing in a variable (columns)

    // Validate maze using legalMazeCheck()

    // Create 2D array with size[rows][columns]

    // Populate with maze contents

    // playerPosition[2] = Start position coordinates

}

int inputValidation(){
    // Check for null input

    // Check for string input

    // Check for legal char input

}

int playerMove(){
    // Adjust playerPosition using user input
    
}
int main(){
    // Call gameSetup()

    // While player not at Exit

        // Accept user input

        // Call inputValidation()

        // If user input M
            // Call mapShow()
        // If user input W,A,S,D
            // Call playerMove()

        // 
}