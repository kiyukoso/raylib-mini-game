// #include "raylib.h"

// // raylib 最小可运行模板
// // 按 Ctrl+Shift+B 编译，按 F5 调试运行
// // raylib.h 的位置已经写在 .vscode 配置里，源码中不需要再写头文件路径

// int main(void)
// {
//     // 创建 800x450 的窗口，标题栏文字
//     InitWindow(800, 450, "raylib is ready");

//     // 限制帧率 60，避免空转跑满 CPU
//     SetTargetFPS(60);

//     int x = 400;   // 小球的横坐标
//     int y = 300;   // 小球的纵坐标
//     int r = 50;    // 小球半径
//     int dx = 4;    // 横向速度
//     int dy = 3;    // 纵向速度

//     // WindowShouldClose() 在点关闭按钮或按 ESC 时返回 true
//     while (!WindowShouldClose())
//     {
//         // 让小球在窗口内反弹
//         x += dx;
//         y += dy;
//         if (x - r < 0 || x + r > GetScreenWidth())  dx = -dx;
//         if (y - r < 0 || y + r > GetScreenHeight()) dy = -dy;

//         BeginDrawing();                 // 开始绘制这一帧
//         ClearBackground(RAYWHITE);      // 清屏成白色

//         DrawText("Congrats! raylib is set up.", 190, 120, 20, DARKGRAY);
//         DrawText(TextFormat("FPS: %i", GetFPS()), 10, 10, 20, LIGHTGRAY);
//         DrawCircle(x, y, r, MAROON);    // 画小球

//         EndDrawing();                   // 结束这一帧，显示出来
//     }

//     CloseWindow();   // 关闭窗口，释放资源
//     return 0;
// }


#include "raylib.h"
#include <stdlib.h>

typedef enum GameState {
    STATE_PLAYING,
    STATE_GAME_OVER
} GameState;

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "raylib Mini Game - Dodge the Blocks");

    // Player
    Rectangle player = { (float)screenWidth/2 - 20, (float)screenHeight - 80, 40, 40 };
    float playerSpeed = 5.0f;

    // Obstacle
    Rectangle obstacle = { (float)GetRandomValue(0, screenWidth - 50), -50, 50, 50 };
    float obstacleSpeed = 3.0f;

    int score = 0;
    GameState state = STATE_PLAYING;

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // -------------------- Update --------------------
        if (state == STATE_PLAYING)
        {
            // Player movement
            if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) player.x -= playerSpeed;
            if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) player.x += playerSpeed;

            // Keep player inside screen
            if (player.x < 0) player.x = 0;
            if (player.x + player.width > screenWidth) player.x = screenWidth - player.width;

            // Obstacle falls down
            obstacle.y += obstacleSpeed;

            // Obstacle passed the bottom: reset and increase score
            if (obstacle.y > screenHeight)
            {
                obstacle.y = -50;
                obstacle.x = (float)GetRandomValue(0, screenWidth - (int)obstacle.width);
                score++;
                if (obstacleSpeed < 10.0f) obstacleSpeed += 0.1f;
            }

            // Collision check
            if (CheckCollisionRecs(player, obstacle))
                state = STATE_GAME_OVER;
        }
        else if (state == STATE_GAME_OVER)
        {
            // Press SPACE to restart
            if (IsKeyPressed(KEY_SPACE))
            {
                player.x = (float)screenWidth/2 - 20;
                obstacle.y = -50;
                obstacle.x = (float)GetRandomValue(0, screenWidth - (int)obstacle.width);
                obstacleSpeed = 3.0f;
                score = 0;
                state = STATE_PLAYING;
            }
        }

        // -------------------- Draw --------------------
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (state == STATE_PLAYING)
        {
            // Draw player (blue) and obstacle (red)
            DrawRectangleRec(player, BLUE);
            DrawRectangleRec(obstacle, RED);

            // Draw score
            DrawText(TextFormat("Score: %d", score), 10, 10, 20, DARKGRAY);
        }
        else if (state == STATE_GAME_OVER)
        {
            // Game over screen
            const char *title = "GAME OVER";
            const char *finalScore = TextFormat("Final Score: %d", score);
            const char *hint = "Press SPACE to restart";

            DrawText(title,
                     screenWidth/2 - MeasureText(title, 50)/2,
                     screenHeight/2 - 80, 50, RED);
            DrawText(finalScore,
                     screenWidth/2 - MeasureText(finalScore, 30)/2,
                     screenHeight/2, 30, DARKGRAY);
            DrawText(hint,
                     screenWidth/2 - MeasureText(hint, 20)/2,
                     screenHeight/2 + 50, 20, GRAY);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}