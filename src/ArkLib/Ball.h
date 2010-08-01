#pragma once
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include "vmath.h"
#include <deque>

/* The Ball class bounces around within a container and should destroy blocks it
 * comes into contact with
 */
class Ball
{
//Typedefs
public:
	typedef boost::shared_ptr<Ball> SharedPointer;
	typedef boost::weak_ptr<Ball> WeakPointer;
//Predicates
	static bool IsRemovable(SharedPointer ball);
//Constants
public:
	static const int INITIAL_SPEED = 120;
	static const int DEFAULT_BOUNDS_W = 400;
	static const int DEFAULT_BOUNDS_H = 480;
	static const int INITIAL_RADIUS = 16;
	static const int BOUNCE_ACCELERATION = 25;
	static const int BOUNCE_ACCELERATION_HIGH = 75;
	static const int MAXIMUM_SPEED = 400;
	static const int TRAIL_LENGTH = 5;
	static const int TRAIL_SEGMENT_TIME = 30; //ms

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
	bool mOverlapping;
	bool mOverlappingPaddle;
	std::deque<Vector2f> mTrail;
	float mTrailTime;
	Vector2f mTrailOffset;
//Public getters/setters
public:
	//Gets/sets the centre of the ball
	Vector2f GetPosition() const {return mPosition;}
	void SetPosition(Vector2f position){mPosition = position;}

	Vector2f GetVelocity() const {return mVelocity;}
	void SetVelocity(Vector2f velocity){mVelocity = velocity;}

	Vector2f GetBounds() const {return mBounds;}
	void SetBounds(Vector2f bounds){mBounds = bounds;}

	float GetRadius() const {return mRadius;}
	void SetRadius(float radius){mRadius = radius;}

	bool GetOverlapping() const {return mOverlapping;}
	void SetOverlapping(bool overlapping){mOverlapping = overlapping;}

	bool GetOverlappingPaddle() const {return mOverlappingPaddle;}
	void SetOverlappingPaddle(bool overlapping) {mOverlappingPaddle = overlapping;}

	const std::deque<Vector2f> GetTrail() const {return mTrail;}

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
