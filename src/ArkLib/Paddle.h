#pragma once
#include <vector>
#include "Ball.h"
#include "Wall.h"

/* Paddle represents an AI controlled opponent who will try to bat the ball at you. 
 * He should be unbeatable with one ball, but vulnerable to two at once
 *
 */
class Paddle
{
//Typedefs
public:
	typedef boost::shared_ptr<Paddle> SharedPointer;
	typedef boost::weak_ptr<Paddle> WeakPointer;
//Constants
public:
	static const int INITIAL_X = 200;
	static const int FIXED_Y = 40;
	static const int DEFAULT_BOUNDS_W = 400;
	static const int DEFAULT_BOUNDS_H = 480;
	static const int PADDLE_WIDTH = 80;
	static const int PADDLE_HEIGHT = 20;
//Constructors
public:
	Paddle(void);
//Private members
private:
	Vector2f mBounds;
	Vector2f mPosition;
	Vector2f mSize;

//Public getters/setters
public:
	Vector2f GetBounds() const {return mBounds;}
	void SetBounds(Vector2f bounds){mBounds = bounds;}

	Vector2f GetPosition() const {return mPosition;}
	Vector2f GetCentre() const {return mPosition + (mSize / 2);}
	Vector2f GetSize() const {return mSize;}

//Public methods
public:
	void Tick(float timespan, std::vector<Ball::SharedPointer> balls, Wall::SharedPointer wall);

};
