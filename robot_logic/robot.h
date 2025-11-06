//Holds declarations of robot control functions
//
#ifndef ROBOT_H
#define ROBOT_H

typedef enum _orientation {UP = 0, RIGHT, DOWN, LEFT}orientation;

#include "robot_navigation.h"

typedef struct _Robot
{
    int x,y;
    int markers;
    orientation dir;
    int **knownMap;
}robot;

void Forward(robot *);
void Left(robot *);
void Right(robot *);
int AtMarker();
int CanMoveForward();
void PickUpMarker();
void DropMarker();
int MarkerCount();

#endif