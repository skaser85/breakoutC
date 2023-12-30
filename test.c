#include <stdbool.h>
#include "Assets.h"

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 600

#define PADDLE_WIDTH 100
#define PADDLE_HEIGHT 20
#define PADDLE_SPEED  10

#define BLOCK_WIDTH 100
#define BLOCK_HEIGHT 20
#define BLOCK_COUNT  10

int main(void) {
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "breakout test");

  SetTargetFPS(60);

  SetRandomSeed(45356);

  int cx = SCREEN_WIDTH / 2;
  int cy = SCREEN_HEIGHT / 2;

  Rectangle rect = {
    cx - PADDLE_WIDTH/2, 
    SCREEN_HEIGHT - 100 - PADDLE_HEIGHT/2, 
    PADDLE_WIDTH, 
    PADDLE_HEIGHT
  };
  Paddle paddle = {rect, ORANGE, 10.0f, 1, false};
  
  int r = 10;
  Vector2 s = {0, 0};
  Ball ball = {
    rect.x + PADDLE_WIDTH/2 - r/2, 
    rect.y - r - 1, 
    r ,LIME, s, true, 1, true
  };
  
  Block blocks[BLOCK_COUNT] = {0};
  for (int i = 0; i < BLOCK_COUNT; i++) {
    Rectangle r = {i*BLOCK_WIDTH, 200, BLOCK_WIDTH, BLOCK_HEIGHT};
    Block b = {r, BLACK, true};
    blocks[i] = b;
  }

  while (!WindowShouldClose())
	{

    if (ball.on_paddle) {
      if (IsKeyPressed(KEY_SPACE)) {
        ball.on_paddle = false;
        int x = 0;
        if (paddle.is_moving) {
          x = paddle.speed * ball.paddle_direction;
        }
        Vector2 s = {x, -3};
        ball.speed = s;
      }
    }

    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
      handle_paddle_move(&paddle, -1, &ball, SCREEN_WIDTH);
    } else if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
      handle_paddle_move(&paddle, 1, &ball, SCREEN_WIDTH);
    } else {
      paddle.is_moving = false;
    }

    check_ball_collisions(&ball, paddle, blocks, BLOCK_COUNT, SCREEN_WIDTH, SCREEN_HEIGHT);
	
    BeginDrawing();
		ClearBackground(RAYWHITE);

    for (int i = 0; i < BLOCK_COUNT; i++) {
      draw_block(blocks[i]);
    }
    draw_ball(ball);
    draw_paddle(paddle);

    EndDrawing();
  }		
	
  CloseWindow();
	
	return 0;
}
