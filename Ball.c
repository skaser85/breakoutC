#include "raylib.h"
#include "raymath.h"


typedef struct {
  float x;
  float y; 
  float r;
  Color color;
  Vector2 speed;
}Ball;

static Vector2 get_random_speed() {
  int amt_x = GetRandomValue(5, 10);
  int amt_y = GetRandomValue(5, 10);
  Vector2 speed = {amt_x, amt_y};
  return speed;
}

static void apply_speed(Ball* b) {
  b->x += (float)b->speed.x;
  b->y += (float)b->speed.y;
  if (b->x + b->r > SCREEN_WIDTH || b->x - b->r < 0) {
    b->speed.x *= -1;
  }
  if (b->y + b->r > SCREEN_HEIGHT || b->y - b->r < 0) {
    b->speed.y *= -1;
  }
}
