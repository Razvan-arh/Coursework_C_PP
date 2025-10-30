//declaration of all drawing functions
#define WINDOW_WIDTH 850
#define WINDOW_HEIGHT 850
#define UPP_CORNER_X 30
#define UPP_CORNER_Y 30

#include "graphics.h"

const int cellSize = 20;

int isDrawingBackground = 0;
int isDrawingForeground = 0;

//declaration of background drawing functions
void DrawGrid(int);
void DrawObstacle(int, int);
void DrawMarker(int, int);

//declaration of foreground drawing functions
void DrawRobot(int, int, orientation);

//drawing logic
void DrawBackground(int);
void DrawForeground();
void InitializeWindow(void);