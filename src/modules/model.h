#ifndef modelfile
#define modelfile

#include "../main.h"

typedef struct {
    Model    Model;
    char    *ModelPath;
    Vector3  ModelPosition;
    float  ModelScale;
} Model3D;

typedef struct {
    int AnimsFrameCounter;
    ModelAnimation *Anims;
    int AnimsID;
    int AnimsCount;
} Animation;

void LoadModel3D(Model3D *ThisModel, char *ModelPath, Vector3 ModelPosition, float ModelScale); 
void DrawModel3D(Model3D *ThisModel);
void LoadAnimation3D(Animation *ThisAnimation, Model3D *ThisModel); 
void PlayAnimation3D(Animation *ThisAnimation, Model3D *ThisModel, bool PlayNow); 



#endif
