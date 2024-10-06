#include "../main.h"
#include "camera.h"


void DrawCollision(SolidCollision *ThisCollisions) {
    int WallCount = ThisCollisions->SolidObjectCount;
    for (int i = 0; i < WallCount; i++) {
        DrawCube(ThisCollisions->Position[i], ThisCollisions->Scale[i].x, ThisCollisions->Scale[i].y, ThisCollisions->Scale[i].z, GPurple1);
    }
}


// Read 2 gc file for create Wall Position and Scale -> Vector3 ---------------------
void CreateCollision(SolidCollision *ThisCollisions, char *Positions, char *Scales) {
    FILE *Positions_File; FILE *Scales_File;
    int PositionLineCount = 0; int ScalesLineCount = 0;
    char Read_Position; char Read_Scale;

    Positions_File = fopen(Positions, "r");
    if (Positions_File != NULL) {
        while ((Read_Position = fgetc(Positions_File)) != EOF) {
            if (Read_Position == '\n') { PositionLineCount++; } 
        } rewind(Positions_File);
    } else { printf("File Read Problem Position File"); }
   
    Scales_File = fopen(Scales,   "r");
    if (Scales_File != NULL) {
        while ((Read_Scale = fgetc(Scales_File)) != EOF) {
            if (Read_Scale    == '\n') { ScalesLineCount++; } 
        } rewind(Scales_File);
    } else { printf("File Read Problem Scale File"); }
    
    // Copy Wall Count
    ThisCollisions->SolidObjectCount = PositionLineCount;
    if (PositionLineCount > 1) {
        if (PositionLineCount == ScalesLineCount) {
            ThisCollisions->Position = (Vector3*)malloc(PositionLineCount * sizeof(Vector3));
            ThisCollisions->Scale    = (Vector3*)malloc(ScalesLineCount   * sizeof(Vector3));
            for (int i = 0; i < PositionLineCount; i++) {
                fscanf(Positions_File, "%f %f %f", &ThisCollisions->Position[i].x, &ThisCollisions->Position[i].y, &ThisCollisions->Position[i].z);
                fscanf(Scales_File, "%f %f %f", &ThisCollisions->Scale[i].x, &ThisCollisions->Scale[i].y, &ThisCollisions->Scale[i].z);
            }
        }
    } else { printf("Collision Size Must be more than 1"); }
    fclose(Positions_File); fclose(Scales_File); 
}


// Write Vector3 Collision to File
void WriteCollisionToFile(SolidCollision *ThisCollisions, char *Positions, char *Scales) {
    FILE *Positions_File; FILE *Scales_File;
    Positions_File = fopen(Positions, "w"); Scales_File = fopen(Scales, "w");

    if (Positions_File != NULL) {
       for (int i = 0; i < ThisCollisions->SolidObjectCount; i++) {
            fprintf(Positions_File, "%f %f %f\n", ThisCollisions->Position[i].x, ThisCollisions->Position[i].y, ThisCollisions->Position[i].z); } // END
    } else { printf("Position File Problem! -> Write"); } fclose(Positions_File);

    if (Scales_File != NULL) {
        for (int i = 0; i < ThisCollisions->SolidObjectCount; i++) {
            fprintf(Scales_File, "%f %f %f\n", ThisCollisions->Scale[i].x, ThisCollisions->Scale[i].y, ThisCollisions->Scale[i].z); } // END
    } else { printf("Scale File Problem! -> Write"); } fclose(Scales_File); 
}


// not finish yet
void CollisionEdit(SolidCollision *ThisCollisions, _CameraGO *ThisPlayer, int IndexHere) {
    if (isdigit(IndexHere)) { ThisCollisions->SolidObjectIndex = IndexHere;  } else { ThisCollisions->SolidObjectIndex = 0; }
    if (IsKeyPressed(KEY_Q) && ThisCollisions->SolidObjectIndex > 0) { 
        ThisCollisions->SolidObjectIndex--; }
    else if (IsKeyPressed(KEY_E) && ThisCollisions->SolidObjectCount > ThisCollisions->SolidObjectIndex) { 
        ThisCollisions->SolidObjectIndex++; }

    if (IsKeyDown(KEY_LEFT_ALT)) {
       ThisPlayer->StopMove = true;

    } else if (IsKeyDown(KEY_LEFT_CONTROL)) {
    
    } else { ThisPlayer->StopMove = false; }
    

}


// This is only Simple walls
void FPS_WallCollision(_CameraGO *ThisPlayer, SolidCollision *SolidObjects) {
    ThisPlayer->BodyHit = false;
    for (int i = 0; i < SolidObjects->SolidObjectCount; i++) {
        if (CheckCollisionBoxes(
            (BoundingBox){
                (Vector3){ 
                    ThisPlayer->GO.position.x - ThisPlayer->BodySize.x/2,
                    ThisPlayer->GO.position.y - ThisPlayer->BodySize.y/2,
                    ThisPlayer->GO.position.z - ThisPlayer->BodySize.z/2 },
                (Vector3){ 
                    ThisPlayer->GO.position.x + ThisPlayer->BodySize.x/2,
                    ThisPlayer->GO.position.y + ThisPlayer->BodySize.y/2,
                    ThisPlayer->GO.position.z + ThisPlayer->BodySize.z/2 } 
            },

            (BoundingBox){
                (Vector3){ 
                    SolidObjects->Position[i].x - SolidObjects->Scale[i].x/2,
                    SolidObjects->Position[i].y - SolidObjects->Scale[i].y/2,
                    SolidObjects->Position[i].z - SolidObjects->Scale[i].z/2 },
                (Vector3){ 
                    SolidObjects->Position[i].x + SolidObjects->Scale[i].x/2,
                    SolidObjects->Position[i].y + SolidObjects->Scale[i].y/2,
                    SolidObjects->Position[i].z + SolidObjects->Scale[i].z/2 } 
            })
        ) { ThisPlayer->BodyHit = true; break; } // Ends if In For Loop
    } // Ends For Loop
}


// This is for Triger Event ----------------------------------------------------------------------
void FPS_Area(_CameraGO *ThisPlayer, Vector3 *AreaPosition, Vector3 *AreaScale, bool *EnterArea) {
    *EnterArea = false;
    if (CheckCollisionBoxes(
        (BoundingBox){
            (Vector3){ 
                ThisPlayer->GO.position.x - ThisPlayer->BodySize.x/2,
                ThisPlayer->GO.position.y - ThisPlayer->BodySize.y/2,
                ThisPlayer->GO.position.z - ThisPlayer->BodySize.z/2 },
            (Vector3){ 
                ThisPlayer->GO.position.x + ThisPlayer->BodySize.x/2,
                ThisPlayer->GO.position.y + ThisPlayer->BodySize.y/2,
                ThisPlayer->GO.position.z + ThisPlayer->BodySize.z/2 } 
        },

        (BoundingBox){
            (Vector3){ 
                AreaPosition->x - AreaScale->x/2,
                AreaPosition->y - AreaScale->y/2,
                AreaPosition->z - AreaScale->z/2 },
            (Vector3){ 
                AreaPosition->x + AreaScale->x/2,
                AreaPosition->y + AreaScale->y/2,
                AreaPosition->z + AreaScale->z/2 } 
        })
    ) { *EnterArea = true; }
}


