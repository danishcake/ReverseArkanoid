#include "stdafx.h"
#include <ArkGame.h>
#include <Wall.h>
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

TEST(WallInheritsBounds)
{
	ArkGame::SharedPointer game(new ArkGame());
	game->SetBounds(Vector2f(640, 480));

	Wall::SharedPointer wall(new Wall());
	CHECK_EQUAL(Vector2f(Wall::DEFAULT_BOUNDS_W, Wall::DEFAULT_BOUNDS_H), wall->GetBounds());

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
	CHECK_EQUAL(Vector2f(ArkGame::DEFAULT_BOUNDS_W, ArkGame::DEFAULT_BOUNDS_H), game->GetPaddle()->GetBounds());
	game->SetBounds(Vector2f(640, 480));

	CHECK_EQUAL(Vector2f(640, 480), game->GetPaddle()->GetBounds());
}

TEST(GameStartsAfterXSeconds)
{
	ArkGame::SharedPointer game(new ArkGame());
	CHECK_EQUAL(GamePhase::Starting, game->GetPhase());
	game->Tick(((float)ArkGame::STARTING_TIME) / 1000.0f);
	CHECK_EQUAL(GamePhase::Running, game->GetPhase());
}

TEST(Lives)
{
}

TEST(GameCreatesBallAtStart)
{
	ArkGame::SharedPointer game(new ArkGame());
	game->Tick(((float)ArkGame::STARTING_TIME) / 1000.0f);
	CHECK_EQUAL(1, game->GetBalls().size());
}

TEST(BallBouncesOnPaddle)
{
	ArkGame::SharedPointer game(new ArkGame());
	game->Tick(((float)ArkGame::STARTING_TIME) / 1000.0f);
	Ball::SharedPointer ball = game->GetBalls()[0];
	ball->SetPosition(Vector2f(ball->GetPosition().x, 100));
	ball->SetVelocity(Vector2f(0, -100));

	float distance = 100 - ball->GetRadius() - Paddle::FIXED_Y;
	int steps = (distance / -ball->GetVelocity().y) / 0.016666f;
	for(int i = 0; i < steps; i++)
	{
		game->Tick(0.016666f);
	} //Advance until bounce expected
	CHECK_CLOSE(100, ball->GetVelocity().y, 5);
}

TEST(BlocksDestroyedByBall)
{
	ArkGame::SharedPointer game(new ArkGame());
	
	Wall::SharedPointer wall(new Wall());
	Brick::SharedPointer brick(new Brick(BrickType::BlueBrick));
	wall->AddBrick(brick);
	game->SetWall(wall);
	game->Tick(((float)ArkGame::STARTING_TIME) / 1000.0f);

	Ball::SharedPointer ball = game->GetBalls()[0];
	ball->SetPosition(Vector2f(100, 100));
	ball->SetVelocity(Vector2f(0, 100));

	wall->SetX(100 - Brick::BRICK_WIDTH/2);
	float distance = Wall::FIXED_Y - ball->GetPosition().y - ball->GetRadius();
	int steps = (distance / ball->GetVelocity().y) / 0.016666f;
	for(int i = 0; i < steps; i++)
	{
		game->Tick(0.016666f);
	}
	CHECK_CLOSE(-100, ball->GetVelocity().y, 5);
}

TEST(Scoring)
{
}