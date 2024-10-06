#include "../main.h"





// 3D Model ----------------------------------------------------------------------------------------
void LoadGLTFModel(ModelGLTF *ThisModel, char *ModelPath, Vector3 ModelPosition, float ModelScale) {
   ThisModel->Model = LoadModel(ModelPath);
   ThisModel->ModelPosition = (Vector3)ModelPosition;
   ThisModel->ModelScale = ModelScale;
}

void DrawGLTFModel(ModelGLTF *ThisModel) {
    DrawModel(ThisModel->Model, ThisModel->ModelPosition, ThisModel->ModelScale, WHITE);
}

// Animation ---------------------------------------------------------------------------------------
void LoadAnimation(Animation *ThisAnimation, ModelGLTF *ThisModel) {
    ThisAnimation->AnimsID = 0;
    ThisAnimation->AnimsFrameCounter = 0;
    // Load Animation in Anims
    ThisAnimation->Anims = LoadModelAnimations(ThisModel->ModelPath, &ThisAnimation->AnimsCount);
}

void PlayAnimation(Animation *ThisAnimation, ModelGLTF *ThisModel, bool PlayNow) {
    if (PlayNow) {
        ThisAnimation->AnimsFrameCounter++;
        UpdateModelAnimation(ThisModel->Model, ThisAnimation->Anims[ThisAnimation->AnimsID], ThisAnimation->AnimsFrameCounter); }
}

