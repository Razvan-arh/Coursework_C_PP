//
//

#include "drawings.h"
#include "robot.h"
#include "robot_navigation.h"
#include <string.h>


int grid[20][20] = {0};
int numberOfMarkers = 0;
int numberOfCells = 2;
int dirX[] = {-1, 0, 1, 0};
int dirY[] = {0, 1, 0, -1};



int main()
{
    
    int updateMarkers = 0;
    robot mRobot;
    robot *rob = &mRobot;
    numberOfCells = ReadAll(rob);
    
    for (int i = 0; i < numberOfCells; i++)
        for (int j = 0; j < numberOfCells; j++)
        rob -> knownMap[i][j] = 0;
    // logic
    
    InitializeWindow();
    UpdateDrawing(rob, numberOfCells);

    // loop
    SimpleNavigation(rob, numberOfCells);
    
    //implement task
    
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
    UpdateDrawing(rob, n);

    rob -> knownMap[rob->x][rob->y] = 0;
    
    if(grid[rob -> x][rob -> y] == 2)
    {
        PickUpMarker(rob);
        updateMarkers = 1;
    }
    if(MarkerCount() == numberOfMarkers)
        return;
    
    for(int i = 0; i < 4; i++)
    {
        int newDir = (rob -> dir + i) % 4;
        int newX = rob -> x + dirX[i];
        int newY = rob -> y + dirY[i];

        while(rob -> dir != newDir)
            Right(rob);

        if(newX >= 0 && newY >= 0 && newX < n && newY < n && rob -> knownMap[newX][newY] == 0)
        {
            if(CanMoveForward(rob, n))
            {
                Forward(rob);
                SimpleNavigation(rob, n);
                GoBack(rob);
            }
            else
            {
                rob -> knownMap[newX][newY] = 1;
            }
        }
    }

}
