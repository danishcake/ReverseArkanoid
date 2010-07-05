#include "stdafx.h"
#include <Brick.h>

TEST(BrickBasic)
{
	Brick::SharedPointer brick(new Brick(BrickType::BlueBrick));
	CHECK_EQUAL(Vector2f(0, 0), brick->GetPosition());
	CHECK_EQUAL(Vector2f(Brick::BRICK_WIDTH, Brick::BRICK_HEIGHT), brick->GetSize());
}

TEST(BrickLives)
{
	Brick::SharedPointer brick(new Brick(BrickType::BlueBrick));
	CHECK_EQUAL(1, brick->GetLives());
	brick = Brick::SharedPointer(new Brick(BrickType::RedBrick));
	CHECK_EQUAL(2, brick->GetLives());

	brick = Brick::SharedPointer(new Brick(BrickType::YellowBrick));
	CHECK_EQUAL(3, brick->GetLives());

	brick->Hit();
	CHECK_EQUAL(2, brick->GetLives());
	
	brick->Hit();
	CHECK_EQUAL(1, brick->GetLives());

	brick->Hit();
	CHECK_EQUAL(0, brick->GetLives());
}