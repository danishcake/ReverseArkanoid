#include "BrickCollection.h"
#include <cfloat>

using std::vector;

BrickCollection::BrickCollection(void) :
	mPosition((float)INITIAL_X, (float)FIXED_Y),
	mLeftEdge(0),
	mRightEdge(0),
	mBounds((float)DEFAULT_BOUNDS_W, (float)DEFAULT_BOUNDS_H)
{
}

BrickCollection::~BrickCollection(void)
{
}

void BrickCollection::AddBrick(Brick::SharedPointer brick)
{
	mBricks.push_back(brick);
	RecalculateBounds();
}

void BrickCollection::RecalculateBounds()
{
	if(mBricks.size() > 0)
	{
		mLeftEdge = FLT_MAX;
		mRightEdge = -FLT_MAX;
	} else
	{
		mLeftEdge = 0;
		mRightEdge = 0;
	}
	for(vector<Brick::SharedPointer>::iterator it = mBricks.begin(); it != mBricks.end(); ++it)
	{
		float left = (*it)->GetPosition().x;
		float right = (*it)->GetPosition().x + (*it)->GetSize().x;

		if(left < mLeftEdge)
			mLeftEdge = left;
		if(right > mRightEdge)
			mRightEdge = right;
	}
}

void BrickCollection::SetX(float x)
{
	if(x > mBounds.x - mRightEdge)
		mPosition.x = mBounds.x - mRightEdge;
	else if(x < mLeftEdge)
		mPosition.x = mLeftEdge;
	else
		mPosition.x = x;
}