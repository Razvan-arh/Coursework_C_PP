//definition of draw functions both foreground and background

#include "../robot_logic/robot.h"
#include "../robot_logic/robot_navigation.h"
#include "math.h"
#include "drawings.h"

#define PI 3.14159265358979323846

const int cellSize = 35;
int isDrawingBackground = 0;
int isDrawingForeground = 0;

//background
void DrawGrid(int n) //n represents the number of cells
{
    setColour(black);

    for (int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            drawRect(UPP_CORNER_X + i * cellSize, UPP_CORNER_Y + j * cellSize, cellSize, cellSize);

    setColour(red);
    drawRect(UPP_CORNER_X, UPP_CORNER_Y, n * cellSize, n * cellSize);
}

void DrawObstacle(int x, int y) //coordinates of the cell
{
    setColour(black);

    //calculate where to draw obstacle based on the cell position
    //chose the magic numbers based on what looked the pretiest they don't appear anywhere else

    int cornerX = UPP_CORNER_X + x * cellSize + 2;
    int cornerY = UPP_CORNER_Y + y * cellSize + 2;
    int length = cellSize - 4;

    fillRect(cornerX, cornerY, length, length); 
    
}

void DrawMarker(int x, int y)
{
    setColour(gray);

    //same logic as DrawObstacle
    int cornerX = UPP_CORNER_X + x * cellSize + 3;
    int cornerY = UPP_CORNER_Y + y * cellSize + 3;
    int length = cellSize - 6;

    fillArc(cornerX, cornerY, length, length,0,360);
}

//foreground
void DrawRobot(int x, int y, orientation dirFacing)
{
    setColour(blue);

    int triX[3], triY[3];
    double angle;

    switch(dirFacing)
    {
        case 0:
            triX[0] = UPP_CORNER_X + x * cellSize + cellSize / 2;
            triY[0] = UPP_CORNER_Y + y * cellSize + cellSize / 4;
            angle = 0;
            break;
        case 1:
            triX[0] = UPP_CORNER_X + x * cellSize + cellSize - cellSize / 4;
            triY[0] = UPP_CORNER_Y + y * cellSize + cellSize / 2;
            angle = PI * 3 / 2;
            break;
        case 2:
            triX[0] = UPP_CORNER_X + x * cellSize + cellSize / 2;
            triY[0] = UPP_CORNER_Y + y * cellSize + cellSize - cellSize / 4;
            angle = PI;
            break;
        case 3:
            triX[0] = UPP_CORNER_X + x * cellSize + cellSize / 4;
            triY[0] = UPP_CORNER_Y + y * cellSize + cellSize - cellSize / 2;
            angle = PI / 2;
            break;
        default:
            break;
    }

    triX[1] = triX[0] + (int)((sin(angle)) * (cellSize / 3 * 2) + (cos(angle)) * 10); //sin + cos0
    triY[1] = triY[0] + (int)((cos(angle)) * (cellSize / 3 * 2) + (sin(angle)) * 10); //sin0 cos -
    triX[2] = triX[0] + (int)((sin(angle)) * (cellSize / 3 * 2) - (cos(angle)) * 10); //sin - cos0
    triY[2] = triY[0] + (int)((cos(angle)) * (cellSize / 3 * 2) - (sin(angle)) * 10); //sin 0 cos +

    fillPolygon(3, triX, triY);

    setColour(red);
    drawLine(triX[1] + (int)(cos(angle)) * 2, triY[1] + (int)(sin(angle)) * 2, triX[2] - (int)(cos(angle)) * 2, triY[2] - (int)(sin(angle)) * 2);
}

//drawing logic
void InitializeWindow()
{
    setWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
}

void DrawBackground(int numberOfCells)
{
    background();
    isDrawingBackground = 1;
    isDrawingForeground = 0;

    clear();

    DrawGrid(numberOfCells);

    for(int i = 0; i < numberOfCells; i++)
        for(int j = 0; j < numberOfCells; j++)
        {
            if(grid[i][j] == 1)
                DrawObstacle(i, j);
            if(grid[i][j] == 2)
                DrawMarker(i, j);
        }
    
}

void DrawForeground(int robotX, int robotY, orientation robotDirection)
{
    if(!isDrawingForeground)
    {    
        foreground();
        isDrawingForeground = 1;
        isDrawingBackground = 0;
    }

    clear();
    
    DrawRobot(robotX, robotY, robotDirection);
}

void UpdateDrawing(robot *rob, int n)
{
    if(isDrawingBackground == 0 && isDrawingForeground == 0)
    {
        DrawBackground(n);
        DrawForeground(rob -> x, rob -> y, rob -> dir);
    }
    else if(updateMarkers)
    {
        DrawBackground(n);
        DrawForeground(rob -> x, rob -> y, rob -> dir);
        updateMarkers = 0;
    }
    else
        DrawForeground(rob -> x, rob -> y, rob -> dir);
    sleep(UPDATE_SPEED);
}