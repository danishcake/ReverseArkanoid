#pragma once
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include "vmath.h"
#include <vector>
#include "Brick.h"

class BrickCollection
{
//Typedefs
public:
	typedef boost::shared_ptr<BrickCollection> SharedPointer;
	typedef boost::weak_ptr<BrickCollection> WeakPointer;
//Constants
	static const int INITIAL_X = 200;
	static const int FIXED_Y = 440;
	static const int DEFAULT_BOUNDS_W = 400;
	static const int DEFAULT_BOUNDS_H = 480;
//Constructors
public:
	BrickCollection(void);
	~BrickCollection(void);

//Private members
private:
	float mLeftEdge;
	float mRightEdge;
	Vector2f mPosition;
	Vector2f mBounds;
	std::vector<Brick::SharedPointer> mBricks;

//Public getters/setters
public:
	const std::vector<Brick::SharedPointer> GetBricks(){return mBricks;}
	void AddBrick(Brick::SharedPointer brick);

	const Vector2f GetPosition(){return mPosition;}
	const float GetLeftEdge(){return mLeftEdge;}
	const float GetRightEdge(){return mRightEdge;}

	void SetX(float x);

	const Vector2f GetBounds(){return mBounds;}
	void SetBounds(Vector2f bounds){mBounds = bounds;}

//Private methods
private:
	void RecalculateBounds();
};
