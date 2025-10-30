//
//

#include "robot_main.h"
#include "robot.h"



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

int CanMoveForward(robot *rob)
{

}

void PickUpMarker(robot *rob)
{

}

void DropMarker(robot *rob)
{

}

int MarkerCount(robot *rob)
{
    return rob -> markers;
}