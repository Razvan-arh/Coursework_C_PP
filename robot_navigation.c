//
//

#include "drawings.h"
#include "robot.h"
#include "robot_navigation.h"
#include <string.h>


int grid[MAX_GRID_LENGTH][MAX_GRID_LENGTH] = {0};
int numberOfMarkers = 0;
int numberOfCells = 2;
int dirX[] = {0, 1, 0, -1};
int dirY[] = {-1, 0, 1, 0};
int allMarkersCollected = 0;


int main()
{
    
    int updateMarkers = 0;
    robot mRobot;
    robot *rob = &mRobot;

    numberOfCells = ReadAll(rob);
    if(numberOfCells > MAX_GRID_LENGTH)
        return 0;
    
    for (int i = 0; i < numberOfCells; i++)
        for (int j = 0; j < numberOfCells; j++)
        rob -> knownMap[i][j] = 0;
    
    rob -> markers = 0;
    rob -> dir = UP;

    // logic
    InitializeWindow();
    UpdateDrawing(rob, numberOfCells);

    // loop
    SimpleNavigation(rob, numberOfCells);
    
    //TODO implement task
    
   return 0;
}


//

void GoBack(robot *rob)
{
    Right(rob);
    Right(rob);
    Forward(rob);
    Right(rob);
    Right(rob);
}

void SimpleNavigation(robot *rob, int n)
{
    rob -> knownMap[rob->x][rob->y] = 2;
    
    if(allMarkersCollected)
       return;

    if(AtMarker(rob))
    {
        updateMarkers = 1;
        PickUpMarker(rob);
        
        if(MarkerCount(rob) == numberOfMarkers)
            {
                allMarkersCollected = 1;
                return;   
            }
    }

    if(numberOfMarkers == 1)
        drawLine(10, 10, 100, 100);
    
    for(int i = 0; i < 4; i++)
    {
        if(allMarkersCollected)
            break;

        int newDir = (rob -> dir + i) % 4;
        int newX = rob -> x + dirX[newDir];
        int newY = rob -> y + dirY[newDir];

        while(rob -> dir != newDir)
            Right(rob);

        if(newX >= 0 && newY >= 0 && newX < n && newY < n && rob -> knownMap[newX][newY] == 0)
        {
            if(CanMoveForward(rob, n))
            {
                if(allMarkersCollected)
                    return;

                Forward(rob);
                SimpleNavigation(rob, n);

                if(allMarkersCollected)
                    return;    
                else
                    GoBack(rob);
            }
            else
            {
                rob -> knownMap[newX][newY] = 1;
            }
        }
    }

}
