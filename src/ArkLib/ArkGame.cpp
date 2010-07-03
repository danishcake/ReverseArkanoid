#include "ArkGame.h"

ArkGame::ArkGame(void) : 
	mBounds((float)DEFAULT_BOUNDS_W, (float)DEFAULT_BOUNDS_H),
	mPhase(GamePhase::Starting),
	mTimer(0)
{
}

ArkGame::~ArkGame(void)
{
}

void ArkGame::Tick(float timespan)
{
	mTimer += timespan;

	switch(mPhase)
	{
	case GamePhase::Starting:
		if(mTimer >= STARTING_TIME)
		{
			mPhase = GamePhase::Running;
		}
		break;
	case GamePhase::Running:
		break;
	case GamePhase::BallLost:
		break;
	case GamePhase::GameOver:
		break;
	}
}

void ArkGame::SetWall(BrickCollection::SharedPointer wall)
{
	mWall = wall;
	mWall->SetBounds(mBounds);
}

void ArkGame::AddBall(Ball::SharedPointer ball)
{
	mBalls.push_back(ball);
	ball->SetBounds(mBounds);
}