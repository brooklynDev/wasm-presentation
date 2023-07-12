#include <stdint.h>
#include "rand.c"

#define EXPORT __attribute__((visibility("default")))

typedef struct
{
    float x;
    float y;
    float radius;
    float dx;
    float dy;
    int red;
    int green;
    int blue;
} Ball;

#define MAX_BALLS 100000
#define BALLS_PER_ITERATION 100
#define MAX_BALL_RADIUS 10

void platform_draw_ball(Ball b);

Ball balls[MAX_BALLS];

int canvas_width = 0;
int canvas_height = 0;
int current_ball_index = 0;

EXPORT void add_balls(float startX, float startY)
{
    for (int i = current_ball_index; i < current_ball_index + BALLS_PER_ITERATION; i++)
    {
        balls[i].x = startX;
        balls[i].y = startY;
        balls[i].radius = (rand_cmwc() % MAX_BALL_RADIUS) + MAX_BALL_RADIUS;
        balls[i].dx = (rand_float() * 10.0f) - 5.0f;
        balls[i].dy = (rand_float() * 10.0f) - 5.0f;
        balls[i].red = rand_cmwc() % 256;
        balls[i].green = rand_cmwc() % 256;
        balls[i].blue = rand_cmwc() % 256;
    }

    current_ball_index += BALLS_PER_ITERATION;
}

EXPORT void init(uint32_t seed, int width, int height)
{
    init_rand(seed);
    canvas_width = width;
    canvas_height = height;
}

void move_ball(Ball *b)
{
    b->x += b->dx;
    b->y += b->dy;
    if (b->x - b->radius < 0 || b->x + b->radius > canvas_width) 
    {
        b->dx *= -1;
        b->x = b->dx > 0 ? b->radius : canvas_width - b->radius;
    }
    
    if (b->y - b->radius < 0 || b->y + b->radius > canvas_height) 
    {
        b->dy *= -1;
        b->y = b->dy > 0 ? b->radius : canvas_height - b->radius;
    }
}

EXPORT void update()
{
    for (int i = 0; i < current_ball_index; i++)
    {
        move_ball(&balls[i]);
    }
}

EXPORT void draw()
{
    for (int i = 0; i < current_ball_index; i++)
    {
        platform_draw_ball(balls[i]);
    }
}

EXPORT int get_ball_count() 
{
    return current_ball_index;
}