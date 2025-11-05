//
//

#include "robot_navigation.h"
#include "robot.h"
#include "../drawing_logic/drawings.h"

//
void Forward(robot *rob)
{
    switch(rob -> dir)
    {
        case 0:
            rob -> y -= 1;
            break;
        case 1:
            rob -> x += 1;
            break;
        case 2:
            rob -> y += 1; 
            break;
        case 3:
            rob -> x -= 1;
            break;
        default:
            break;
    }
    UpdateDrawing(rob, numberOfCells);
}

void Left(robot *rob)
{
    rob -> dir = (rob -> dir - 1) % 4;
    UpdateDrawing(rob, numberOfCells);
}

void Right(robot *rob)
{
    rob -> dir = (rob -> dir + 1) % 4;
    UpdateDrawing(rob, numberOfCells);
}

int AtMarker(robot *rob)
{
    if (grid[rob -> x][rob -> y] == 2)
        return 1;
    return 0;
}

int CanMoveForward(robot *rob, int n)
{
    if ((rob -> dir == UP) && (rob -> y >= 0) && (grid[rob -> x][(rob -> y) - 1] != 1))
        return 1;
    if ((rob -> dir == RIGHT) && (rob -> x < n) && (grid[(rob -> x) + 1][rob -> y] != 1))
        return 1;
    if ((rob -> dir == DOWN) && (rob -> y < n) && (grid[rob -> x][(rob -> y) + 1] != 1))
        return 1;
    if ((rob -> dir == LEFT) && (rob -> x >= 0) && (grid[(rob -> x) - 1][rob -> y] != 1))
        return 1; 
    
    return 0;
}

void PickUpMarker(robot *rob)
{
    grid[rob -> x][rob -> y] = 0;

    rob -> markers += 1;
    
    UpdateDrawing(rob, numberOfCells);
}

void DropMarker(robot *rob)
{
    grid[rob -> x][rob -> y] = 2;

    rob -> markers -= 1;

    UpdateDrawing(rob, numberOfCells);
}

int MarkerCount(robot *rob)
{
    return rob -> markers;
}


