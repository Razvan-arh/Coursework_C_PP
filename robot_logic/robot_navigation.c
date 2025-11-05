//
//

#include "../drawing_logic/drawings.h"
#include "robot.h"
#include "robot_navigation.h"
#include <string.h>


int grid[MAX_GRID_LENGTH][MAX_GRID_LENGTH] = {0};
int updateMarkers;
int numberOfMarkers = 0;
int numberOfCells = 2;
int dirX[] = {0, 1, 0, -1};
int dirY[] = {-1, 0, 1, 0};
int objectiveCompleted = 0;
int objective = 0;
int objX;
int objY;

int main()
{
    
    int updateMarkers = 0;
    robot mRobot;
    robot *rob = &mRobot;

    rob -> markers = 0;
    rob -> dir = UP;
    
    numberOfCells = ReadAll(rob);
     
    if(numberOfCells > MAX_GRID_LENGTH)
        return 0;
    
    for (int i = 0; i < numberOfCells; i++)
        for (int j = 0; j < numberOfCells; j++)
        rob -> knownMap[i][j] = 0;
    
    
    // logic
    InitializeWindow();
    UpdateDrawing(rob, numberOfCells);

    // loop
    SimpleNavigation(rob, numberOfCells, 0);
    
    if(objective == 1)
    {
        objectiveCompleted = 0;
        SimpleNavigation(rob, numberOfCells, 1); //TODO make it draw the droped marker
    }

    
   return 0;
}


//
void TurnTo(robot *rob, int new_dir) {
    int turn = (new_dir - rob -> dir + 4) % 4;
    if(turn == 1) Right(rob);
    else if(turn == 2) { Right(rob); Right(rob); }
    else if(turn == 3) Left(rob);
}


void SimpleNavigation(robot *rob, int n, int currentObjective) {
    rob -> knownMap[rob -> x][rob -> y] = 2;
    
    if(objectiveCompleted)
       return;

    if(currentObjective == 0){
        if(AtMarker(rob))
        {
            updateMarkers = 1;
            PickUpMarker(rob);
            
            if(MarkerCount(rob) == numberOfMarkers)
                {
                    objectiveCompleted = 1;
                    return;   
                }
        }
    }
    else if(currentObjective == 1)
    {
        if(rob -> x == objX && rob -> y == objY)
            {
                DropMarker(rob);
                objectiveCompleted = 1;
                return; 
            }  
    }


    for(int i = 0; i < 4; i++) {
        if(objectiveCompleted)
            break;

        int direction = rob -> dir;
        int new_dir = (direction + i) % 4; // check all directions
        int nx = rob -> x + dirX[new_dir];
        int ny = rob -> y + dirY[new_dir];
    

        if(nx >= 0 && nx < n && ny >= 0 && ny < n && rob -> knownMap[nx][ny] != 2) {
            TurnTo(rob, new_dir);
            if(CanMoveForward(rob)) {
                if(objectiveCompleted)
                    return;
                Forward(rob);
                SimpleNavigation(rob, n, currentObjective);
                if(objectiveCompleted)
                    return;
                // backtrack
                TurnTo(rob, (new_dir + 2) % 4); // turn back
                if(CanMoveForward(rob))
                    Forward(rob);
                TurnTo(rob, direction); // restore original direction
            }
        }
    }
}

