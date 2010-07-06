#include "stdafx.h"
#include <Paddle.h>
#include <Ball.h>
#include <Wall.h>

TEST(PaddleGuessesWhenBallReceding)
{
	std::vector<Ball::SharedPointer> balls;
	Ball::SharedPointer ball(new Ball());
	balls.push_back(ball);
	ball->SetPosition(Vector2f(50, 50));
	ball->SetVelocity(Vector2f(25, 75));

	Wall::SharedPointer wall(new Wall());
	Paddle::SharedPointer paddle(new Paddle());

	paddle->Tick(0.1f, balls, wall);



	//The ball will take ( paddle->GetBounds().y * 2 - paddle->GetPosition().y - ball->GetPosition().y) / yspeed to get back
	float transit_time = (paddle->GetBounds().y * 2 - paddle->GetPosition().y - ball->GetPosition().y) / ball->GetVelocity().y;
	//Therefore it will move this far
	float x_dist = ball->GetVelocity().x * transit_time;
	float x_final =  fmodf(x_dist + ball->GetPosition().x, ball->GetBounds().x);
	
}

TEST(PaddleTracksWhenBallApproaching)
{

}

TEST(PaddlePrioritisesFirstArrivingBall)
{
}