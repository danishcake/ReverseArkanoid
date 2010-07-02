#include "Ball.h"

Ball::Ball(void) :
	mBounds((float)DEFAULT_BOUNDS_W, (float)DEFAULT_BOUNDS_H),
	mRadius((float)INITIAL_RADIUS)
{

}

Ball::~Ball(void)
{
}


void Ball::Start()
{
	mVelocity = Vector2f(0, (float)INITIAL_SPEED);
}

void Ball::Tick(float timespan)
{
	mPosition += mVelocity * timespan;
	//Constrain and bounce in bounds
	if(mPosition.y + mRadius > mBounds.y && mVelocity.y > 0)
	{
		//Bounce off top
		mPosition.y = mBounds.y - mRadius;
		mVelocity.y *= -1;
	}
	if(mPosition.x - mRadius < 0 && mVelocity.x < 0)
	{
		mPosition.x = mRadius;
		mVelocity.x *= -1;
	}
	if(mPosition.x + mRadius > mBounds.x && mVelocity.x > 0)
	{
		mPosition.x = mBounds.x - mRadius;
		mVelocity.x *= -1;
	}
}

void Ball::Bounce(Vector2f normal)
{
	normal.normalize();
	Vector2f normal_component = normal * mVelocity.dotProduct(normal);

	mVelocity -= normal_component * 2;
}