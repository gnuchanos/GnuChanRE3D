#include "../main.h"

// Simple way to Crate Camera for fps player -------------------------------------------------------
_CameraGO GOCAM() {
    _CameraGO GO;
    GO.GO.position = (Vector3){ 0.0f, 1.5f, 0.0f };    // Camera position
    GO.GO.target =   (Vector3){ -1.45, 1.5f, -2.20f };    // Camera looking at point
    GO.GO.up =       (Vector3){ 0.0f, 1.0f, 0.0f };     // Camera up vector (rotation towards target)
    GO.GO.fovy = 90.0f;                                 // Camera field-of-view Y
    GO.GO.projection = CAMERA_PERSPECTIVE;              // Camera projection type

    GO.RecordCamPosition = (Vector3){ 5.0f, 1.5f, 5.0f };
    GO.BodySize          = (Vector3){ 0.1f, 1.5f,  0.1f };
    GO.BodyHit           = false;
    GO.ShowMouse         = false;
    GO.StopMove          = false;
    GO.SettingsMode      = false;
    return GO; 
}

// Simple fps player only record x,z for wall --------------
void FPS(_CameraGO *Player) {

    // Stop move and rotate
    Vector3 Movement = (Vector3){0.0f, 0.0f, 0.0f};
    Vector3 Rotation = (Vector3){0.0f, 0.0f, 0.0f};
    float Zoom = 0.0f;

    if (Player->BodyHit) {
        Player->GO.position.x = Player->RecordCamPosition.x;
        Player->GO.position.z = Player->RecordCamPosition.z;
    } else {
        Player->RecordCamPosition.x = Player->GO.position.x;
        Player->RecordCamPosition.z = Player->GO.position.z;
    }

    if (!Player->SettingsMode) {
        Vector2 mouseDelta = GetMouseDelta();
        Rotation.x = mouseDelta.x; Rotation.y = mouseDelta.y;
    }

    // maybe i can chair i see in x.com it's cool
    if (!Player->StopMove) {
        if (!Player->SettingsMode) {
            if (IsKeyDown(KEY_W)) { Movement.x =  0.05f; } else if (IsKeyDown(KEY_S)) { Movement.x = -0.05f; }
            if (IsKeyDown(KEY_A)) { Movement.y = -0.05f; } else if (IsKeyDown(KEY_D)) { Movement.y =  0.05f; }
        }
    }

    
    UpdateCameraPro(&Player->GO, Movement, Rotation, Zoom);
}

