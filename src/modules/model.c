#include "model.h"
#include "../main.h"





// 3D Model ----------------------------------------------------------------------------------------
void LoadModel3D(Model3D *ThisModel, char *ModelPath, Vector3 ModelPosition, float ModelScale) {
    // Default Model Settings
    ThisModel->Model = LoadModel(ModelPath);
    ThisModel->ModelPosition = (Vector3)ModelPosition;
    ThisModel->ModelScale = ModelScale;

    // Model Path Must Free
    ThisModel->ModelPath = (char *)malloc((strlen(ModelPath) + 1) * sizeof(char));    
    strcpy(ThisModel->ModelPath, ModelPath);
}

void DrawModel3D(Model3D *ThisModel) {
    DrawModel(ThisModel->Model, ThisModel->ModelPosition, ThisModel->ModelScale, WHITE);
}

// Animation ---------------------------------------------------------------------------------------
void LoadAnimation3D(Animation *ThisAnimation, Model3D *ThisModel) {
    // Default Animation Settings
    ThisAnimation->AnimsCount = 0;
    ThisAnimation->AnimsID = 0;
    ThisAnimation->AnimsFrameCounter = 0;

    // Load Animation in Anims
    ThisAnimation->Anims = LoadModelAnimations(ThisModel->ModelPath, &ThisAnimation->AnimsCount);
}

void PlayAnimation3D(Animation *ThisAnimation, Model3D *ThisModel, bool PlayNow) {
    if (PlayNow) {
        ThisAnimation->AnimsFrameCounter++;
        UpdateModelAnimation(ThisModel->Model, ThisAnimation->Anims[ThisAnimation->AnimsID], ThisAnimation->AnimsFrameCounter); }
}

