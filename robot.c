//
//

#include "robot_navigation.h"
#include "robot.h"


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
}

void Left(robot *rob)
{
    if(rob -> dir == UP)
        rob -> dir = LEFT;
    else
        rob -> dir -= 1;
}

void Right(robot *rob)
{
    if(rob -> dir == LEFT)
        rob -> dir = UP;
    else
        rob -> dir += 1;
}

int AtMarker(robot *rob)
{
    if (grid[rob -> x][rob -> y] == 2)
        return 1;
    return 0;
}

int CanMoveForward(robot *rob, int n)
{
    if ((rob -> dir == UP) && (rob -> y != 0) && (grid[rob -> x][rob -> y - 1] == 1))
        return 0;
    if ((rob -> dir == RIGHT) && (rob -> x != (n - 1)) && (grid[rob -> x + 1][rob -> y] == 1))
        return 0;
    if ((rob -> dir == DOWN) && (rob -> y != (n - 1)) && (grid[rob -> x][rob -> y + 1] == 1))
        return 0;
    if ((rob -> dir == LEFT) && (rob -> x != 0) && (grid[rob -> x - 1][rob -> y] == 1))
        return 0; 
    
    return 1;
}

void PickUpMarker(robot *rob)
{
    grid[rob -> x][rob -> y] = 0;

    rob -> markers += 1;
}

void DropMarker(robot *rob)
{
    grid[rob -> x][rob -> y] = 2;

    rob -> markers -= 1;
}

int MarkerCount(robot *rob)
{
    return rob -> markers;
}


