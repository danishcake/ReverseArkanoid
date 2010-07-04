#include "Paddle.h"

Paddle::Paddle() :
	mPosition((float)INITIAL_X, (float)FIXED_Y),
	mBounds((float)DEFAULT_BOUNDS_W, (float)DEFAULT_BOUNDS_H),
	mSize((float)PADDLE_WIDTH, (float)PADDLE_HEIGHT)
{
}

void Paddle::Tick(float timespan, std::vector<Ball::SharedPointer> balls, Wall::SharedPointer wall)
{
}