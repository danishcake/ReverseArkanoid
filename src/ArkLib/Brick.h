#pragma once
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include "vmath.h"

namespace BrickType
{
	enum Enum
	{
		BlueBrick,
		RedBrick,
		YellowBrick
	};
}

/* The Brick class is part of the player. It goes inside the BrickCollection 
 * that the player can move. Some bricks may have multiple lives
 */
class Brick
{
//Typedefs
public:
	typedef boost::shared_ptr<Brick> SharedPointer;
	typedef boost::weak_ptr<Brick> WeakPointer;
//Constants
public:
	static const int BRICK_WIDTH = 40;
	static const int BRICK_HEIGHT = 20;
//Constructors
public:
	Brick(BrickType::Enum brickType);
	~Brick(void);
//Private members
private:
	BrickType::Enum mBrickType;
	Vector2f mSize;
	Vector2f mPosition;

//Public getters/setters
public:
	const BrickType::Enum GetBrickType(){return mBrickType;}
	Vector2f GetSize(){return mSize;}

	const Vector2f GetPosition(){return mPosition;}
	void SetPosition(Vector2f position){mPosition = position;}
};
