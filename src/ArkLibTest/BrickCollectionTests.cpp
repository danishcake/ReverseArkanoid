#include "stdafx.h"
#include <BrickCollection.h>
#include <Brick.h>

TEST(CollectionBasics)
{
	BrickCollection::SharedPointer collection(new BrickCollection());
	CHECK_EQUAL(Vector2f(BrickCollection::INITIAL_X, BrickCollection::FIXED_Y), collection->GetPosition());
	CHECK_EQUAL(0, collection->GetBricks().size());

	CHECK_EQUAL(Vector2f(BrickCollection::DEFAULT_BOUNDS_W, BrickCollection::DEFAULT_BOUNDS_H), collection->GetBounds());
}

TEST(AddBricks)
{
	BrickCollection::SharedPointer collection(new BrickCollection());
	Brick::SharedPointer brick(new Brick(BrickType::BlueBrick));
	brick->SetPosition(Vector2f(0, 0));

	collection->AddBrick(brick);
	CHECK_EQUAL(1, collection->GetBricks().size());
	CHECK_EQUAL(0, collection->GetLeftEdge());
	CHECK_EQUAL(Brick::BRICK_WIDTH, collection->GetRightEdge());

	//Collection can only move within limits of bounds

	collection->SetX(0);
	CHECK_EQUAL(0, collection->GetPosition().x);
	collection->SetX(-10);
	CHECK_EQUAL(0, collection->GetPosition().x);
	collection->SetX(collection->GetBounds().x + 500);
	CHECK_EQUAL(collection->GetBounds().x - Brick::BRICK_WIDTH, collection->GetPosition().x);
}

