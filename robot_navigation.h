//important varaibles and functions that may be needed throught the codebase
//mostly realted to input

#ifndef ROBOT_NAVIGATION_H
#define ROBOT_NAVIGATION_H

#include <stdio.h>

#define SLEEP_DURATION 100

extern FILE *inputPtr;
extern FILE *fileptr;

extern int grid[20][20];//most important variable in the code
                 //free space = 0
                 //obstacle = 1
                 //marker = 2
                 //grid is numbered from leftmost corner

extern int numberOfMarkers;
extern int updateMarkers;
extern int numberOfCells;

void SimpleNavigation();
void GoBack();
int ReadAll();

#endif