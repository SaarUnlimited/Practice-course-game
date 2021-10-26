#include "raylib.h"

struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

int main()
{
    int windowDimensions[2];
    windowDimensions[0] = 518;
    windowDimensions[1] = 400;


    //Initialize The Window
    InitWindow(windowDimensions[0], windowDimensions[1], "Dapper Dasher");

    //Acceleration due to gravity (pixels/s)/s
    const int gravity{1'000};

    //nebula variables
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

    //AnimData for nebula
    AnimData nebData{
        {0.0, 0.0, (float)nebula.width / 8.0, (float)nebula.height / 8.0}, // Rectangle Rec
        {windowDimensions[0], windowDimensions[1] - nebula.height / 8},                   // Vector2 pos
        0,                                                                 // int frame
        1.0 / 12.0,                                                        // Float updateTime
        0                                                                  // Float runningTime
    };

    //AnimData for second nebula
    AnimData nebData2{
        {0.0, 0.0, (float)nebula.width / 8.0, (float)nebula.height / 8.0},
        {windowDimensions[0] + 325, windowDimensions[1] - nebula.height / 8.0},
        0,
        1.0 / 15.0,
        0.0
    };

    AnimData nebulae[2]{ nebData, nebData2 };
    

    //Nebula X Velocity (pixels/second)
    int nebVel{-244};

    // alex variables
    Texture2D alex = LoadTexture("textures/alex.png");
    AnimData alexData;
    alexData.rec.width = alex.width / 6;
    alexData.rec.height = alex.height;
    alexData.rec.x = 0;
    alexData.rec.y = 0;
    alexData.pos.x = windowDimensions[0] / 2 - alexData.rec.width / 2;
    alexData.pos.y = windowDimensions[1] - alexData.rec.height;
    alexData.frame = 0;
    alexData.updateTime = 1.0 / 12.0;
    alexData.runningTime = 0.0;

    // Is The Rectangle in The Air?
    bool isInAir{};
    // Jump  velocity (pixels/s)/s
    const int jumpVel{-600};

    int velocity{0};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        //Delta Time (Time since last frame)
        const float dT{GetFrameTime()};
        //Start Drawing
        BeginDrawing();
        ClearBackground(WHITE);

        //Perform Ground Check
        if (alexData.pos.y >= windowDimensions[1] - alexData.rec.height)
        {
            // Rectangle is on the ground
            velocity = 0;
            isInAir = false;
        }
        else
        {
            // rectangle is in the air
            velocity += gravity * dT;
            isInAir = true;
        }
        //Jump checking
        if (IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jumpVel;
        }

        //  Update nebula Position
        nebulae[0].pos.x += nebVel * dT;

        // Update nebula2a Position
        nebulae[1].pos.x += nebVel * dT;

        //Update alex Position
        alexData.pos.y += velocity * dT;

        //update alex's animation frame
        if (!isInAir)
        {
            //Update Running Time
            alexData.runningTime += dT;
            if (alexData.runningTime >= alexData.updateTime)
            {
                alexData.runningTime = 0.0;
                // Update Animation frame
                alexData.rec.x = alexData.frame * alexData.rec.width;
                alexData.frame++;
                if (alexData.frame > 5)
                {
                    alexData.frame = 0;
                }
            }
        }

        //Update nebula animation frame
        nebulae[0].runningTime += dT;
        if (nebulae[0].runningTime >= nebulae[0].updateTime)
        {
            nebulae[0].runningTime = 0.0;
            nebulae[0].rec.x = nebulae[0].frame * nebulae[0].rec.width;
            nebulae[0].frame++;
            if (nebulae[0].frame > 7)
            {
                nebulae[0].frame = 0;
            }
        }

        //Update nebula 2 animation frame
        nebulae[1].runningTime += dT;
        if (nebulae[1].runningTime >= nebulae[1].updateTime)
        {
            nebulae[1].runningTime = 0.0;
            nebulae[1].rec.x = nebulae[1].frame * nebulae[1].rec.width;
            nebulae[1].frame++;
            if (nebulae[1].frame > 7)
            {
                nebulae[1].frame = 0;
            }
        }

        //Draw nebula
        DrawTextureRec(nebula, nebulae[0].rec, nebulae[0].pos, WHITE);

        //Draw Second nebula
        DrawTextureRec(nebula, nebulae[1].rec, nebulae[1].pos, YELLOW);

        //Draw alex
        DrawTextureRec(alex, alexData.rec, alexData.pos, WHITE);

        //Stop Drawing
        EndDrawing();
    }
    UnloadTexture(alex);
    UnloadTexture(nebula);
    CloseWindow();
}