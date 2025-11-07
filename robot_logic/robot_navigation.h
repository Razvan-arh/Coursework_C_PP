//important varaibles and functions that may be needed throught the codebase
//mostly realted to input

#ifndef ROBOT_NAVIGATION_H
#define ROBOT_NAVIGATION_H

#include <stdio.h>
#include "robot.h"

#define MAX_GRID_LENGTH 25 //number of cells
#define SEED 235 // testing seed


extern int grid[MAX_GRID_LENGTH][MAX_GRID_LENGTH];  //holds the complete map
                                                    //free space = 0
                                                    //obstacle = 1
                                                    //marker = 2
                                                    //grid is labled from leftmost corner

extern int numberOfMarkers;
extern int updateMarkers;
extern int numberOfCells;
extern int objective;   //there are 2 main objectives
                        // 0 - for just getting all the markers
                        // 1 - for puting markers in a corner
                        //if unspecified it is assumed 0

//only used for objective 1
extern int objX; 
extern int objY;

void SimpleNavigation();
void TurnTo();
int ReadAll();

#endif