#include "stdafx.h"
#include <ArkGame.h>
#include <BrickCollection.h>
#include <Ball.h>
#include <Brick.h>

//Tests the game flow

TEST(GameBasics)
{
	//Defaults bounds
	ArkGame::SharedPointer game(new ArkGame());
	CHECK_EQUAL(Vector2f(ArkGame::DEFAULT_BOUNDS_W, ArkGame::DEFAULT_BOUNDS_H), game->GetBounds());

	//Initial state should be starting
	CHECK_EQUAL(GamePhase::Starting, game->GetPhase());
}

TEST(BrickCollectionInheritsBounds)
{
	ArkGame::SharedPointer game(new ArkGame());
	game->SetBounds(Vector2f(640, 480));

	BrickCollection::SharedPointer wall(new BrickCollection());
	CHECK_EQUAL(Vector2f(BrickCollection::DEFAULT_BOUNDS_W, BrickCollection::DEFAULT_BOUNDS_H), wall->GetBounds());

	game->SetWall(wall);
	CHECK_EQUAL(Vector2f(640, 480), wall->GetBounds());
}

TEST(BallInheritsBounds)
{
	ArkGame::SharedPointer game(new ArkGame());
	game->SetBounds(Vector2f(640, 480));

	Ball::SharedPointer ball(new Ball());
	CHECK_EQUAL(Vector2f(Ball::DEFAULT_BOUNDS_W, Ball::DEFAULT_BOUNDS_H), ball->GetBounds());

	game->AddBall(ball);
	CHECK_EQUAL(1, game->GetBalls().size());
	CHECK_EQUAL(Vector2f(640, 480), ball->GetBounds());
}

TEST(PaddleInheritsBounds)
{
	//Paddle is automatically added as I have no need to change it
	ArkGame::SharedPointer game(new ArkGame());


}

TEST(GameStartsAfterXSeconds)
{
	ArkGame::SharedPointer game(new ArkGame());
	CHECK_EQUAL(GamePhase::Starting, game->GetPhase());
	game->Tick(ArkGame::STARTING_TIME);
	CHECK_EQUAL(GamePhase::Running, game->GetPhase());
}

TEST(Lives)
{
}

TEST(BallBouncesOnPaddle)
{
}

TEST(BlocksDestroyedByBall)
{
}

TEST(Scoring)
{
}