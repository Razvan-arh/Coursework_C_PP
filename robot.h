//Holds declarations of robot control functions
//

typedef enum _orientation {UP = 0, RIGHT, DOWN, LEFT}orientation;


typedef struct _Robot
{
    int x,y;
}robot;

void Forward();
void Left();
void Right();
int AtMarker();
int CanMoveForward();
void PickUpMarker();
void DropMarker();
int MarkerCount();