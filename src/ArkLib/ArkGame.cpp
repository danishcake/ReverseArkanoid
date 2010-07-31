#include "ArkGame.h"
#include "vmath-collisions.h"

using std::vector;

ArkGame::ArkGame(void) : 
	mBounds((float)DEFAULT_BOUNDS_W, (float)DEFAULT_BOUNDS_H),
	mPhase(GamePhase::Starting),
	mTimer(0),
	mPaddle(new Paddle()),
	mScore(0)
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
			Vector2f brick_bounds[4]; //Bounding hull of brick

			vector<Brick::SharedPointer> bricks = mWall->GetBricks();
			for(vector<Brick::SharedPointer>::iterator brick = bricks.begin(); brick != bricks.end(); ++brick)
			{
				brick_bounds[0] = BrickToGame(*brick, mWall) + Vector2f(-(*brick)->GetSize().x,  (*brick)->GetSize().y) / 2.0f;
				brick_bounds[1] = BrickToGame(*brick, mWall) + Vector2f( (*brick)->GetSize().x,  (*brick)->GetSize().y) / 2.0f;
				brick_bounds[2] = BrickToGame(*brick, mWall) + Vector2f( (*brick)->GetSize().x, -(*brick)->GetSize().y) / 2.0f;
				brick_bounds[3] = BrickToGame(*brick, mWall) + Vector2f(-(*brick)->GetSize().x, -(*brick)->GetSize().y) / 2.0f;

				Vector2f collision_point;
				float collision_distance = Collisions2f::PolygonPointDistance(brick_bounds, 4, BallToGame(*ball), collision_point);
				if(collision_distance < (*ball)->GetRadius())
				{
					Vector2f outward_vector = BallToGame(*ball) - collision_point;
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
		Vector2f paddle_bounds[4]; //Bounding hull of paddle

		paddle_bounds[0] = PaddleToGame(mPaddle) + Vector2f(-mPaddle->GetSize().x,  mPaddle->GetSize().y) / 2.0f;
		paddle_bounds[1] = PaddleToGame(mPaddle) + Vector2f( mPaddle->GetSize().x,  mPaddle->GetSize().y) / 2.0f;
		paddle_bounds[2] = PaddleToGame(mPaddle) + Vector2f( mPaddle->GetSize().x, -mPaddle->GetSize().y) / 2.0f;
		paddle_bounds[3] = PaddleToGame(mPaddle) + Vector2f(-mPaddle->GetSize().x, -mPaddle->GetSize().y) / 2.0f;

		Vector2f paddle_collision_point;
		float paddle_collision_distance = Collisions2f::PolygonPointDistance(paddle_bounds, 4, BallToGame(*ball), paddle_collision_point);
		if(paddle_collision_distance < (*ball)->GetRadius())
		{
			if(!(*ball)->GetOverlappingPaddle())
			{
				const Vector2f down_bias(0, -300); //Increasing this makes bounces more vertically biased
				//(*ball)->Bounce(BallToGame(*ball) - paddle_collision_point + down_bias);
				(*ball)->Bounce(PaddleToGame(mPaddle) - paddle_collision_point + down_bias);
				(*ball)->SetOverlappingPaddle(true);

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
					split_ball->SetOverlappingPaddle(true);
					spawned_balls.push_back(split_ball);
				}
				(*ball)->SetVelocity(direction * magnitude);

				//Scoring
				if(mWall.get())
					mScore += static_cast<int>(mWall->GetBricks().size()) * BOUNCE_POINTS;
			}
		} else
		{
			(*ball)->SetOverlappingPaddle(false);
		}
	}
	for(vector<Ball::SharedPointer>::iterator it = spawned_balls.begin(); it != spawned_balls.end(); ++it)
	{
		AddBall(*it);
	}

	if(mWall.get())
	{
		int ball_count = static_cast<int>(mBalls.size());
		mBalls.erase(std::remove_if(mBalls.begin(), mBalls.end(), Ball::IsRemovable), mBalls.end());
		mScore += static_cast<int>(mWall->GetBricks().size()) * BOUNCE_POINTS * BALL_POINTS * (ball_count - mBalls.size());
	}
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

Vector2f ArkGame::BallToGame(Ball::SharedPointer ball)
{
	return ball->GetPosition() + Vector2f((640 - ball->GetBounds().x) / 2, 0);
}

Vector2f ArkGame::BrickToGame(Brick::SharedPointer brick, Wall::SharedPointer wall)
{
	return brick->GetPosition() + wall->GetPosition() + (brick->GetSize() / 2) +
		   Vector2f((640 - wall->GetBounds().x) / 2, 0);
}

Vector2f ArkGame::PaddleToGame(Paddle::SharedPointer paddle)
{
	return paddle->GetPosition() + Vector2f((640 - paddle->GetBounds().x) / 2.0, 0) + Vector2f(paddle->GetSize().x / 2, -paddle->GetSize().y / 2);
}
