#include "Brick.h"

Brick::Brick(BrickType::Enum brickType) :
	mBrickType(brickType),
	mSize((float)BRICK_WIDTH, (float)BRICK_HEIGHT),
	mPosition(0, 0)
{

}

Brick::~Brick(void)
{
}
