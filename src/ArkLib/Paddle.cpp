#include "Paddle.h"
#include <cfloat>

using std::vector;

Paddle::Paddle() :
	mPosition((float)INITIAL_X, (float)FIXED_Y),
	mBounds((float)DEFAULT_BOUNDS_W, (float)DEFAULT_BOUNDS_H),
	mSize((float)PADDLE_WIDTH, (float)PADDLE_HEIGHT),
	mVelocity(0),
	mTargetOffset(10)
{
}

void Paddle::Tick(float timespan, std::vector<Ball::SharedPointer> balls, Wall::SharedPointer wall)
{
	float target_x;
	float target_dx;

	if(balls.size() > 0)
	{
		//First off find the ball that will arrive first
		Ball::SharedPointer ball = balls[0];
		float time_to_hit = FLT_MAX;
		
		for(vector<Ball::SharedPointer>::iterator it = balls.begin(); it != balls.end(); ++it)
		{
			float dist = (*it)->GetPosition().y;
			if((*it)->GetVelocity().y > 0)
				dist += (*it)->GetBounds().y;
			float time_to_paddle = dist / fabs((*it)->GetVelocity().y);
			
			if(time_to_paddle < time_to_hit)
			{
				time_to_hit = time_to_paddle;
				ball = *it;
			}
		}
		target_x = ball->GetPosition().x + ball->GetRadius() - mSize.x / 2;
		target_dx = ball->GetVelocity().x;
	} else
	{ //Wander to the centre slowly
		target_x = mBounds.x - mSize.x / 2;
		target_dx = 0;
	}


	//Deceleration time = delta_v / PADDLE_ACCELERATION
	//Deceleration dist = delta_t * (mVelocity + target_dx) / 2 
	float delta_v = target_dx - mVelocity;
	float decel_t = fabsf(delta_v / PADDLE_ACCELERATION);
	float decel_d = fabs(decel_t * (mVelocity + target_dx)) / 2.0f;

	//Accelerate towards target until within decel_d, then decelerate towards target_dx

	float acceleration;
	bool velocity_match = false;
	float deadzone_scale = fabsf(mPosition.x - target_x) / (mSize.x / 2);

	if(fabsf(mPosition.x - target_x) > decel_d)
	{
		if(target_x < mPosition.x)
			acceleration = -deadzone_scale;
		else
			acceleration = deadzone_scale;
	} else //Decelerate until at target_v
	{
		if(target_dx < mVelocity)
			acceleration = -1;
		else
			acceleration = 1;
		velocity_match = true;
	}

	if(acceleration > 1.0f) acceleration = 1.0f;
	if(acceleration < -1.0f) acceleration = -1.0f;
	
	if(fabs(target_dx - mVelocity) < fabs(PADDLE_ACCELERATION * acceleration) && velocity_match)
		mVelocity = target_dx;
	else
		mVelocity += PADDLE_ACCELERATION * acceleration;


	if(mVelocity > PADDLE_MAX_SPEED) mVelocity = PADDLE_MAX_SPEED;
	if(mVelocity < -PADDLE_MAX_SPEED) mVelocity = -PADDLE_MAX_SPEED;
	


	SetX(mPosition.x + mVelocity * timespan);

}

void Paddle::SetX(float x)
{
	if(x + mSize.x > mBounds.x)
		mPosition.x = mBounds.x - mSize.x;
	else if(x < 0)
		mPosition.x = 0;
	else 
		mPosition.x = x;
}