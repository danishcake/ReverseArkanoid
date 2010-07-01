#include "stdafx.h"
#include "IMode.h"
#include <cstring> //For NULL
#include <assert.h>

IMode::IMode()
{
	mPendMode = NULL;
	mPendTime = 1;
	mPendTimer = 0;
	mAge = 0;
	mFade = 0;
}

ModeAction::Enum IMode::Tick(float _dt)
{
	if(mPendMode)
		mPendTimer += _dt;
	else
		mPendTimer -= _dt;

	mPendTimer = mPendTimer < 0 ? 0 : mPendTimer;
	mAge += _dt;
	
	float fadeIn = 1.0f - (mAge / mPendTime);
	float fadeOut = mPendTimer / mPendTime;
	mFade = fadeIn > fadeOut ? fadeIn : fadeOut;
	mFade = mFade > 1 ? 1 : mFade;
	
	if(mPendTimer > mPendTime)
		return ModeAction::ChangeMode;
	else
		return ModeAction::NoAction;
}

IMode* IMode::Teardown()
{
	assert(mPendMode);
	return mPendMode;
}