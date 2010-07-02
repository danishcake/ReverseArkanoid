#include "stdafx.h"
#include <Brick.h>

TEST(BrickBasic)
{
	Brick::SharedPointer brick(new Brick(BrickType::BlueBrick));
	CHECK_EQUAL(Vector2f(0, 0), brick->GetPosition());
	CHECK_EQUAL(Vector2f(Brick::BRICK_WIDTH, Brick::BRICK_HEIGHT), brick->GetSize());

	
}