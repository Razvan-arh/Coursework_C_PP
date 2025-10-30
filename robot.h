//Holds declarations of robot control functions
//

typedef enum _orientation {UP = 0, RIGHT, DOWN, LEFT}orientation;


typedef struct _Robot
{
    int x,y;
    int markers;
    orientation dir;

}robot;

void Forward(robot *);
void Left(robot *);
void Right(robot *);
int AtMarker();
int CanMoveForward();
void PickUpMarker();
void DropMarker();
int MarkerCount();