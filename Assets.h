#include <stdio.h>
#include <stdbool.h>
#include "raylib.h"
#include "raymath.h"

typedef struct {
  int x;
  int y; 
  int r;
  Color color;
  Vector2 speed;
  bool on_paddle;
  int paddle_direction;
  bool active;
}Ball;

typedef struct {
  Rectangle rect;
  Color color;
  int speed;
  int direction;
  bool is_moving;
}Paddle;

typedef struct {
  int top;
  int left;
  int bottom;
  int right;
}BBox;

typedef struct {
  Rectangle rect;
  Color color;
  bool active;
}Block;

static BBox create_bbox_rect(Rectangle rect) {
  BBox b = {rect.y, rect.x + rect.width, rect.y + rect.height, rect.x};
  return b;
}

static BBox create_bbox_ball(Ball b) {
  BBox bb = {b.y - b.r, b.x + b.r, b.y + b.r, b.x - b.r};
  return bb;
}

static void check_ball_collisions(Ball* b, Paddle p, Block* blocks, int block_count, int screen_w, int screen_h) {
  if (b->active) {
   b->x += b->speed.x;
   b->y += b->speed.y;
   
   BBox bBox = create_bbox_ball(*b);
   
   if (bBox.right >= screen_w || bBox.left <= 0) {
     b->speed.x *= -1;
   }
   
   if (bBox.bottom >= screen_h) {
    b->active = false;
   } else if (bBox.top <= 0) {
     b->speed.y *= -1;
   }
   
   Vector2 ballPos = {b->x, b->y};
   
   BBox pBox = create_bbox_rect(p.rect);
   if (CheckCollisionCircleRec(ballPos, b->r, p.rect)) {
    if (bBox.bottom >= pBox.top && (bBox.left <= pBox.right || bBox.right <= pBox.left)) {
      b->speed.y *= -1;
      b->speed.x = (int)(p.speed * p.direction);
    }
   }

   for (int i = 0; i < block_count; i++) {
    BBox blBox = create_bbox_rect(blocks[i].rect);
    if (CheckCollisionCircleRec(ballPos, b->r, blocks[i].rect)) {
      printf("block boink!");
    }
   }
  }
}

static void draw_ball(Ball ball) {
  if (ball.active) {
    DrawCircle(ball.x, ball.y, ball.r, ball.color);
  }
}

static void draw_paddle(Paddle p) {
  DrawRectangleRec(p.rect, p.color);
}

static void draw_block(Block b) {
  if (b.active) {
    DrawRectangleLines(b.rect.x, b.rect.y, b.rect.width, b.rect.height, b.color);
  }
}

static void handle_paddle_move(Paddle* p, int direction, Ball* b, int screen_w) {
  p->is_moving = true;
  p->direction = direction;
  p->rect.x += (p->speed * direction);
  if (p->rect.x < 0) {
    p->rect.x = 0;
  } else if (p->rect.x + p->rect.width > screen_w) {
    p->rect.x = screen_w - p->rect.width;
  }
  if (b->on_paddle) {
    b->x = p->rect.x + p->rect.width/2;
    b->paddle_direction = direction;
  }
}
