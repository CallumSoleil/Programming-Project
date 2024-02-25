#!/bin/bash

echo -e "__ File Handling __"

echo -n "Test Available File"
./mazeGame fakeFile.txt > tmp
if grep -q "Error: File not available" tmp;
then
    echo "Test Passed"
else
    echo "Test Failed"
fi

echo -n "Test Too Large Maze"
./mazeGame data/bigMaze.txt > tmp
if grep -q "Error: Maze dimensions too large" tmp;
then
    echo "Test Passed"
else
    echo "Test Failed"
fi

echo -n "Test Too Small Maze"
./mazeGame data/smallMaze.txt > tmp
if grep -q "Error: Maze dimensions too small" tmp;
then
    echo "Test Passed"
else
    echo "Test Failed"
fi

echo -n "Test Rectangular Maze"
./mazeGame data/inconsistentMaze.txt > tmp
if grep -q "Error: Maze dimensions not consistent" tmp;
then
    echo "Test Passed"
else
    echo "Test Failed"
fi

echo -n "Test Legal Maze Characters"
./mazeGame data/illegalCharsMaze.txt > tmp
if grep -q "Error: Maze contains illegal characters" tmp;
then
    echo "Test Passed"
else
    echo "Test Failed"
fi

echo -n "Test player can move"
echo "d" | ./mazeGame data/goodMaze.txt > tmp
if grep -q "You moved East!" tmp;
then
    echo "Test Passed"
else
    echo "Test Failed"
fi

echo -n "Test walls stop player"
echo "s" | ./mazeGame data/goodMaze.txt > tmp
if grep -q "There is a wall there!" tmp;
then
    echo "Test Passed"
else
    echo "Test Failed"
fi

echo -n "Test dealing of illegal input char"
echo "z" | ./mazeGame data/goodMaze.txt > tmp
if grep -q "Error: Bad input" tmp;
then
    echo "Test Passed"
else
    echo "Test Failed"
fi

echo -n "Test dealing of empty input"
echo "" | ./mazeGame data/goodMaze.txt > tmp
if grep -q "Error: Bad input" tmp;
then
    echo "Test Passed"
else
    echo "Test Failed"
fi

echo -n "Test dealing of a string input"
echo "HI" | ./mazeGame data/goodMaze.txt > tmp
if grep -q "Error: Bad input" tmp;
then
    echo "Test Passed"
else
    echo "Test Failed"
fi

echo -n "Test win"
./mazeGame data/goodMaze.txt > tmp
if grep -q "Congratulations! You reached the exit!" tmp;
then
    echo "Test Passed"
else
    echo "Test Failed"
fi