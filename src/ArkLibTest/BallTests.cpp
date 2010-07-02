#include "stdafx.h"
#include <Ball.h>

TEST(BallBasics)
{
	Ball::SharedPointer ball(new Ball());
	CHECK_EQUAL(Vector2f(0, 0), ball->GetPosition());
	CHECK_EQUAL(Vector2f(0, 0), ball->GetVelocity());

	ball->SetPosition(Vector2f(5, 5));
	ball->SetVelocity(Vector2f(-2, 1));

	CHECK_EQUAL(Vector2f(5, 5), ball->GetPosition());
	CHECK_EQUAL(Vector2f(-2, 1), ball->GetVelocity());
}

TEST(BallStart)
{
	Ball::SharedPointer ball(new Ball());

	ball->SetPosition(Vector2f(200, 0));
	CHECK_EQUAL(Vector2f(0, 0), ball->GetVelocity());
	ball->Start();
	CHECK_EQUAL(Vector2f(0, Ball::INITIAL_SPEED), ball->GetVelocity());
}

TEST(BallMovement)
{
	Ball::SharedPointer ball(new Ball());
	ball->SetPosition(Vector2f(200, 0));
	ball->Start();
	ball->Tick(1.0f);
	CHECK_EQUAL(Vector2f(200, Ball::INITIAL_SPEED), ball->GetPosition());
}

TEST(BallPause)
{
	
}

TEST(BallBounceWalls)
{
	Ball::SharedPointer ball(new Ball());

	CHECK_EQUAL(Vector2f(Ball::DEFAULT_BOUNDS_W, Ball::DEFAULT_BOUNDS_H), ball->GetBounds());

	ball->SetPosition(Vector2f(200, 0));
	ball->Start();
	ball->Tick((float)Ball::DEFAULT_BOUNDS_H / (float)Ball::INITIAL_SPEED);
	
	CHECK_EQUAL(Vector2f(200, Ball::DEFAULT_BOUNDS_H - Ball::INITIAL_RADIUS), ball->GetPosition());
	CHECK_EQUAL(Vector2f(0, -80), ball->GetVelocity());

	ball->SetVelocity(Vector2f(-200, -50));
	ball->Tick(1.0f);

	CHECK_CLOSE(((float)Ball::INITIAL_RADIUS), ball->GetPosition().x, 0.01);
	CHECK_EQUAL(Vector2f(200, -50), ball->GetVelocity());

	ball->Tick(((float)Ball::DEFAULT_BOUNDS_W) / 200.0f);
	CHECK_EQUAL(Vector2f(-200, -50), ball->GetVelocity());
}

TEST(BallVelocityMustContainVertical)
{

}

TEST(BallBounceFlatSurface)
{
	Ball::SharedPointer ball(new Ball());
	ball->SetPosition(Vector2f(200, 200));

	ball->Start();
	ball->Bounce(Vector2f(0, 1));
	CHECK_EQUAL(Vector2f(0, -Ball::INITIAL_SPEED), ball->GetVelocity());
	ball->Bounce(Vector2f(0, 1));
	CHECK_EQUAL(Vector2f(0, Ball::INITIAL_SPEED), ball->GetVelocity());

	ball->Bounce(Vector2f(0, -1));
	CHECK_EQUAL(Vector2f(0, -Ball::INITIAL_SPEED), ball->GetVelocity());
	ball->Bounce(Vector2f(0, -1));
	CHECK_EQUAL(Vector2f(0, Ball::INITIAL_SPEED), ball->GetVelocity());

	ball->Bounce(Vector2f(1, 1)); //Up right normal equivalet to wall going left up
	CHECK_CLOSE(-Ball::INITIAL_SPEED, ball->GetVelocity().x, 0.1);
	CHECK_CLOSE(0, ball->GetVelocity().y, 0.1);
}

TEST(BallBouncePaddle)
{
}