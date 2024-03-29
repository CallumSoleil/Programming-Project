#!/bin/bash

# Most tests were adapted forms of tests found in https://github.com/uol-feps-soc-comp1921-2324-classroom/lab2-finished/blob/main/test.sh
# bigMaze.txt was made using https://www.dcode.fr/maze-generator


passCount=0
totalTests=0


echo -e "__ File Handling __"

# Maze file must be accessible to open
echo -n "Test Available File - "
./mazeGame fakeFile.txt > tmp
if grep -q "Error: File not available" tmp;
then
    echo "Test Passed"
    ((passCount++))
else
    echo "Test Failed"
fi
((totalTests++))

# Set of tests to ensure the maze fits the size and character constraints
echo -e "__ Maze Constraints __"

echo -n "Test Too Large Maze - "
./mazeGame TestData/bigMaze.txt > tmp
if grep -q "Error: Maze dimensions too large" tmp;
then
    echo "Test Passed"
    ((passCount++))
else
    echo "Test Failed"
fi
((totalTests++))

echo -n "Test Too Small Maze - "
./mazeGame TestData/smallMaze.txt > tmp
if grep -q "Error: Maze dimensions too small" tmp;
then
    echo "Test Passed"
    ((passCount++))
else
    echo "Test Failed"
fi
((totalTests++))

echo -n "Test for Rectangular Maze - "
./mazeGame TestData/inconsistentMaze.txt > tmp
if grep -q "Error: Maze dimensions not consistent" tmp;
then
    echo "Test Passed"
    ((passCount++))
else
    echo "Test Failed"
fi
((totalTests++))

echo -n "Test Legal Maze Characters - "
./mazeGame TestData/illegalCharsMaze.txt > tmp
if grep -q "Error: Maze contains illegal characters" tmp;
then
    echo "Test Passed"
    ((passCount++))
else
    echo "Test Failed"
fi
((totalTests++))

# Set of tests to ensure all possible user inputs are dealt with
echo -e "__ User Inputs __"

echo -n "Test dealing of illegal input char - "
echo "z" | ./mazeGame TestData/goodMaze.txt > tmp
if grep -q "Error: Bad input" tmp;
then
    echo "Test Passed"
    ((passCount++))
else
    echo "Test Failed"
fi
((totalTests++))

echo -n "Test dealing of empty input - "
echo "" | ./mazeGame TestData/goodMaze.txt > tmp
if grep -q "Error: Bad input" tmp;
then
    echo "Test Passed"
    ((passCount++))
else
    echo "Test Failed"
fi
((totalTests++))

echo -n "Test dealing of a string input - "
echo "HI" | ./mazeGame TestData/goodMaze.txt > tmp
if grep -q "Error: Bad input" tmp;
then
    echo "Test Passed"
    ((passCount++))
else
    echo "Test Failed"
fi
((totalTests++))

echo -n "Test map show - "
echo "m" | ./mazeGame TestData/goodMaze.txt > tmp
if grep -q "X ###\n#  ##\n## ##\n##  #\n#    E" tmp;
then
    echo "Test Passed"
    ((passCount++))
    
else
    echo "Test Failed"
fi
((totalTests++))

# Set of tests to check the player will move only through spaces
# and that error messages are shown too
echo -e "__ Player Movement __"

echo -n "Test player can move - "
echo "d" | ./mazeGame TestData/goodMaze.txt > tmp
if grep -q "You moved East!" tmp;
then
    if grep -q "SX###\n#  ##\n## ##\n##  #\n#    E" tmp;
    then
        echo "Test Passed"
        ((passCount++))
    else
        echo "Test Failed"
    fi
else
    echo "Test Failed"
fi
((totalTests++))


echo -n "Test walls stop player - "
echo -e "s\nm" | ./mazeGame TestData/goodMaze.txt > tmp
if grep -q "There is a wall there!" tmp;
then
    if grep -q "X ###\n#  ##\n## ##\n##  #\n#    E" tmp;
    then
        echo "Test Passed"
        ((passCount++))
    else
        echo "Test Failed"
    fi
else
    echo "Test Failed"
fi
((totalTests++))

echo -n "Test maze edge stop player - "
echo -e "a\nm" | ./mazeGame TestData/goodMaze.txt > tmp
if grep -q "Thats the edge of the maze!" tmp;
then
    if grep -q "X ###\n#  ##\n## ##\n##  #\n#    E" tmp;
    then
        echo "Test Passed"
        ((passCount++))
    else
        echo "Test Failed"
    fi
else
    echo "Test Failed"
fi
((totalTests++))


# Test that the player wins when they reach the Exit
echo -n "__ Objectibe Work __"

echo -n "Test win - "
./mazeGame TestData/goodMaze.txt < winMovements.txt > tmp
if grep -q "Congratulations! You reached the exit!" tmp;
then
    echo "Test Passed"
    ((passCount++))
else
    echo "Test Failed"
fi
((totalTests++))

echo "$passCount/$totalTests tests passed"