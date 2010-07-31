#pragma once
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include "vmath.h"
#include "Wall.h"
#include "Ball.h"
#include "Paddle.h"
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
	static const int DEFAULT_BOUNDS_W = 528;
	static const int DEFAULT_BOUNDS_H = 480;
	static const int STARTING_TIME = 2000; //ms
	static const int BOUNCE_POINTS = 10;
	static const int BALL_POINTS = 5; //Equivalent to 5 bounces
//Constructors
public:
	ArkGame(void);
	~ArkGame(void);
//Private members
private:
	Vector2f mBounds;
	GamePhase::Enum mPhase;
	float mTimer;
	Wall::SharedPointer mWall;
	std::vector<Ball::SharedPointer> mBalls;
	Paddle::SharedPointer mPaddle;
	int mScore;

//Public getters/setters
public:
	Vector2f GetBounds() const{return mBounds;}
	void SetBounds(Vector2f bounds);

	GamePhase::Enum GetPhase() const{return mPhase;}

	Wall::SharedPointer GetWall() const{return mWall;}
	void SetWall(Wall::SharedPointer wall);

	void AddBall(Ball::SharedPointer ball);
	const std::vector<Ball::SharedPointer> GetBalls() const {return mBalls;}

	Paddle::SharedPointer GetPaddle() const {return mPaddle;}

	int GetScore(){return mScore;}

//Public methods
public:
	void Tick(float timespan);
	//Gets the balls center in game space 
	static Vector2f BallToGame(Ball::SharedPointer ball);
	//Gets the bricks center in game space
	static Vector2f BrickToGame(Brick::SharedPointer brick, Wall::SharedPointer wall);
	//Gets the paddles center in game space
	static Vector2f PaddleToGame(Paddle::SharedPointer paddle);
//Private methods
private:
	void TickRunning(float timespan);
};
