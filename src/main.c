#include "main.h"
#include "modules/model.h"
#include "modules/ui.h"
#include <raylib.h>

// Note: You can play .m3d animation


int main(void) {
    // Default Settings
    const int screenWidth = 940; const int screenHeight = 640;
    const char GameTitle[20] = "Game Title Here";
    InitWindow(screenWidth, screenHeight, GameTitle);
    SetExitKey(KEY_NULL);
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);
    Vector2 MousePosition = {0.0f, 0.0f};

    Font DefaultFont = LoadFont("./Assets/Font/Sans_normal.ttf");
    Color skycolor = BLUE;
    int CurrentScene = LOGO; 
    float logoTimer  = 2; char TimerLog[64];

    // ui for menu
    Button StartButton;
    CreateButton(&StartButton, DefaultFont, 30, "Start Game", 10, screenHeight/2,  WHITE, BLACK, BLACK, WHITE);

    // Load Test Model And Animation
    Model3D Test3D; 
    LoadModel3D(&Test3D, "./Assets/Models/nv.m3d", (Vector3){0.0f, 0.0f, 0.0f}, 1.7f);
    // Load Texture 
    Texture2D DefaultTexture = LoadTexture("./Assets/Texture/color_atlas.png");
    Texture2D NvM3DFaceTexture = LoadTexture("./Assets/Texture/face.png");
    // Apply Texture and Color
    Test3D.Model.materials[1].maps[MATERIAL_MAP_DIFFUSE].texture = DefaultTexture; // Color Palette
    Test3D.Model.materials[2].maps[MATERIAL_MAP_DIFFUSE].texture = NvM3DFaceTexture; // Face
    Test3D.Model.materials[4].maps[MATERIAL_MAP_ALBEDO].color = GPurple5; // Light

    // Load Animation 
    Animation Test3D_Animation; 
    LoadAnimation3D(&Test3D_Animation, &Test3D);
    Test3D_Animation.AnimsID = 3;



    // Default FPS Camera
    _CameraGO CAM = GOCAM();
    CAM.GO.position.x = 3;
    CAM.GO.position.z = 5;
    CAM.GO.target = (Vector3){0.0f, 1.5f, 0.0f};

    // Load Shader
    Shader shader = LoadShader(0, TextFormat("./Assets/Shader/bloom.fs", GLSL_VERSION));
    RenderTexture2D target = LoadRenderTexture(screenWidth, screenHeight);

    // Default Wall Example
    SolidCollision AllObject;
    AllObject.SolidObjectIndex = 0;
    CreateCollision(&AllObject, "./Assets/Collisions/level0_Position.gc", "./Assets/Collisions/level0_Scale.gc");
    char IndexDebug[128];
    sprintf(IndexDebug, "Wall Index: -> %d", AllObject.SolidObjectIndex);

    // Area Test
    Vector3      AreaPosition = (Vector3) {-1.0f, 0.0f, 0.0f};
    Vector3      AreaScale    = (Vector3) {5.0f, 5.0f, 5.0f};
    bool         AreaEnter    = false;
    char         AreaEnterDebug[128]; sprintf(AreaEnterDebug, "Area Enter: -> False");
    

    SetMousePosition(screenWidth/2, screenHeight/2);
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
        
        // Get Mouse Position
        MousePosition = GetMousePosition();

        if (CurrentScene == LOGO) {
            if (logoTimer > 0) {
                logoTimer -= 1 * GetFrameTime();
                sprintf(TimerLog, "Timer: %f", logoTimer);
            } else {
                logoTimer = 2;
                CurrentScene = MENU;
                CAM.ShowMouse = true;
                EnableCursor();
            }
        } else if (CurrentScene == MENU) {
            PressButton(&StartButton, MousePosition);
            if (StartButton.ButtonPress) {
                CurrentScene = GAMEPLAY;
                CAM.ShowMouse = false;
                DisableCursor();
            }
        } else if (CurrentScene == GAMEPLAY) {
            // Player And Collision test
            FPS(&CAM);

            // Wall Collisin and move Walls
            FPS_WallCollision(&CAM, &AllObject);
            CollisionEdit(&AllObject, &CAM);
            sprintf(IndexDebug, "Wall Index: -> %d", AllObject.SolidObjectIndex);

            // Area Enter Test
            FPS_Area(&CAM, AreaPosition, AreaScale, &AreaEnter);
            if (AreaEnter) { 
                sprintf(AreaEnterDebug, "Area Entering: -> True"); 
                skycolor = DARKGRAY;
            } else { 
                sprintf(AreaEnterDebug, "Area Entering: -> False"); 
                skycolor = DARKBLUE;
            }

            // Play GLTF Animation
            PlayAnimation3D(&Test3D_Animation, &Test3D, true);
        } else if (CurrentScene == END) {
        
        }

        BeginTextureMode(target);
            ClearBackground(skycolor);
            // only 3D
            if (CurrentScene == GAMEPLAY) {
                BeginMode3D(CAM.GO);
                    DrawGrid(10, 1.0f);
                    
                    // Draw Test Model
                    DrawModel3D(&Test3D);


                    // Drawll Walls for edit
                    DrawCollision(&AllObject);
                    DrawCube(AreaPosition, AreaScale.x, AreaScale.y, AreaScale.z, GPurple3);
                EndMode3D();        
            }

        EndTextureMode();

        BeginDrawing();
            BeginShaderMode(shader);
                // NOTE: Render texture must be y-flipped due to default OpenGL coordinates (left-bottom)
                DrawTextureRec(target.texture, (Rectangle){ 0, 0, (float)target.texture.width, (float)-target.texture.height }, (Vector2){ 0, 0 }, WHITE);
            EndShaderMode();
            if (CurrentScene == LOGO) {
                DrawRectangle(0, 0, screenWidth, screenHeight, GPurple0);
                DrawText(TimerLog, 10, 10, 30, GPurple5);
            } else if (CurrentScene == MENU) {
                DrawRectangle(0, 0, screenWidth, screenHeight, GPurple0);
                DrawText("Menu Scene", 10, 10, 30, GPurple5);
                
                // Test Draw UI->UI.h 
                DrawButton(&StartButton, DefaultFont);
                 
            } else if (CurrentScene == GAMEPLAY) {
               // Draw UI Here!
                DrawText(IndexDebug, 10, 10, 30, GPurple1);
                DrawText(AreaEnterDebug, 10, 40, 30, GPurple1);
                DrawFPS(screenWidth-100, 10);
           
            } else if (CurrentScene == END) {
            
            }
        EndDrawing();
    }


    // unload things
    UnloadFont(DefaultFont);
    UnloadButton(&StartButton);    


    CloseWindow();
    return 0; }
