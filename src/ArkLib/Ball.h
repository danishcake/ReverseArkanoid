#pragma once
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include "vmath.h"

/* The Ball class bounces around within a container and should destroy blocks it
 * comes into contact with
 */
class Ball
{
//Typedefs
public:
	typedef boost::shared_ptr<Ball> SharedPointer;
	typedef boost::weak_ptr<Ball> WeakPointer;
//Constants
public:
	static const int INITIAL_SPEED = 80;
	static const int DEFAULT_BOUNDS_W = 400;
	static const int DEFAULT_BOUNDS_H = 480;
	static const int INITIAL_RADIUS = 10;

//Constructors
public:
	Ball(void);
	~Ball(void);
//Private members
private:
	Vector2f mPosition;
	Vector2f mVelocity;
	Vector2f mBounds;
	float mRadius;

//Public getters/setters
public:
	Vector2f GetPosition() const {return mPosition;}
	Vector2f GetCentre() const {return mPosition + Vector2f(mRadius, mRadius);}
	void SetPosition(Vector2f position){mPosition = position;}

	Vector2f GetVelocity() const {return mVelocity;}
	void SetVelocity(Vector2f velocity){mVelocity = velocity;}

	Vector2f GetBounds() const {return mBounds;}
	void SetBounds(Vector2f bounds){mBounds = bounds;}

	float GetRadius() const {return mRadius;}
	void SetRadius(float radius){mRadius = radius;}

//Public methods
public:
	/* Starts the ball moving straight up */
	void Start();
	/* Advances the ball. It is the users responsibility to not call with 
	   too large a timespan */
	void Tick(float timespan);
	/* Bounces against surface with specified normal */
	void Bounce(Vector2f normal);
};
