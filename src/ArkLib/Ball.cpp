#include "Ball.h"
#include "ArkGame.h"

bool Ball::IsRemovable(SharedPointer ball)
{
	return ball->GetPosition().y - ball->GetRadius() <= 0;
}

Ball::Ball(void) :
	mBounds((float)DEFAULT_BOUNDS_W, (float)DEFAULT_BOUNDS_H),
	mRadius((float)INITIAL_RADIUS),
	mOverlapping(false),
	mOverlappingPaddle(false),
	mTrailTime(0),
	mTrailOffset(0, 0)
{
}

Ball::~Ball(void)
{
}


void Ball::Start()
{
	mTrail.clear();
	mVelocity = Vector2f(0, (float)INITIAL_SPEED);
}

void Ball::Tick(float timespan)
{
	Vector2f ltv_position = mPosition;
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

	//Filthy hackish way to get a trail
	//Add a trail segment every 50ms so total trail 250ms long irespective of frame rate
	mTrailTime += timespan;
	if(mTrailTime > ((float)TRAIL_SEGMENT_TIME) / 1000.0f)
	{
		mTrail.push_front(ArkGame::BallToGame(this));
		if(mTrail.size() == TRAIL_LENGTH + 1)
			mTrail.pop_back();
		mTrailTime = 0;
		for(std::deque<Vector2f>::iterator it = mTrail.begin(); it != mTrail.end(); ++it)
		{
			*it -= mTrailOffset;
		}
		mTrailOffset = Vector2f(0, 0);
	} else //In between updates move all frames along, but at update undo the integration
	{
		mTrailOffset += (mPosition - ltv_position);
		for(std::deque<Vector2f>::iterator it = mTrail.begin(); it != mTrail.end(); ++it)
		{
			*it += (mPosition - ltv_position);
		}
	}
}

void Ball::Bounce(Vector2f normal)
{
	normal.normalize();
	Vector2f normal_component = normal * mVelocity.dotProduct(normal);

	mVelocity -= normal_component * 2;

	//Now constrain angles - two cones of 30 degrees left/right should be invalid
	float dot = mVelocity.dotProduct(Vector2f(1, 0));
	if(dot > cos(DEG2RAD(30)) || dot < -cos(DEG2RAD(30)))
	{
		/*
		float magnitude = mVelocity.length();
		if(mVelocity.x < 0 && mVelocity.y < 0)
			mVelocity = Vector2f(-cos(DEG2RAD(30)), -sin(DEG2RAD(30))) * magnitude;
		else if(mVelocity.x > 0 && mVelocity.y < 0)
			mVelocity = Vector2f(cos(DEG2RAD(30)), -sin(DEG2RAD(30))) * magnitude;
		else if(mVelocity.x < 0 && mVelocity.y > 0)
			mVelocity = Vector2f(-cos(DEG2RAD(30)), sin(DEG2RAD(30))) * magnitude;
		else
			mVelocity = Vector2f(cos(DEG2RAD(30)), sin(DEG2RAD(30))) * magnitude;
			*/
	}

}