#include "ArkGame.h"
#include "vmath-collisions.h"

using std::vector;

ArkGame::ArkGame(void) : 
	mBounds((float)DEFAULT_BOUNDS_W, (float)DEFAULT_BOUNDS_H),
	mPhase(GamePhase::Starting),
	mTimer(0),
	mPaddle(new Paddle())
{
	mPaddle->SetBounds(mBounds);
	mPaddle->SetX(mBounds.x / 2 - mPaddle->GetSize().x / 2);
}

ArkGame::~ArkGame(void)
{
}

void ArkGame::TickRunning(float timespan)
{
	vector<Ball::SharedPointer> spawned_balls;
	for(vector<Ball::SharedPointer>::iterator ball = mBalls.begin(); ball != mBalls.end(); ++ball)
	{
		//Advance the ball and bounce off bounds
		(*ball)->Tick(timespan);
		//Collide with the wall
		bool ball_hit = false;
		if(mWall.get())
		{
			Vector2f brick_bounds[5]; //Bounding hull of brick

			vector<Brick::SharedPointer> bricks = mWall->GetBricks();
			for(vector<Brick::SharedPointer>::iterator brick = bricks.begin(); brick != bricks.end(); ++brick)
			{
				brick_bounds[0] = (*brick)->GetPosition() + mWall->GetPosition();
				brick_bounds[1] = (*brick)->GetPosition() + Vector2f((*brick)->GetSize().x, 0) + mWall->GetPosition();
				brick_bounds[2] = (*brick)->GetPosition() + (*brick)->GetSize() + mWall->GetPosition();
				brick_bounds[3] = (*brick)->GetPosition() + Vector2f(0, (*brick)->GetSize().y) + mWall->GetPosition();
				brick_bounds[4] = (*brick)->GetPosition() + mWall->GetPosition();

				Vector2f collision_point;
				int collision_index;
				if(Collisions2f::CircleIntersectsConvex((*ball)->GetCentre(), (*ball)->GetRadius(), brick_bounds, 5, collision_point, collision_index))
				{
					Vector2f outward_vector;
					//Vector2f outward_vector = (*ball)->GetCentre() - collision_point;
					//outward_vector.normalize();//
					switch(collision_index)
					{
					case 0:
					case 3:
					default:
						outward_vector = Vector2f(0, 1);
						break;
					case 1:
					case 2:
						outward_vector = Vector2f(1, 0);
						break;
					}

					if(!(*ball)->GetOverlapping())
					{
						(*ball)->Bounce(outward_vector);
						(*ball)->SetOverlapping(true);
						(*brick)->Hit();
					}
					ball_hit = true;
				}
			}
			mWall->Tick();
		}

		if(!ball_hit)
			(*ball)->SetOverlapping(false);


		//Collide with the paddle
		Vector2f paddle_bottom_left = mPaddle->GetPosition();
		Vector2f paddle_top_left = mPaddle->GetPosition() + Vector2f(0, mPaddle->GetSize().y);
		Vector2f paddle_top_right = mPaddle->GetPosition() + mPaddle->GetSize();
		Vector2f collision_point;

		if((*ball)->GetVelocity().y <= 0 && Collisions2f::LineInCircle(paddle_top_left, paddle_top_right, 
									  (*ball)->GetCentre(), (*ball)->GetRadius(),
									  collision_point))
		{
			const Vector2f down_bias(0, -100); //Increasing this makes bounces more vertically biased
			Vector2f outward_vector = (*ball)->GetCentre() - (mPaddle->GetCentre() + down_bias);
			outward_vector.normalize();
			(*ball)->Bounce(outward_vector);
			//Apply acceleration

			Vector2f direction = (*ball)->GetVelocity();
			float magnitude = direction.length();
			direction.normalize();
			magnitude += Ball::BOUNCE_ACCELERATION;
			if(magnitude > Ball::MAXIMUM_SPEED)
			{
				Vector2f split_direction;
				magnitude = Ball::INITIAL_SPEED;
				if(direction.x < 0)
					direction.x -= 0.2f;
				else
					direction.x += 0.2f;

				direction.normalize();
				split_direction = direction;
				split_direction.x *= -1;


				Ball::SharedPointer split_ball(new Ball());
				split_ball->SetPosition((*ball)->GetPosition());
				split_ball->SetVelocity(split_direction * (magnitude + 2 * Ball::BOUNCE_ACCELERATION));
				spawned_balls.push_back(split_ball);
			}
			(*ball)->SetVelocity(direction * magnitude);
		}
	}
	for(vector<Ball::SharedPointer>::iterator it = spawned_balls.begin(); it != spawned_balls.end(); ++it)
	{
		AddBall(*it);
	}

	mBalls.erase(std::remove_if(mBalls.begin(), mBalls.end(), Ball::IsRemovable), mBalls.end());;
	mPaddle->Tick(timespan, mBalls, mWall);
}

void ArkGame::Tick(float timespan)
{
	mTimer += timespan;

	switch(mPhase)
	{
	case GamePhase::Starting:
		if(mTimer >= ((float)STARTING_TIME) / 1000.0f)
		{
			mPhase = GamePhase::Running;
			Ball::SharedPointer ball(new Ball());
			ball->SetPosition(mPaddle->GetCentre() + Vector2f(-ball->GetRadius(), ball->GetRadius() + (mPaddle->GetSize().y / 2.0f)));
			ball->Start();
			AddBall(ball);
		}
		break;
	case GamePhase::Running:
		TickRunning(timespan);
		break;
	case GamePhase::BallLost:
		break;
	case GamePhase::GameOver:
		break;
	}
}

void ArkGame::SetBounds(Vector2f bounds)
{
	mBounds = bounds;
	for(vector<Ball::SharedPointer>::iterator it = mBalls.begin(); it != mBalls.end(); ++it)
	{
		(*it)->SetBounds(bounds);
	}
	if(mWall.get())
		mWall->SetBounds(mBounds);
	mPaddle->SetBounds(mBounds);
}

void ArkGame::SetWall(Wall::SharedPointer wall)
{
	mWall = wall;
	mWall->SetBounds(mBounds);
	mWall->SetY(Wall::FIXED_Y - mWall->GetTopEdge());
	mWall->SetX(mBounds.x / 2 - (mWall->GetRightEdge() + mWall->GetLeftEdge()) / 2);
}

void ArkGame::AddBall(Ball::SharedPointer ball)
{
	mBalls.push_back(ball);
	ball->SetBounds(mBounds);
}