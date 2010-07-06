#include "Brick.h"

bool Brick::IsRemovable(SharedPointer brick)
{
	return brick->GetLives() <= 0;
}

Brick::Brick(BrickType::Enum brickType) :
	mBrickType(brickType),
	mSize((float)BRICK_WIDTH, (float)BRICK_HEIGHT),
	mPosition(0, 0)
{
	switch(mBrickType)
	{
	default:
	case BrickType::BlueBrick:
		mLives = 1;
		break;
	case BrickType::RedBrick:
		mLives = 2;
		break;
	case BrickType::YellowBrick:
		mLives = 3;
		break;
	}
}

Brick::~Brick(void)
{
}
