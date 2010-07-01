#pragma once
#include <vector>
struct SDL_Surface;

namespace ModeType
{
	enum Enum
	{
		Intro,
		Menu,
		Game
	};
}

namespace ModeAction
{
	enum Enum
	{
		NoAction,
		ChangeMode,
		Exit
	};
}

/*
 * Represents a mode for a state machine.
 */
class IMode
{
protected:
	IMode* mPendMode;
	float mPendTime;
	float mPendTimer;
	float mAge;
	float mFade;
public:
	IMode();
	virtual ~IMode(){}
	virtual IMode* Teardown();
	virtual void Setup() = 0;
	virtual ModeAction::Enum Tick(float _dt);
	virtual ModeType::Enum GetType() = 0;
	virtual void Draw(SDL_Surface* screenSurface) = 0;
};
