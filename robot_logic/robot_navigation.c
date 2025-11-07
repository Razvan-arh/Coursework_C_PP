// holds the navigation logic and the main function

#include "../drawing_logic/drawings.h"
#include "robot.h"
#include "robot_navigation.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>

int grid[MAX_GRID_LENGTH][MAX_GRID_LENGTH] = {0};
int updateMarkers = 0;
int numberOfMarkers = 0;
int numberOfCells = 2;
int dirX[4] = {0, 1, 0, -1};
int dirY[4] = {-1, 0, 1, 0};
int objectiveCompleted = 0;
int objective = 0;
int objX = 0;
int objY = 0;

int main()
{
    // this is where I set the seed for the random function
    // it should be noted that I have left another function used for testing which completley randomizes the seed

    srand(SEED);
    //srand(time(NULL));

    // robot initialization
    robot mRobot;
    robot *rob = &mRobot;

    // default values
    rob -> markers = 0;
    rob -> dir = UP;
   
    // input function
    numberOfCells = ReadAll(rob);
     
    // verifies if the grid is valid
    if(numberOfCells > MAX_GRID_LENGTH || numberOfCells <= 3)
        return 0;
    

    // allocates memory for the robots internal map
    rob->knownMap = malloc(MAX_GRID_LENGTH * sizeof(int *));
        for (int i = 0; i < MAX_GRID_LENGTH; i++)
            rob->knownMap[i] = malloc(MAX_GRID_LENGTH * sizeof(int));

    // initializes his internal map as empty
    for (int i = 0; i < MAX_GRID_LENGTH; i++)
        for (int j = 0; j < MAX_GRID_LENGTH; j++)
            rob -> knownMap[i][j] = 0;
    
    
    // initializes drawing
    InitializeWindow();
    UpdateDrawing(rob, numberOfCells);

    // first main loop
    SimpleNavigation(rob, numberOfCells, 0);
    
    //if the objective is to bring the markers back, it enters the second loop 
    if(objective == 1)
    {
        objectiveCompleted = 0;
        SimpleNavigation(rob, numberOfCells, 1); 
    }

    
   return 0;
}


// maze solving logic
void TurnTo(robot *rob, int new_dir) // goes to a certain direction
{
    int turn = (new_dir - rob -> dir + 4) % 4;

    if(turn == 0) return;

    if(turn == 1) Right(rob);

    else if(turn == 2) 
    { Right(rob); Right(rob); }

    else if(turn == 3) Left(rob);
}

// A depth first search algorithm that employs backtracking
// This part of the code has been debugged with the help of LLM (Chat GPT, Gemini)
void SimpleNavigation(robot *rob, int n, int currentObjective) 
{
    //checks for objectives and the type of objective
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
                updateMarkers = 1;
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

            if(CanMoveForward(rob, n)) {

                if(objectiveCompleted)
                    return;
                
                Forward(rob);
                rob -> knownMap[nx][ny] = 2;
                SimpleNavigation(rob, n, currentObjective);

                if(objectiveCompleted)
                    return;
                
                // backtrack
                TurnTo(rob, (new_dir + 2) % 4); // turn back
                if(CanMoveForward(rob, n))
                    Forward(rob);
                TurnTo(rob, direction); // restore original direction
            }
        }
    }
}

