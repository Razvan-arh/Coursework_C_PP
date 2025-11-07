// holds declarations of robot control functions and robot structs

#ifndef ROBOT_H
#define ROBOT_H

#include "robot_navigation.h"


typedef enum _orientation {UP = 0, RIGHT, DOWN, LEFT}orientation;


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
int AtMarker(robot *);
int CanMoveForward(robot *, int);
void PickUpMarker(robot *);
void DropMarker(robot *);
int MarkerCount(robot *);

#endif