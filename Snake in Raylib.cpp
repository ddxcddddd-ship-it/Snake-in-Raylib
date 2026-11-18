#include "raylib.h"
#include <stdlib.h>
#include <iostream>
#define SIZE 25
#define SCREEN_WIDTH SIZE * SIZE
#define SCREEN_HEIGHT SIZE * SIZE

Color green = { 170, 204, 96, 255 };
Color red = { 200, 0, 0, 255 };
int snakeSize = 1;

enum SnakeDirection {
    UP, DOWN, LEFT, RIGHT
};
SnakeDirection direction;

struct snakePosition {
    int x, y;
} snake[100];

struct applePosition {
    int x, y;
} apple;


bool gameOver;
int score = 0;


void Setup(){
InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snake in Raylib");

SetTargetFPS(10);

direction = RIGHT;

snake[0].x = (SCREEN_WIDTH / SIZE) / 2;
snake[0].y = (SCREEN_WIDTH / SIZE) / 2;
//max x and y value = 24

apple.x = rand() % SIZE;
apple.y = rand() % SIZE;

gameOver = false;

score = 0;

}
void Draw() {

    BeginDrawing();

    ClearBackground(WHITE);

    for (int i = 0; i < snakeSize; i++) {
        DrawRectangle(snake[i].x * SIZE, snake[i].y * SIZE, SIZE, SIZE, green);
    }
    DrawRectangle(apple.x * SIZE, apple.y * SIZE, SIZE, SIZE, red);



    EndDrawing();
}
void Input() {
    
    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {
        direction = UP;
    }
    else if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {
        direction = DOWN;
    }
    else if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
        direction = LEFT; 
    }
    else if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
        direction = RIGHT;
    }
}
void Logic() {
    for (int i = snakeSize; i > 0; i--) {
        snake[i].x = snake[i - 1].x;
        snake[i].y = snake[i - 1].y;
    }
    switch (direction) {
    case UP:
        snake[0].y -= 1;
        break;
    case DOWN:
        snake[0].y += 1;
        break;
    case RIGHT:
        snake[0].x += 1;
        break;
    case LEFT:
        snake[0].x -= 1;
        break;
    }
    if (snake[0].x > SIZE) {
        snake[0].x = 0;
    }
    else if (snake[0].x < 0) {
        snake[0].x = SIZE;
    }
    else if (snake[0].y < 0) {
        snake[0].y = SIZE;
    }
    else if (snake[0].y > SIZE) {
        snake[0].y = 0;
    }

    if ((snake[0].x == apple.x) && (snake[0].y == apple.y)) {
        snakeSize++;
        score++;
        apple.x = rand() % SIZE;
        apple.y = rand() % SIZE;
    }
    for (int i = 0; i < snakeSize; i++) {
        if (snake[0].x == snake[i + 1].x && snake[0].y == snake[i + 1].y) {
            gameOver = true;
        }

    }

}



int main(void)
{
    Setup();


    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        
            Draw();
            Input();
            Logic();

            if (gameOver) {
                break;
            }
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    std::cout << "SCORE: " << score;
    return 0;
}