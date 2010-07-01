#include "StdAfx.h"
#include "ModeIntro.h"
#include "ModeMenu.h"

void ModeIntro::MouseSkip(Widget* /*_widget*/, MouseEventArgs /*mouse_args*/)
{
	mPendMode = new ModeMenu();
}

void ModeIntro::KeySkip(Widget* /*widget*/, KeyPressEventArgs /*key_args*/)
{
	mPendMode = new ModeMenu();
}

IMode* ModeIntro::Teardown()
{
	Widget::ClearRoot();
	return IMode::Teardown();
}

void ModeIntro::Setup()
{
	mLogo1 = new Widget("GameDev5Logo.png");
	mLogo1->SetPosition(Widget::GetScreenCentre() - (mLogo1->GetSize() / 2) - Vector2i(0, 64));
	mLogo1->SetRejectsFocus(true);

	Widget* betaTag = new Widget("Beta.png");
	betaTag->SetPosition(Widget::GetScreenSize() - betaTag->GetSize());

	Widget::OnGlobalKeyUp.connect(boost::bind(&ModeIntro::KeySkip, this, _1, _2));
	Widget::OnGlobalMouseUp.connect(boost::bind(&ModeIntro::MouseSkip, this, _1, _2));
}

ModeAction::Enum ModeIntro::Tick(float dt)
{
	ModeAction::Enum result = IMode::Tick(dt);
	Widget::SetFade(mFade);
	return result;
}

ModeType::Enum ModeIntro::GetType()
{
	return ModeType::Intro;
}

void ModeIntro::Draw(SDL_Surface* screenSurface)
{
}