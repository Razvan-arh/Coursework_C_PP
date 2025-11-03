//Holds declarations of robot control functions
//
#ifndef ROBOT_H
#define ROBOT_H

typedef enum _orientation {UP = 0, RIGHT, DOWN, LEFT}orientation;


typedef struct _Robot
{
    int x,y;
    int markers;
    orientation dir;
    int knownMap[20][20];
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