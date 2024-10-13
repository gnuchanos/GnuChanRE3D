#ifndef collisionfile
#define collisionfile

#include "../main.h"
#include "camera.h"

typedef struct {
    Vector3 *Position;
    Vector3 *Scale;
    int      SolidObjectCount;
    int      SolidObjectIndex;
} SolidCollision;

void DrawCollision(SolidCollision *ThisCollisions);
void CreateCollision(SolidCollision *ThisCollisions, char *Positions, char *Scales);
void CollisionEdit(SolidCollision *ThisCollisions, _CameraGO *ThisPlayer);
void FPS_WallCollision(_CameraGO *ThisPlayer, SolidCollision *SolidObjects);
void FPS_Area(_CameraGO *ThisPlayer, Vector3 AreaPosition, Vector3 AreaScale, bool *EnterArea);

#endif
