
#include <stdio.h>
#include "robot.h"
#include "robot_navigation.h"
#include <string.h>

FILE *inputPtr;
FILE *fileptr;

int updateMarkers;

void ReadGrid(robot *rob)
{
    int robX, robY;

    //read robot position
    fscanf(fileptr, "[%d, %d]", &robX, &robY);
    rob -> x = robX;
    rob -> y = robY;

    //read marker positions
    fscanf(fileptr, "%d", &numberOfMarkers);

    for(int i = 0; i < numberOfMarkers; i++)
    {
        int x, y;
        fscanf(fileptr, "%d %d", &x, &y);

        grid[x][y] = 2;
    }

    //read all obstacle position
    while(!feof(fileptr))
    {
        int x, y;
        fscanf(fileptr, "(%d %d)", &x, &y);

        grid[x][y] = 1;
    }

    //the rest of the grid is left empty and is considered free space
}

int ReadGridLength()
{
    int n;
    fscanf(fileptr, "%d", &n);
    return n;
}

int ReadAll(robot *rob)
{
    rob -> dir = UP;

    inputPtr = fopen("input.txt", "r");
    int n; //cell number
    char codeWord[20];
    fgets(codeWord, 20, inputPtr);
    fclose(inputPtr);

    if (strcmp(codeWord, "EMPTY") == 0)
    {
        fileptr = fopen("empty.txt", "r");

        n = ReadGridLength();
        ReadGrid(rob);

        fclose(fileptr);
        return n;
    }

    if (strcmp(codeWord, "RANDOM"))
    {
        //random
    }
    
    if (strcmp(codeWord, "CUSTOM"))
    {
        fileptr = fopen("custom.txt", "r");

        n = ReadGridLength();
        ReadGrid(rob);

        fclose(fileptr);    
        return n;
    }

    return n;
}
