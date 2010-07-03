#pragma once
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include "vmath.h"
#include "BrickCollection.h"
#include "Ball.h"
#include <vector>

/* ArkGame represents the moding of the game - it performs all the updates,
 * collision checking and lives of the game
 */
namespace GamePhase
{
	enum Enum
	{
		Starting, Running, BallLost, GameOver
	};
}

class ArkGame
{
//Typedefs
public:
	typedef boost::shared_ptr<ArkGame> SharedPointer;
	typedef boost::weak_ptr<ArkGame> WeakPointer;
//Constants
public:
	static const int DEFAULT_BOUNDS_W = 400;
	static const int DEFAULT_BOUNDS_H = 480;
	static const int STARTING_TIME = 2000; //ms
//Constructors
public:
	ArkGame(void);
	~ArkGame(void);
//Private members
private:
	Vector2f mBounds;
	GamePhase::Enum mPhase;
	float mTimer;
	BrickCollection::SharedPointer mWall;
	std::vector<Ball::SharedPointer> mBalls;

//Public getters/setters
public:
	Vector2f GetBounds() const{return mBounds;}
	void SetBounds(Vector2f bounds){mBounds = bounds;}

	GamePhase::Enum GetPhase() const{return mPhase;}

	BrickCollection::SharedPointer GetWall() const{return mWall;}
	void SetWall(BrickCollection::SharedPointer wall);

	void AddBall(Ball::SharedPointer ball);
	const std::vector<Ball::SharedPointer> GetBalls() const {return mBalls;}

//Public methods
public:
	void Tick(float timespan);
};
