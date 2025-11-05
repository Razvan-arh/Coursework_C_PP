//
//

#include "math.h"
#include <stdlib.h>
#include <stdio.h>
#include "../robot_logic/robot.h"
#include "../robot_logic/robot_navigation.h"
#include "stages.h"


int GenerateStage1(robot *rob)
{
    int n = 10;
    int x, y;
    int direction;

    numberOfMarkers = 1;
    objective = 0;
    
    do //selects robot position, not near a wall
    {
        x = rand() % n;
        y = rand() % n;
    } while (!(x > 0 && x < n - 1 && y > 0 && y < n - 1));
    printf("%d %d\n", x, y);
    rob -> x = x;
    rob -> y = y;

    do //selects marker position, near a wall
    {
        x = rand() % n;
        y = rand() % n;
    } while (!(x == 0 || y == 0 || x == (n-1) || y ==(n-1)));

    grid[x][y] = 2; 

    rob -> dir = rand() % 4; //selects random direction

    return n;
}

int GenerateStage2(robot *rob)
{
    int n;
    int x, y;
    int direction;

    numberOfMarkers = 1;
    objective = 1;

    do //picks a random grid length between 10 and the max length
    {
        n = rand() % 100;
    } while (n > MAX_GRID_LENGTH || n < 10);
    

    //selects robot position
    x = rand() % n;
    y = rand() % n;
    
    
    rob -> x = x;
    rob -> y = y;

    do //selects marker position, near a wall
    {
        x = rand() % n;
        y = rand() % n;
    } while (!(x == 0 || y == 0 || x == (n-1) || y ==(n-1)) || (x == rob -> x && y == rob -> y));

    grid[x][y] = 2; 

    rob -> dir = rand() % 4; //selects random direction

    objX = (n - 1) * (rand() % 2); //chooses the objective corner at random
    objY = (n - 1) * (rand() % 2);

    return n;
}

int GenerateStage3(robot *rob)
{
    int n;
    int x, y;
    int direction;

    numberOfMarkers = 1;
    objective = 1;

    do //picks a random grid length between 10 and the max length
    {
        n = rand() % 100;
    } while (n > MAX_GRID_LENGTH || n < 10);
    

    //selects robot position
    x = rand() % n;
    y = rand() % n;
    
    
    rob -> x = x;
    rob -> y = y;

    do //selects marker position
    {
        x = rand() % n;
        y = rand() % n;
    } while (x == rob -> x && y == rob -> y);

    grid[x][y] = 2; 

    rob -> dir = rand() % 4; //selects random direction

    objX = (n - 1) * (rand() % 2); //chooses the objective corner at random
    objY = (n - 1) * (rand() % 2);

    return n;
}

int GenerateStage4(robot *rob)
{
    int n;
    int x, y;
    int direction;
    int maximumNumberOfObstacles;

    numberOfMarkers = 1;
    objective = 1;
    

    do //picks a random grid length between 10 and the max length
    {
        n = rand() % 100;
    } while (n > MAX_GRID_LENGTH || n < 10);

    maximumNumberOfObstacles = n / 10 * 3; //chose an arbitrary number based on n

    //selects robot position
    x = rand() % n;
    y = rand() % n;
    
    
    rob -> x = x;
    rob -> y = y;

    do //selects marker position
    {
        x = rand() % n;
        y = rand() % n;
    } while (x == rob -> x && y == rob -> y);

    grid[x][y] = 2; 

    rob -> dir = rand() % 4; //selects random direction

    objX = (n - 1) * (rand() % 2); //chooses the objective corner at random
    objY = (n - 1) * (rand() % 2);

    //generates all obstacles
    for(int i = rand() % maximumNumberOfObstacles; i < maximumNumberOfObstacles; i++)   
        {   
            do
            {
                x = rand() % n;
                y = rand() % n;
            } while((x == rob -> x && y == rob -> y) || grid[x][y] == 2 || (x == objX && y == objY));
            grid[x][y] = 1;
        }

    return n;
}

int GenerateStage5(robot *rob)
{
    int n;
    int x, y;
    int direction;

    numberOfMarkers = rand() % 5;
    objective = 0;
    

    do //picks a random grid length between 10 and the max length
    {
        n = rand() % 100;
    } while (n > MAX_GRID_LENGTH || n < 10);

    //circle parameters
    double cx = n / 2.0;
    double cy = n / 2.0;
    double radius = (n / 2.0) - 2.0; //at least distance 2 from edges

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            double dx = i - cx + 0.5;
            double dy = j - cy + 0.5;
            double dist = sqrt(dx * dx + dy * dy);
            if (dist >= radius) 
                grid[i][j] = 1;
        }
    }

    do
    {
        x = rand() % n;
        y = rand() % n;  
    }while(grid[x][y] == 1);
    
    rob -> x = x;
    rob -> y = y;

    rob -> dir = rand() % 4; //selects random direction

    for(int i = 0; i < numberOfMarkers; i++)    
    {
        do
        {
            x = rand() % n;
            y = rand() % n;  
        }while(grid[x][y] == 1 || (x == rob -> x && y == rob -> y));
        grid[x][y] = 2;
    }

    return n;
}
