//declaration of all drawing functions

#ifndef DRAWINGS_H
#define DRAWINGS_H

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000
#define UPP_CORNER_X 30 // top left corner
#define UPP_CORNER_Y 30
#define UPDATE_SPEED 50 //sleep time, it looks best at 50

#include "graphics.h"
#include "../robot_logic/robot.h"

extern const int cellSize;

extern int isDrawingBackground;
extern int isDrawingForeground;

//declaration of background drawing functions
void DrawGrid(int); 
void DrawObstacle(int, int);
void DrawMarker(int, int);

//declaration of foreground drawing functions
void DrawRobot(int, int, orientation);

//drawing logic
void DrawBackground(int); //draws grid obstacles and markers
void DrawForeground(int, int, orientation); //draws the robot
void InitializeWindow(void);
void UpdateDrawing(robot *, int);

#endif 