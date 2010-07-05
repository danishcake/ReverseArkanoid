#pragma once
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include "vmath.h"
#include <vector>
#include "Brick.h"

class Wall
{
//Typedefs
public:
	typedef boost::shared_ptr<Wall> SharedPointer;
	typedef boost::weak_ptr<Wall> WeakPointer;
//Constants
	static const int INITIAL_X = 200;
	static const int FIXED_Y = 440;
	static const int DEFAULT_BOUNDS_W = 400;
	static const int DEFAULT_BOUNDS_H = 480;
//Constructors
public:
	Wall(void);
	Wall(std::string filename);
	~Wall(void);

//Private members
private:
	float mLeftEdge;
	float mRightEdge;
	Vector2f mPosition;
	Vector2f mBounds;
	std::vector<Brick::SharedPointer> mBricks;

//Public getters/setters
public:
	std::vector<Brick::SharedPointer> GetBricks() const {return mBricks;}
	void AddBrick(Brick::SharedPointer brick);

	Vector2f GetPosition() const {return mPosition;}
	float GetLeftEdge() const {return mLeftEdge;}
	float GetRightEdge() const {return mRightEdge;}

	void SetX(float x);

	Vector2f GetBounds() const {return mBounds;}
	void SetBounds(Vector2f bounds){mBounds = bounds;}

//Private methods
private:
	void RecalculateBounds();
};

