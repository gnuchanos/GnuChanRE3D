#ifndef modelfile
#define modelfile

#include "../main.h"

typedef struct {
    Model    Model;
    char    *ModelPath;
    Vector3  ModelPosition;
    float  ModelScale;
} ModelGLTF;

typedef struct {
    int AnimsFrameCounter;
    ModelAnimation *Anims;
    int AnimsID;
    int AnimsCount;
} Animation;

void LoadGLTFModel(ModelGLTF *ThisModel, char *ModelPath, Vector3 ModelPosition, float ModelScale);
void DrawGLTFModel(ModelGLTF *ThisModel);
void LoadAnimation(Animation *ThisAnimation, ModelGLTF *ThisModel);
void PlayAnimation(Animation *ThisAnimation, ModelGLTF *ThisModel, bool PlayNow);



#endif