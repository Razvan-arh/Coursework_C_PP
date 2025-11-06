
#include "math.h"
#include <stdlib.h>
#include <stdio.h>
#include "../robot_logic/robot.h"
#include "../robot_logic/robot_navigation.h"
#include <string.h>
#include "stages.h"

FILE *inputPtr;
FILE *fileptr;


void ReadGrid(robot *rob)
{
    int robX, robY;
    int x, y;
    //read robot position
    fscanf(fileptr, "[%d, %d]\n", &robX, &robY);
    rob -> x = robX;
    rob -> y = robY;

    //read marker positions
    fscanf(fileptr, "%d\n", &numberOfMarkers);
    for(int i = 0; i < numberOfMarkers; i++)
    {
        
        fscanf(fileptr, "%d %d\n", &x, &y);
        
        grid[x][y] = 2;
    }
    
    //read all obstacle position
    while(!feof(fileptr))
    {
        fscanf(fileptr, "(%d, %d)\n", &x, &y);

        grid[x][y] = 1;
    }

    //the rest of the grid is left empty and is considered free space
}

int ReadGridLength()
{
    int n;
    fscanf(fileptr, "%d\n", &n);
    return n;
}

int RandomGeneration(robot *rob)
{
    int n;
    int x, y;
    int direction;
    int maximumNumberOfObstacles;

    numberOfMarkers = rand() % 5;
    objective = 0;
    

    do //picks a random grid length between 10 and the max length
    {
        n = rand() % 100;
    } while (n > MAX_GRID_LENGTH || n < 10);

    maximumNumberOfObstacles = n / 3 * 5; //chose an arbitrary number based on n

    //selects robot position
    x = rand() % n;
    y = rand() % n;
    
    
    rob -> x = x;
    rob -> y = y;

    for(int i = 0; i < numberOfMarkers; i++){
        do //selects marker position
        {
            x = rand() % n;
            y = rand() % n;
        } while (x == rob -> x && y == rob -> y);

        grid[x][y] = 2; 
    }

    rob -> dir = rand() % 4; //selects random direction

    //generates all obstacles
    for(int i = rand() % maximumNumberOfObstacles; i < maximumNumberOfObstacles; i++)   
        {   
            do
            {
                x = rand() % n;
                y = rand() % n;
            } while((x == rob -> x && y == rob -> y) || grid[x][y] == 2);
            grid[x][y] = 1;
        }

    return n;
}


int ReadAll(robot *rob)
{
    
    rob -> dir = UP;

    inputPtr = fopen("input/input.txt", "r");
    int n = 3; //cell number
    char codeWord[20];
    fgets(codeWord, 20, inputPtr);
    fclose(inputPtr);
    
    if (strcmp(codeWord, "EMPTY") == 0)
    {
        
        fileptr = fopen("input/empty.txt", "r");
        
        n = ReadGridLength();
        if(n > MAX_GRID_LENGTH)
            return n;

        ReadGrid(rob);
        
        fclose(fileptr);
        return n;
    }

    if (strcmp(codeWord, "RANDOM") == 0)
    {
        n = RandomGeneration(rob);
    }
    
    if (strcmp(codeWord, "CUSTOM") == 0)
    {
        fileptr = fopen("input/custom.txt", "r");

        n = ReadGridLength();
        if(n > MAX_GRID_LENGTH)
            return n;
        
        ReadGrid(rob);
        
        fclose(fileptr);    
        return n;
    }
    
    if (strcmp(codeWord, "STAGE1") == 0) 
        n = GenerateStage1(rob);
    if (strcmp(codeWord, "STAGE2") == 0)
        n = GenerateStage2(rob);
    if (strcmp(codeWord, "STAGE3") == 0)
        n = GenerateStage3(rob);
    if (strcmp(codeWord, "STAGE4") == 0)
        n = GenerateStage4(rob);
    if (strcmp(codeWord, "STAGE5") == 0)
        n = GenerateStage5(rob);

    return n;
}

