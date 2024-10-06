#include "main.h"




int main(void) {
    // Default Settings
    const int screenWidth = 940; const int screenHeight = 640;
    const char GameTitle[20] = "Game Title Here";
    InitWindow(screenWidth, screenHeight, GameTitle);
    SetExitKey(KEY_NULL);
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);

    // Default FPS Camera
    _CameraGO CAM = GOCAM();

    // Load Shader
    Shader shader = LoadShader(0, TextFormat("./Assets/Shader/bloom.fs", GLSL_VERSION));
    RenderTexture2D target = LoadRenderTexture(screenWidth, screenHeight);





    SetTargetFPS(60); DisableCursor();
    while (!WindowShouldClose()) {
        // Show Cursor or Hide
        if (IsKeyPressed(KEY_ESCAPE) && CAM.ShowMouse) {
            CAM.ShowMouse = false;
            DisableCursor();
        } else if (IsKeyPressed(KEY_ESCAPE) && !CAM.ShowMouse) {
            CAM.ShowMouse = true;
            EnableCursor(); 
        }
        FPS(&CAM);


        BeginTextureMode(target);
            ClearBackground(BLUE);
            BeginMode3D(CAM.GO);
                DrawGrid(10, 1.0f);
                //DrawModel(model, (Vector3){0.0f, 0.0f, 0.0f}, 1.0f, WHITE);






            EndMode3D();
        EndTextureMode();

        BeginDrawing();
            BeginShaderMode(shader);
                // NOTE: Render texture must be y-flipped due to default OpenGL coordinates (left-bottom)
                DrawTextureRec(target.texture, (Rectangle){ 0, 0, (float)target.texture.width, (float)-target.texture.height }, (Vector2){ 0, 0 }, WHITE);
            EndShaderMode();
            // Draw UI Here!
            DrawFPS(10, 10);

        EndDrawing();
    }
    // unload things



    CloseWindow();
    return 0; }
