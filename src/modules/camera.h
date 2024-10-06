#ifndef camerafile
#define camerafile

#include "../main.h"


typedef struct {
    Camera3D GO;
    Vector3 RecordCamPosition;
    Vector3 BodySize;
    bool    BodyHit;
    bool    ShowMouse;
    bool    StopMove;
} _CameraGO;

_CameraGO GOCAM();
void FPS(_CameraGO *Player);


#endif