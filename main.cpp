#include "raylib.h"
using namespace std;
int main()
{

    // window dimensions
    const int width = 800;
    const int height = 600;

    // initiate window
    InitWindow(width, height, "Penalty kick!");

    // goalpost dimensions
    const int bar = 200;
    const int post = 68;
    int gppos_x = 300;
    int gppos_y = 60;

    // goal dimensions
    int goalpos_left_x = gppos_x + 8;
    int goalpos_right_x = gppos_x + bar - 8;
    int goalpos_bottom_y = gppos_y + post;

    // football dimensions
    int radius = 30;
    int fbpos_x = 400;
    int initial_fbpos_y = 450;
    int fbpos_y = 450;
    int fb_left_x = fbpos_x - radius;
    int fb_right_x = fbpos_x + radius;
    int fb_top_y = fbpos_y - radius;
    int fb_bottom_y = fbpos_y + radius;

    // goalpost movement
    int direction = 15;

    // ball movement
    int ball_direction = 10;

    // track if kicked
    bool kicked = false;

    // track if goal
    bool goal = false;

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {

        BeginDrawing();
        ClearBackground(BLACK);

        if (goal == false)
        {
            DrawRectangle(gppos_x, gppos_y, bar, post, WHITE);
            DrawRectangle(gppos_x + 8, gppos_y + 8, 184, 58, BLACK);
            DrawLine(0, 128, width, 128, WHITE);
            DrawCircle(fbpos_x, fbpos_y, radius, WHITE);

            // game logic starts
            if (gppos_x > width - bar or gppos_x < 0)
            {
                direction = -direction;
            }

            // move goalpost
            gppos_x += direction;

            // update goal edges
            goalpos_left_x += direction;
            goalpos_right_x += direction;

            // update if kicked
            if (IsKeyPressed(KEY_SPACE))
            {
                kicked = true;
            }

            if (kicked)
            {

                // move ball
                fbpos_y -= ball_direction;

                // update ball edges
                fb_top_y -= ball_direction;
                fb_bottom_y -= ball_direction;

                // check if ball is in goal
                if (fb_bottom_y <= goalpos_bottom_y)
                {
                    if (fb_left_x > goalpos_left_x && fb_right_x < goalpos_right_x)
                    {
                        goal = true;
                    }
                }

                // update ball position if no goal
                if (fb_top_y <= 0)
                {
                    kicked = false;
                    fbpos_y = initial_fbpos_y;
                    fb_top_y = fbpos_y - radius;
                    fb_bottom_y = fbpos_y + radius;
                }
            }
            DrawText("Press Space to shoot", 260, 550, 25, WHITE);
        }

        if (goal)
        {
            DrawText("GOAL!!", 328, 260, 40, WHITE);
            DrawText("Press Space to play again!", 205, 320, 25, WHITE);
            if (IsKeyPressed(KEY_SPACE))
            {
                goal = false;
                fbpos_y = initial_fbpos_y;
                fb_top_y = fbpos_y - radius;
                fb_bottom_y = fbpos_y + radius;
                kicked = false;
            }
        }
        EndDrawing();
        // game logic ends
    }
    CloseWindow();
}